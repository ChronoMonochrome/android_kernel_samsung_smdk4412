/*
 * Library implementing the most common irq chip callback functions
 *
 * Copyright (C) 2011, Thomas Gleixner
 */
#include <linux/io.h>
#include <linux/irq.h>

static inline struct irq_chip_regs *cur_regs(struct irq_data *d)
{
	return &container_of(d->chip, struct irq_chip_type, chip)->regs;
}

/**
 * irq_gc_mask_and_ack_set- Mask and ack pending interrupt
 * @d: irq_data
 */
void irq_gc_mask_and_ack_set(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	u32 mask = 1 << (d->irq - gc->irq_base);

	irq_gc_lock(gc);
	gc->mask_cache |= mask;
	irq_reg_writel(gc->mask_cache, gc->reg_base + cur_regs(d)->mask);
	irq_reg_writel(mask, gc->reg_base + cur_regs(d)->ack);
	irq_gc_unlock(gc);
}
