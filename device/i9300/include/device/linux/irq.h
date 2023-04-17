#ifndef _DEVICE_LINUX_IRQ_H
#define _DEVICE_LINUX_IRQ_H

#include <linux/irq.h>

void irq_gc_mask_and_ack_set(struct irq_data *d);
#endif /* _DEVICE_LINUX_IRQ_H */
