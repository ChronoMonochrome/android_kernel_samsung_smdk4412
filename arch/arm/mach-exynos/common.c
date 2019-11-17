/*
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Common Codes for EXYNOS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/irqchip.h>
#include <linux/io.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/serial_core.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/of_irq.h>
#include <linux/export.h>
#include <linux/irqdomain.h>
#include <linux/irqchip.h>
#include <linux/of_address.h>
#include <linux/irqchip/arm-gic.h>
#include <linux/irqchip/chained_irq.h>

#include <asm/proc-fns.h>
#include <asm/exception.h>
#include <asm/hardware/cache-l2x0.h>
#include <asm/system_misc.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>
#include <asm/mmu-legacy.h>
#include <asm/cacheflush.h>
#include <asm/system_misc.h>

#include <mach/regs-irq.h>
#include <mach/regs-pmu.h>
#include <mach/regs-gpio.h>
#include <mach/smc.h>

#include <plat/reset.h>
#include <plat/audio.h>
#include <plat/cpu.h>
#include <plat/exynos4.h>
#include <plat/exynos5.h>
#include <plat/clock.h>
#include <plat/devs.h>
#include <plat/pm.h>
#include <plat/mshci.h>
#include <plat/sdhci.h>
#include <plat/gpio-cfg.h>
#include <plat/adc-core.h>
#include <plat/fb-core.h>
#include <plat/fimc-core.h>
#include <plat/iic-core.h>
#include <plat/tv-core.h>
#include <plat/spi-core.h>
#include <plat/regs-serial.h>
#include <plat/rtc-core.h>

#include "common.h"

#define L2_AUX_VAL 0x7C470001
#define L2_AUX_MASK 0xC200ffff

static const char name_exynos4210[] = "EXYNOS4210";
static const char name_exynos4212[] = "EXYNOS4212";
static const char name_exynos4412[] = "EXYNOS4412";
static const char name_exynos5210[] = "EXYNOS5210";
static const char name_exynos5250[] = "EXYNOS5250";
static const char name_exynos5440[] = "EXYNOS5440";

static struct cpu_table cpu_ids[] __initdata = {
	{
		.idcode		= EXYNOS4210_CPU_ID,
		.idmask		= EXYNOS4_CPU_MASK,
		.map_io		= exynos4_map_io,
		.init_clocks	= exynos4_init_clocks,
		.init_uarts	= exynos4_init_uarts,
		.init		= exynos4_init,
		.name		= name_exynos4210,
	}, {
		.idcode		= EXYNOS4212_CPU_ID,
		.idmask		= EXYNOS4_CPU_MASK,
		.map_io		= exynos4_map_io,
		.init_clocks	= exynos4_init_clocks,
		.init_uarts	= exynos4_init_uarts,
		.init		= exynos4_init,
		.name		= name_exynos4212,
	}, {
		.idcode		= EXYNOS4412_CPU_ID,
		.idmask		= EXYNOS4_CPU_MASK,
		.map_io		= exynos4_map_io,
		.init_clocks	= exynos4_init_clocks,
		.init_uarts	= exynos4_init_uarts,
		.init		= exynos4_init,
		.name		= name_exynos4412,

	}, {
		.idcode         = EXYNOS5210_CPU_ID,
		.idmask         = EXYNOS4_CPU_MASK,
		.map_io         = exynos5_map_io,
		.init_clocks    = exynos5_init_clocks,
		.init_uarts     = exynos5_init_uarts,
		.init           = exynos5_init,
		.name           = name_exynos5210,
	}, {
		.idcode         = EXYNOS5250_SOC_ID,
		.idmask         = EXYNOS4_CPU_MASK,
		.map_io         = exynos5_map_io,
		.init_clocks    = exynos5_init_clocks,
		.init_uarts     = exynos5_init_uarts,
		.init           = exynos5_init,
		.name           = name_exynos5250,
	}, {
		.idcode		= EXYNOS5440_SOC_ID,
		.idmask		= EXYNOS5_SOC_MASK,
		.map_io		= exynos5_map_io,
		.init_clocks    = exynos5_init_clocks,
		.init_uarts     = exynos5_init_uarts,
		.init		= exynos5_init,
		.name		= name_exynos5440,
	},
};

/* minimal IO mapping */

static struct map_desc s5p_iodesc[] __initdata = {
	{
		.virtual	= (unsigned long)S5P_VA_CHIPID,
		.pfn		= __phys_to_pfn(S5P_PA_CHIPID),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S3C_VA_SYS,
		.pfn		= __phys_to_pfn(S5P_PA_SYSCON),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S3C_VA_TIMER,
		.pfn		= __phys_to_pfn(S5P_PA_TIMER),
		.length		= SZ_16K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S3C_VA_WATCHDOG,
		.pfn		= __phys_to_pfn(S3C_PA_WDT),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_SROMC,
		.pfn		= __phys_to_pfn(S5P_PA_SROMC),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S3C_VA_HSPHY,
		.pfn		= __phys_to_pfn(S5P_PA_HSPHY),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

/* read cpu identification code */

unsigned long cpu_idcode;
void __init s5p_init_io(struct map_desc *mach_desc,
			int size, void __iomem *cpuid_addr)
{
	/* initialize the io descriptors we need for initialization */
	iotable_init_legacy(s5p_iodesc, ARRAY_SIZE(s5p_iodesc));
	if (mach_desc)
		iotable_init_legacy(mach_desc, size);

	/* detect cpu id and rev. */
	s5p_init_cpu(cpuid_addr);

	s3c_init_cpu(samsung_cpu_id, cpu_ids, ARRAY_SIZE(cpu_ids));
}

/* Initial IO mappings */
static struct map_desc exynos4_iodesc[] __initdata = {
	{
		.virtual	= (unsigned long)S5P_VA_SYSTIMER,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_SYSTIMER),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_CMU,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_CMU),
		.length		= SZ_128K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_PMU,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_PMU),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_COMBINER_BASE,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_COMBINER),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_COREPERI_BASE,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_COREPERI),
		.length		= SZ_8K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_L2CC,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_L2CC),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_GPIO1,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_GPIO1),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_GPIO2,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_GPIO2),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_GPIO3,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_GPIO3),
		.length		= SZ_256,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_GPIO4,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_GPIO4),
		.length		= SZ_256,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S3C_VA_UART,
		.pfn		= __phys_to_pfn(S3C_PA_UART),
		.length		= SZ_512K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_SROMC,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_SROMC),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S3C_VA_USB_HSPHY,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_HSPHY),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_GIC_CPU,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_GIC_CPU),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_GIC_DIST,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_GIC_DIST),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	}, {
		.virtual        = (unsigned long)S5P_VA_AUDSS,
		.pfn            = __phys_to_pfn(EXYNOS4_PA_AUDSS),
		.length         = SZ_4K,
		.type           = MT_DEVICE,
	}, {
		.virtual        = (unsigned long)S5P_VA_PPMU_CPU,
		.pfn            = __phys_to_pfn(EXYNOS4_PA_PPMU_CPU),
		.length         = SZ_8K,
		.type           = MT_DEVICE,
	}, {
		.virtual        = (unsigned long)S5P_VA_PPMU_DMC0,
		.pfn            = __phys_to_pfn(EXYNOS4_PA_PPMU_DMC0),
		.length         = SZ_8K,
		.type           = MT_DEVICE,
	}, {
		.virtual        = (unsigned long)S5P_VA_PPMU_DMC1,
		.pfn            = __phys_to_pfn(EXYNOS4_PA_PPMU_DMC1),
		.length         = SZ_8K,
		.type           = MT_DEVICE,
	}, {
		.virtual        = (unsigned long)S5P_VA_GDL,
		.pfn            = __phys_to_pfn(EXYNOS4_PA_GDL),
		.length         = SZ_4K,
		.type           = MT_DEVICE,
	}, {
		.virtual        = (unsigned long)S5P_VA_GDR,
		.pfn            = __phys_to_pfn(EXYNOS4_PA_GDR),
		.length         = SZ_4K,
		.type           = MT_DEVICE,
	},
};

static struct map_desc exynos4210_iodesc[] __initdata = {
	{
		.virtual	= (unsigned long)S5P_VA_DMC0,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_DMC0),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_DMC1,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_DMC1),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_SYSRAM_NS,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_SYSRAM_NS),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

static struct map_desc exynos4210_iodesc_rev_0[] __initdata = {
	{
		.virtual	= (unsigned long)S5P_VA_SYSRAM,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_SYSRAM0),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

static struct map_desc exynos4210_iodesc_rev_1[] __initdata = {
	{
		.virtual	= (unsigned long)S5P_VA_SYSRAM,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_SYSRAM1),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

static struct map_desc exynos4212_iodesc[] __initdata = {
	{
		.virtual	= (unsigned long)S5P_VA_DMC0,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_DMC0_4212),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_DMC1,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_DMC1_4212),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_SYSRAM,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_SYSRAM1),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_SYSRAM_NS,
		.pfn		= __phys_to_pfn(EXYNOS4_PA_SYSRAM_NS_4212),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

void __init exynos_cpufreq_init(void)
{
	platform_device_register_simple("exynos-cpufreq", -1, NULL, 0);
}

#if 0
void exynos4_restart(char mode, const char *cmd)
{
	__raw_writel(0x1, S5P_SWRESET);
}

void exynos5_restart(char mode, const char *cmd)
{
	u32 val;
	void __iomem *addr;

	if (of_machine_is_compatible("samsung,exynos5250")) {
		val = 0x1;
		addr = EXYNOS_SWRESET;
	} else if (of_machine_is_compatible("samsung,exynos5440")) {
		val = (0x10 << 20) | (0x1 << 16);
		addr = EXYNOS5440_SWRESET;
	} else {
		pr_err("%s: cannot support non-DT\n", __func__);
		return;
	}

	__raw_writel(val, addr);
}

void __init exynos_init_late(void)
{
	if (of_machine_is_compatible("samsung,exynos5440"))
		/* to be supported later */
		return;

	exynos_pm_late_initcall();
}
#endif

/*
 * exynos4_map_io
 *
 * register the standard cpu IO areas
 */
void __init exynos4_map_io(void)
{
	iotable_init_legacy(exynos4_iodesc, ARRAY_SIZE(exynos4_iodesc));

	if (soc_is_exynos4210()) {
		iotable_init_legacy(exynos4210_iodesc, ARRAY_SIZE(exynos4210_iodesc));
		if (samsung_rev() == EXYNOS4210_REV_0)
			iotable_init_legacy(exynos4210_iodesc_rev_0,
				ARRAY_SIZE(exynos4210_iodesc_rev_0));
		else
			iotable_init_legacy(exynos4210_iodesc_rev_1,
				ARRAY_SIZE(exynos4210_iodesc_rev_1));
	} else {
		iotable_init_legacy(exynos4212_iodesc, ARRAY_SIZE(exynos4212_iodesc));
	}

#ifdef CONFIG_S3C_DEV_HSMMC
	exynos4_default_sdhci0();
#endif
#ifdef CONFIG_S3C_DEV_HSMMC1
	exynos4_default_sdhci1();
#endif
#ifdef CONFIG_S3C_DEV_HSMMC2
	exynos4_default_sdhci2();
#endif
#ifdef CONFIG_S3C_DEV_HSMMC3
	exynos4_default_sdhci3();
#endif
#ifdef CONFIG_EXYNOS4_DEV_MSHC
	exynos4_default_mshci();
#endif
	exynos4_i2sv3_setup_resource();

	s3c_fimc_setname(0, "exynos4-fimc");
	s3c_fimc_setname(1, "exynos4-fimc");
	s3c_fimc_setname(2, "exynos4-fimc");
	s3c_fimc_setname(3, "exynos4-fimc");
#ifdef CONFIG_S3C_DEV_RTC
	s3c_rtc_setname("exynos-rtc");
#endif
#ifdef CONFIG_FB_S3C
	s5p_fb_setname(0, "exynos4-fb");	/* FIMD0 */
#endif
	if (soc_is_exynos4210())
		s3c_adc_setname("samsung-adc-v3");
	else
		s3c_adc_setname("samsung-adc-v4");

	s5p_hdmi_setname("exynos4-hdmi");

	/* The I2C bus controllers are directly compatible with s3c2440 */
	s3c_i2c0_setname("s3c2440-i2c");
	s3c_i2c1_setname("s3c2440-i2c");
	s3c_i2c2_setname("s3c2440-i2c");

#ifdef CONFIG_S5P_DEV_ACE
	s5p_ace_setname("exynos-ace");
#endif
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

unsigned int gic_bank_offset __read_mostly;

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

static void exynos4_idle(void)
{
	if (!need_resched())
		cpu_do_idle();

	local_irq_enable();
}

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

static struct s3c24xx_uart_clksrc exynos_serial_clocks[] = {
	[0] = {
		.name		= "uclk1",
		.divisor	= 1,
		.min_baud	= 0,
		.max_baud	= 0,
	},
};

/* uart registration process */
void __init exynos_common_init_uarts(struct s3c2410_uartcfg *cfg, int no)
{
	struct s3c2410_uartcfg *tcfg = cfg;
	u32 ucnt;

	for (ucnt = 0; ucnt < no; ucnt++, tcfg++) {
		if (!tcfg->clocks) {
			tcfg->has_fracval = 1;
			tcfg->clocks = exynos_serial_clocks;
			tcfg->clocks_size = ARRAY_SIZE(exynos_serial_clocks);
		}
		tcfg->flags |= NO_NEED_CHECK_CLKSRC;
	}

	s3c24xx_init_uartdevs("s5pv210-uart", exynos4_uart_resources, cfg, no);
}

static DEFINE_SPINLOCK(eint_lock);

static unsigned int eint0_15_data[16];

static unsigned int eint0_15_src_int[16] = {
	EXYNOS4_IRQ_EINT0, EXYNOS4_IRQ_EINT1, EXYNOS4_IRQ_EINT2, EXYNOS4_IRQ_EINT3,
	EXYNOS4_IRQ_EINT4, EXYNOS4_IRQ_EINT5, EXYNOS4_IRQ_EINT6, EXYNOS4_IRQ_EINT7,
	EXYNOS4_IRQ_EINT8, EXYNOS4_IRQ_EINT9, EXYNOS4_IRQ_EINT10, EXYNOS4_IRQ_EINT11,
	EXYNOS4_IRQ_EINT12, EXYNOS4_IRQ_EINT13, EXYNOS4_IRQ_EINT14, EXYNOS4_IRQ_EINT15,
};

static inline void exynos_irq_eint_mask(struct irq_data *data)
{
	u32 mask;

	spin_lock(&eint_lock);
	mask = __raw_readl(S5P_EINT_MASK(EINT_REG_NR(data->irq)));
	mask |= eint_irq_to_bit(data->irq);
	__raw_writel(mask, S5P_EINT_MASK(EINT_REG_NR(data->irq)));
	spin_unlock(&eint_lock);
}

static void exynos_irq_eint_unmask(struct irq_data *data)
{
	u32 mask;

	spin_lock(&eint_lock);
	mask = __raw_readl(S5P_EINT_MASK(EINT_REG_NR(data->irq)));
	mask &= ~(eint_irq_to_bit(data->irq));
	__raw_writel(mask, S5P_EINT_MASK(EINT_REG_NR(data->irq)));
	spin_unlock(&eint_lock);
}

static inline void exynos_irq_eint_ack(struct irq_data *data)
{
	__raw_writel(eint_irq_to_bit(data->irq),
		     S5P_EINT_PEND(EINT_REG_NR(data->irq)));
}

static void exynos_irq_eint_maskack(struct irq_data *data)
{
	exynos_irq_eint_mask(data);
	exynos_irq_eint_ack(data);
}

static int exynos_irq_eint_set_type(struct irq_data *data, unsigned int type)
{
	int offs = EINT_OFFSET(data->irq);
	int shift;
	u32 ctrl, mask;
	u32 newvalue = 0;
	struct irq_desc *desc = irq_to_desc(data->irq);

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		newvalue = S5P_IRQ_TYPE_EDGE_RISING;
		break;

	case IRQ_TYPE_EDGE_FALLING:
		newvalue = S5P_IRQ_TYPE_EDGE_FALLING;
		break;

	case IRQ_TYPE_EDGE_BOTH:
		newvalue = S5P_IRQ_TYPE_EDGE_BOTH;
		break;

	case IRQ_TYPE_LEVEL_LOW:
		newvalue = S5P_IRQ_TYPE_LEVEL_LOW;
		break;

	case IRQ_TYPE_LEVEL_HIGH:
		newvalue = S5P_IRQ_TYPE_LEVEL_HIGH;
		break;

	case IRQ_TYPE_NONE:
		printk(KERN_DEBUG "None irq type\n");
		break;

	default:
		printk(KERN_ERR "No such irq type %d", type);
		return -EINVAL;
	}

	shift = (offs & 0x7) * 4;
	mask = 0x7 << shift;

	spin_lock(&eint_lock);
	ctrl = __raw_readl(S5P_EINT_CON(EINT_REG_NR(data->irq)));
	ctrl &= ~mask;
	ctrl |= newvalue << shift;
	__raw_writel(ctrl, S5P_EINT_CON(EINT_REG_NR(data->irq)));
	spin_unlock(&eint_lock);

	switch (offs) {
	case 0 ... 7:
		s3c_gpio_cfgpin(EINT_GPIO_0(offs & 0x7), EINT_MODE);
		break;
	case 8 ... 15:
		s3c_gpio_cfgpin(EINT_GPIO_1(offs & 0x7), EINT_MODE);
		break;
	case 16 ... 23:
		s3c_gpio_cfgpin(EINT_GPIO_2(offs & 0x7), EINT_MODE);
		break;
	case 24 ... 31:
		s3c_gpio_cfgpin(EINT_GPIO_3(offs & 0x7), EINT_MODE);
		break;
	default:
		printk(KERN_ERR "No such irq number %d", offs);
	}

	if (type & IRQ_TYPE_EDGE_BOTH)
		desc->handle_irq = handle_edge_irq;
	else
		desc->handle_irq = handle_level_irq;

	return 0;
}

static struct irq_chip exynos_irq_eint = {
	.name		= "exynos-eint",
	.irq_mask	= exynos_irq_eint_mask,
	.irq_unmask	= exynos_irq_eint_unmask,
	.irq_mask_ack	= exynos_irq_eint_maskack,
	.irq_disable	= exynos_irq_eint_maskack,
	.irq_ack	= exynos_irq_eint_ack,
	.irq_set_type	= exynos_irq_eint_set_type,
#ifdef CONFIG_PM
	.irq_set_wake	= s3c_irqext_wake,
#endif
};

/* exynos_irq_demux_eint
 *
 * This function demuxes the IRQ from from EINTs 16 to 31.
 * It is designed to be inlined into the specific handler
 * s5p_irq_demux_eintX_Y.
 *
 * Each EINT pend/mask registers handle eight of them.
 */
static inline u32 exynos_irq_demux_eint(unsigned int start)
{
	unsigned int irq;

	u32 status = __raw_readl(S5P_EINT_PEND(EINT_REG_NR(start)));
	u32 mask = __raw_readl(S5P_EINT_MASK(EINT_REG_NR(start)));
	u32 action = 0;

	status &= ~mask;
	status &= 0xff;

	while (status) {
		irq = fls(status) - 1;
		generic_handle_irq(irq + start);
		status &= ~(1 << irq);
		++action;
	}

	return action;
}

static void exynos_irq_demux_eint16_31(unsigned int irq, struct irq_desc *desc)
{
	struct irq_chip *chip = irq_get_chip(irq);
	u32 a16_23, a24_31;

	chained_irq_enter(chip, desc);
	a16_23 = exynos_irq_demux_eint(IRQ_EINT(16));
	a24_31 = exynos_irq_demux_eint(IRQ_EINT(24));
	chained_irq_exit(chip, desc);

	if (!a16_23 && !a24_31)
		do_bad_IRQ(irq, desc);
}

static void exynos_irq_eint0_15(unsigned int irq, struct irq_desc *desc)
{
	u32 *irq_data = irq_get_handler_data(irq);
	struct irq_chip *chip = irq_get_chip(irq);

	chained_irq_enter(chip, desc);
	generic_handle_irq(*irq_data);
	chained_irq_exit(chip, desc);
}

int __init exynos_init_irq_eint(void)
{
	int irq;

	for (irq = 0 ; irq <= 31 ; irq++) {
		irq_set_chip_and_handler(IRQ_EINT(irq), &exynos_irq_eint,
					 handle_level_irq);
		set_irq_flags(IRQ_EINT(irq), IRQF_VALID);
	}

	irq_set_chained_handler(EXYNOS4_IRQ_EINT16_31, exynos_irq_demux_eint16_31);

	for (irq = 0 ; irq <= 15 ; irq++) {
		eint0_15_data[irq] = IRQ_EINT(irq);

		irq_set_handler_data(eint0_15_src_int[irq],
				     &eint0_15_data[irq]);
		irq_set_chained_handler(eint0_15_src_int[irq],
					exynos_irq_eint0_15);
	}

	return 0;
}

arch_initcall(exynos_init_irq_eint);
