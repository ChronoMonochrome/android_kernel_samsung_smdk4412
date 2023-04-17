#ifndef __DEVICE_GENALLOC_H__
#define __DEVICE_GENALLOC_H__
#include <linux/genalloc.h>

extern unsigned long gen_pool_alloc_aligned(struct gen_pool *, size_t,
                       unsigned);
#endif /* __DEVICE_GENALLOC_H__ */
