/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Common Header for EXYNOS machines
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ARCH_ARM_MACH_EXYNOS_COMMON_H
#define __ARCH_ARM_MACH_EXYNOS_COMMON_H

extern struct smp_operations exynos_smp_ops;

void combiner_init(void __iomem *combiner_base, struct device_node *np);
extern void combiner_cascade_irq(unsigned int combiner_nr, unsigned int irq);

extern void exynos_cpu_die(unsigned int cpu);
extern void __init exynos_timer_init(void);

#endif /* __ARCH_ARM_MACH_EXYNOS_COMMON_H */
