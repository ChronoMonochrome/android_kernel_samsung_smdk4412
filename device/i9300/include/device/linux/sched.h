#ifndef _DEVICE_LINUX_SCHED_H
#define _DEVICE_LINUX_SCHED_H

#include <linux/sched.h>

#define PF_FREEZING    0x00004000      /* freeze in progress. do not account to load */
#define PF_FREEZER_NOSIG 0x80000000  /* Freezer won't send signals to it */
#endif
