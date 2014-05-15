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

extern void exynos4_register_clocks(void);
extern void exynos4_setup_clocks(void);

void combiner_init(void __iomem *combiner_base, struct device_node *np);
extern void combiner_cascade_irq(unsigned int combiner_nr, unsigned int irq);

extern void exynos_cpu_die(unsigned int cpu);
extern void __init exynos4_timer_init(void);
void exynos_cpufreq_init(void);
extern void exynos_cpu_power_down(int cpu);
extern void exynos_cpu_power_up(int cpu);
extern int  exynos_cpu_power_state(int cpu);

extern void set_gps_uart_op(int onoff);
int check_gps_uart_op(void);
#endif /* __ARCH_ARM_MACH_EXYNOS_COMMON_H */
