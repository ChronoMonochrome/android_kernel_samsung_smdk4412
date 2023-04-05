/*
 * mm/truncate.c - code for taking down pages from address_spaces
 *
 * Copyright (C) 2002, Linus Torvalds
 *
 * 10Sep2002	Andrew Morton
 *		Initial version.
 */

#include <linux/kernel.h>
#include <linux/backing-dev.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/export.h>
#include <linux/pagemap.h>
#include <linux/highmem.h>
#include <linux/pagevec.h>

int vmtruncate_range(struct inode *inode, loff_t lstart, loff_t lend)
{
	struct address_space *mapping = inode->i_mapping;
	loff_t holebegin = round_up(lstart, PAGE_SIZE);
	loff_t holelen = 1 + lend - holebegin;

	/*
	 * If the underlying filesystem is not going to provide
	 * a way to truncate a range of blocks (punch a hole) -
	 * we should return failure right now.
	 */
	if (!inode->i_op->truncate_range)
		return -ENOSYS;

	mutex_lock(&inode->i_mutex);
	inode_dio_wait(inode);
	unmap_mapping_range(mapping, holebegin, holelen, 1);
	inode->i_op->truncate_range(inode, lstart, lend);
	/* unmap again to remove racily COWed private pages */
	unmap_mapping_range(mapping, holebegin, holelen, 1);
	mutex_unlock(&inode->i_mutex);

	return 0;
}
