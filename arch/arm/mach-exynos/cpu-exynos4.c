/* linux/arch/arm/mach-exynos/cpu.c
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/sched.h>
#include <linux/delay.h>

#include <asm/mach/map.h>
#include <asm/mmu-legacy.h>
#include <asm/mach/irq.h>

#include <asm/proc-fns.h>
#include <asm/hardware/cache-l2x0.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/irqchip/arm-gic.h>
#include <asm/cacheflush.h>

#include <plat/cpu.h>
#include <plat/clock.h>
#include <plat/devs.h>
#include <plat/fb-core.h>
#include <plat/exynos4.h>
#include <plat/sdhci.h>
#include <plat/mshci.h>
#include <plat/fimc-core.h>
#include <plat/adc-core.h>
#include <plat/pm.h>
#include <plat/iic-core.h>
#include <plat/ace-core.h>
#include <plat/reset.h>
#include <plat/audio.h>
#include <plat/tv-core.h>
#include <plat/rtc-core.h>

#include <mach/regs-irq.h>
#include <mach/regs-pmu.h>
#include <mach/smc.h>
#include "common.h"

unsigned int gic_bank_offset __read_mostly;

static void exynos4_idle(void)
{
	if (!need_resched())
		cpu_do_idle();

	local_irq_enable();
}

void __init exynos4_init_clocks(int xtal)
{
	printk(KERN_DEBUG "%s: initializing clocks\n", __func__);

	s3c24xx_register_baseclocks(xtal);

	if (soc_is_exynos4210())
		exynos4210_register_clocks();
	else
		exynos4212_register_clocks();

	s5p_register_clocks(xtal);
	exynos4_register_clocks();
	exynos4_setup_clocks();
}

#define COMBINER_MAP(x)	((x < 16) ? IRQ_SPI(x) :	\
			(x == 16) ? IRQ_SPI(107) :	\
			(x == 17) ? IRQ_SPI(108) :	\
			(x == 18) ? IRQ_SPI(48) :	\
			(x == 19) ? IRQ_SPI(49) : 0)

void __init exynos4_init_irq(void)
{
	int irq;

	gic_bank_offset = soc_is_exynos4412() ? 0x4000 : 0x8000;

	if (!of_have_populated_dt()) {
		gic_init_bases(0, IRQ_PPI(0), S5P_VA_GIC_DIST, S5P_VA_GIC_CPU, gic_bank_offset, NULL);
		gic_arch_extn.irq_set_wake = s3c_irq_wake;
	}
#ifdef CONFIG_OF
	else
		irqchip_init();
#endif

	if (!of_have_populated_dt())
		combiner_init(S5P_VA_COMBINER_BASE, NULL);

	/*
	 * The parameters of s5p_init_irq() are for VIC init.
	 * Theses parameters should be NULL and 0 because EXYNOS4
	 * uses GIC instead of VIC.
	 */
	s5p_init_irq(NULL, 0);
}

struct bus_type exynos4_subsys = {
	.name	= "exynos4-core",
	.dev_name	= "exynos4-core",
};

static struct device exynos4_dev = {
	.bus	= &exynos4_subsys,
};

static int __init exynos4_core_init(void)
{
	return subsys_system_register(&exynos4_subsys, NULL);
}

core_initcall(exynos4_core_init);

#ifdef CONFIG_CACHE_L2X0
#ifdef CONFIG_ARM_TRUSTZONE
#if defined(CONFIG_PL310_ERRATA_588369) || defined(CONFIG_PL310_ERRATA_727915)
static void exynos4_l2x0_set_debug(unsigned long val)
{
	exynos_smc(SMC_CMD_L2X0DEBUG, val, 0, 0);
}
#endif
#endif

static int __init exynos4_l2x0_cache_init(void)
{
	u32 tag_latency = 0x110;
	u32 data_latency = soc_is_exynos4210() ? 0x110 : 0x120;
	u32 prefetch = (soc_is_exynos4412() &&
			samsung_rev() >= EXYNOS4412_REV_1_0) ?
			0x71000007 : 0x30000007;
	u32 aux_val = 0x7C470001;
	u32 aux_mask = 0xC200FFFF;

#ifdef CONFIG_ARM_TRUSTZONE
	exynos_smc(SMC_CMD_L2X0SETUP1, tag_latency, data_latency, prefetch);
	exynos_smc(SMC_CMD_L2X0SETUP2,
		   L2X0_DYNAMIC_CLK_GATING_EN | L2X0_STNDBY_MODE_EN,
		   aux_val, aux_mask);
	exynos_smc(SMC_CMD_L2X0INVALL, 0, 0, 0);
	exynos_smc(SMC_CMD_L2X0CTRL, 1, 0, 0);
#else
	__raw_writel(tag_latency, S5P_VA_L2CC + L2X0_TAG_LATENCY_CTRL);
	__raw_writel(data_latency, S5P_VA_L2CC + L2X0_DATA_LATENCY_CTRL);
	__raw_writel(prefetch, S5P_VA_L2CC + L2X0_PREFETCH_CTRL);
	__raw_writel(L2X0_DYNAMIC_CLK_GATING_EN | L2X0_STNDBY_MODE_EN,
		     S5P_VA_L2CC + L2X0_POWER_CTRL);
#endif

	l2x0_init(S5P_VA_L2CC, aux_val, aux_mask);

#ifdef CONFIG_ARM_TRUSTZONE
#if defined(CONFIG_PL310_ERRATA_588369) || defined(CONFIG_PL310_ERRATA_727915)
	outer_cache.set_debug = exynos4_l2x0_set_debug;
#endif
#endif
	/* Enable the full line of zero */
	enable_cache_foz();
	return 0;
}

//early_initcall(exynos4_l2x0_cache_init);
early_initcall(exynos4_l2x0_cache_init);
#endif

static void exynos4_sw_reset(void)
{
	int count = 3;

	while (count--) {
		__raw_writel(0x1, EXYNOS_SWRESET);
		mdelay(500);
	}
}

static void __iomem *exynos4_pmu_init_zero[] = {
	S5P_CMU_RESET_ISP_SYS,
	S5P_CMU_SYSCLK_ISP_SYS,
};

int __init exynos4_init(void)
{
	unsigned int value;
	unsigned int tmp;
	unsigned int i;

	printk(KERN_INFO "EXYNOS4: Initializing architecture\n");

	/* set idle function */
	arm_pm_idle = exynos4_idle;

	/*
	 * on exynos4x12, CMU reset system power register should to be set 0x0
	 */
	if (!soc_is_exynos4210()) {
		for (i = 0; i < ARRAY_SIZE(exynos4_pmu_init_zero); i++)
			__raw_writel(0x0, exynos4_pmu_init_zero[i]);
	}

	/* set sw_reset function */
	s5p_reset_hook = exynos4_sw_reset;

	/* Disable auto wakeup from power off mode */
	for (i = 0; i < num_possible_cpus(); i++) {
		tmp = __raw_readl(S5P_ARM_CORE_OPTION(i));
		tmp &= ~S5P_CORE_OPTION_DIS;
		__raw_writel(tmp, S5P_ARM_CORE_OPTION(i));
	}

	if (soc_is_exynos4212() || soc_is_exynos4412()) {
		value = __raw_readl(S5P_AUTOMATIC_WDT_RESET_DISABLE);
		value &= ~S5P_SYS_WDTRESET;
		__raw_writel(value, S5P_AUTOMATIC_WDT_RESET_DISABLE);
		value = __raw_readl(S5P_MASK_WDT_RESET_REQUEST);
		value &= ~S5P_SYS_WDTRESET;
		__raw_writel(value, S5P_MASK_WDT_RESET_REQUEST);
	}

	return device_register(&exynos4_dev);
}
