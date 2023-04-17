#ifndef __DEVICE_LINUX_BITMAP_H
#define __DEVICE_LINUX_BITMAP_H

#include <linux/bitmap.h>

extern unsigned long bitmap_find_next_zero_area_off(unsigned long *map,
						    unsigned long size,
						    unsigned long start,
						    unsigned int nr,
						    unsigned long align_mask,
						    unsigned long align_offset);
#endif /* __LINUX_BITMAP_H */
