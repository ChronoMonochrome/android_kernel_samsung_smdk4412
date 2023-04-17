/*
 * Basic general purpose allocator for managing special purpose
 * memory, for example, memory that is not managed by the regular
 * kmalloc/kfree interface.  Uses for this includes on-device special
 * memory, uncached memory etc.
 *
 * It is safe to use the allocator in NMI handlers and other special
 * unblockable contexts that could otherwise deadlock on locks.  This
 * is implemented by using atomic operations and retries on any
 * conflicts.  The disadvantage is that there may be livelocks in
 * extreme cases.  For better scalability, one allocator can be used
 * for each CPU.
 *
 * The lockless operation only works if there is enough memory
 * available.  If new memory is added to the pool a lock has to be
 * still taken.  So any user relying on locklessness has to ensure
 * that sufficient memory is preallocated.
 *
 * The basic atomic operation of this allocator is cmpxchg on long.
 * On architectures that don't have NMI-safe cmpxchg implementation,
 * the allocator can NOT be used in NMI handler.  So code uses the
 * allocator in NMI handler should depend on
 * CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG.
 *
 * Copyright 2005 (C) Jes Sorensen <jes@trained-monkey.org>
 *
 * This source code is licensed under the GNU General Public License,
 * Version 2.  See the file COPYING for more details.
 */

#include <linux/slab.h>
#include <linux/export.h>
#include <device/linux/bitmap.h>
#include <linux/rculist.h>
#include <linux/interrupt.h>
#include <device/linux/genalloc.h>

static int set_bits_ll(unsigned long *addr, unsigned long mask_to_set)
{
	unsigned long val, nval;

	nval = *addr;
	do {
		val = nval;
		if (val & mask_to_set)
			return -EBUSY;
		cpu_relax();
	} while ((nval = cmpxchg(addr, val, val | mask_to_set)) != val);

	return 0;
}

static int clear_bits_ll(unsigned long *addr, unsigned long mask_to_clear)
{
	unsigned long val, nval;

	nval = *addr;
	do {
		val = nval;
		if ((val & mask_to_clear) != mask_to_clear)
			return -EBUSY;
		cpu_relax();
	} while ((nval = cmpxchg(addr, val, val & ~mask_to_clear)) != val);

	return 0;
}

/*
 * bitmap_set_ll - set the specified number of bits at the specified position
 * @map: pointer to a bitmap
 * @start: a bit position in @map
 * @nr: number of bits to set
 *
 * Set @nr bits start from @start in @map lock-lessly. Several users
 * can set/clear the same bitmap simultaneously without lock. If two
 * users set the same bit, one user will return remain bits, otherwise
 * return 0.
 */
static int bitmap_set_ll(unsigned long *map, int start, int nr)
{
	unsigned long *p = map + BIT_WORD(start);
	const int size = start + nr;
	int bits_to_set = BITS_PER_LONG - (start % BITS_PER_LONG);
	unsigned long mask_to_set = BITMAP_FIRST_WORD_MASK(start);

	while (nr - bits_to_set >= 0) {
		if (set_bits_ll(p, mask_to_set))
			return nr;
		nr -= bits_to_set;
		bits_to_set = BITS_PER_LONG;
		mask_to_set = ~0UL;
		p++;
	}
	if (nr) {
		mask_to_set &= BITMAP_LAST_WORD_MASK(size);
		if (set_bits_ll(p, mask_to_set))
			return nr;
	}

	return 0;
}

/*
 * bitmap_clear_ll - clear the specified number of bits at the specified position
 * @map: pointer to a bitmap
 * @start: a bit position in @map
 * @nr: number of bits to set
 *
 * Clear @nr bits start from @start in @map lock-lessly. Several users
 * can set/clear the same bitmap simultaneously without lock. If two
 * users clear the same bit, one user will return remain bits,
 * otherwise return 0.
 */
static int bitmap_clear_ll(unsigned long *map, int start, int nr)
{
	unsigned long *p = map + BIT_WORD(start);
	const int size = start + nr;
	int bits_to_clear = BITS_PER_LONG - (start % BITS_PER_LONG);
	unsigned long mask_to_clear = BITMAP_FIRST_WORD_MASK(start);

	while (nr - bits_to_clear >= 0) {
		if (clear_bits_ll(p, mask_to_clear))
			return nr;
		nr -= bits_to_clear;
		bits_to_clear = BITS_PER_LONG;
		mask_to_clear = ~0UL;
		p++;
	}
	if (nr) {
		mask_to_clear &= BITMAP_LAST_WORD_MASK(size);
		if (clear_bits_ll(p, mask_to_clear))
			return nr;
	}

	return 0;
}

/**
 * gen_pool_alloc_aligned() - allocate special memory from the pool
 * @pool:	Pool to allocate from.
 * @size:	Number of bytes to allocate from the pool.
 * @alignment_order:	Order the allocated space should be
 *			aligned to (eg. 20 means allocated space
 *			must be aligned to 1MiB).
 *
 * Allocate the requested number of bytes from the specified pool.
 * Uses a first-fit algorithm.
 */
unsigned long __must_check
gen_pool_alloc_aligned(struct gen_pool *pool, size_t size,
		       unsigned alignment_order)
{
	struct gen_pool_chunk *chunk;
	unsigned long addr = 0, align_mask = 0, flags, start = 0;
	int order = pool->min_alloc_order;
	int nbits, remain;

	size_t chunk_size;

#ifndef CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG
	BUG_ON(in_nmi());
#endif

	if (size == 0)
		return 0;

	if (alignment_order > order)
		align_mask = (1 << (alignment_order - order)) - 1;

	nbits = (size + (1UL << order) - 1) >> order;
	//size = nbits >> order;

	rcu_read_lock();
	list_for_each_entry_rcu(chunk, &pool->chunks, next_chunk) {
		if (size > atomic_read(&chunk->avail))
			continue;

		chunk_size = chunk->end_addr - chunk->start_addr + 1;
		if (chunk_size < size)
			continue;

retry:
		start = bitmap_find_next_zero_area_off(chunk->bits, chunk_size,
						       0, size, align_mask,
						       chunk->start_addr);
		if (start >= chunk_size)
			continue;

		bitmap_set(chunk->bits, start, size);
		remain = bitmap_set_ll(chunk->bits, start, nbits);
		if (remain) {
			remain = bitmap_clear_ll(chunk->bits, start,
						 nbits - remain);
			BUG_ON(remain);
			goto retry;
 		}

		addr = (chunk->start_addr + start) << pool->min_alloc_order;
		size = nbits << order;
		atomic_sub(size, &chunk->avail);
		break;
	}
	rcu_read_unlock();
	return addr;
}
EXPORT_SYMBOL(gen_pool_alloc_aligned);

