#ifndef _DEVICE_LINUX_MM
#define _DEVICE_LINUX_MM

#include <linux/mm.h>

int vmtruncate_range(struct inode *inode, loff_t lstart, loff_t lend);
#endif // _DEVICE_LINUX_MM
