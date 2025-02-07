/* linux/arch/arm/mach-exynos/setup-sdhci-gpio.c
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS4 - Helper functions for setting up SDHCI device(s) GPIO (HSMMC)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <device/linux/gpio.h>
#include <device/linux/mmc/host.h>
#include <device/linux/mmc/card.h>

#include <plat/gpio-cfg.h>
#include <plat/regs-sdhci.h>
#include <plat/sdhci.h>

extern int s3c_gpio_slp_cfgpin(unsigned int pin, unsigned int config);
extern int s3c_gpio_slp_setpull_updown(unsigned int pin, unsigned int config);

#if defined(CONFIG_ARCH_EXYNOS4)
void exynos4_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK0[0:1] pins to special-function 2 */
	for (gpio = EXYNOS4_GPK0(0); gpio < EXYNOS4_GPK0(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	switch (width) {
	case 8:
		for (gpio = EXYNOS4_GPK1(3); gpio <= EXYNOS4_GPK1(6); gpio++) {
			/* Data pin GPK1[3:6] to special-function 3 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	case 4:
		for (gpio = EXYNOS4_GPK0(3); gpio <= EXYNOS4_GPK0(6); gpio++) {
			/* Data pin GPK0[3:6] to special-function 2 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	default:
		break;
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS4_GPK0(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPK0(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}

void exynos4_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK1[0:1] pins to special-function 2 */
	for (gpio = EXYNOS4_GPK1(0); gpio < EXYNOS4_GPK1(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	for (gpio = EXYNOS4_GPK1(3); gpio <= EXYNOS4_GPK1(6); gpio++) {
		/* Data pin GPK1[3:6] to special-function 2 */
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS4_GPK1(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPK1(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}

void exynos4_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK2[0:1] pins to special-function 2 */
	for (gpio = EXYNOS4_GPK2(0); gpio < EXYNOS4_GPK2(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
#if defined(CONFIG_MACH_U1) || defined(CONFIG_MACH_TRATS)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV3);
#elif defined(CONFIG_MACH_MIDAS)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#else
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#endif
	}

	switch (width) {
	case 8:
		for (gpio = EXYNOS4_GPK3(3); gpio <= EXYNOS4_GPK3(6); gpio++) {
			/* Data pin GPK3[3:6] to special-function 3 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
#if defined(CONFIG_MACH_U1) || defined(CONFIG_MACH_TRATS)
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV3);
#elif defined(CONFIG_MACH_MIDAS)
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#else
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#endif
		}
	case 4:
		for (gpio = EXYNOS4_GPK2(3); gpio <= EXYNOS4_GPK2(6); gpio++) {
			/* Data pin GPK2[3:6] to special-function 2 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
#if defined(CONFIG_MACH_U1) || defined(CONFIG_MACH_TRATS)
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV3);
#elif defined(CONFIG_MACH_MIDAS)
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#else
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#endif
		}
	default:
		break;
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS4_GPK2(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPK2(2), S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV2);
	}
}

void exynos4_setup_sdhci3_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

#if defined(CONFIG_WIMAX_CMC)
	if (gpio_get_value(GPIO_WIMAX_EN)) {
		for (gpio = EXYNOS4_GPK3(0); gpio < EXYNOS4_GPK3(2); gpio++) {
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV2);
		}
		for (gpio = EXYNOS4_GPK3(3); gpio <= EXYNOS4_GPK3(6); gpio++) {
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV2);
		}
		for (gpio = EXYNOS4_GPK3(0); gpio < EXYNOS4_GPK3(2); gpio++) {
			s3c_gpio_slp_cfgpin(gpio, S3C_GPIO_SLP_INPUT);
			s3c_gpio_slp_setpull_updown(gpio, S3C_GPIO_PULL_NONE);
		}
		for (gpio = EXYNOS4_GPK3(3); gpio <= EXYNOS4_GPK3(6); gpio++) {
			s3c_gpio_slp_cfgpin(gpio, S3C_GPIO_SLP_INPUT);
			s3c_gpio_slp_setpull_updown(gpio, S3C_GPIO_PULL_NONE);
		}
	} else {
		for (gpio = EXYNOS4_GPK3(0); gpio < EXYNOS4_GPK3(2); gpio++) {
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(0));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_DOWN);
		}
		for (gpio = EXYNOS4_GPK3(3); gpio <= EXYNOS4_GPK3(6); gpio++) {
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(0));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_DOWN);
		}
		for (gpio = EXYNOS4_GPK3(0); gpio < EXYNOS4_GPK3(2); gpio++) {
			s3c_gpio_slp_cfgpin(gpio, S3C_GPIO_SLP_INPUT);
			s3c_gpio_slp_setpull_updown(gpio, S3C_GPIO_PULL_DOWN);
		}
		for (gpio = EXYNOS4_GPK3(3); gpio <= EXYNOS4_GPK3(6); gpio++) {
			s3c_gpio_slp_cfgpin(gpio, S3C_GPIO_SLP_INPUT);
			s3c_gpio_slp_setpull_updown(gpio, S3C_GPIO_PULL_DOWN);
		}
	}
#else
	/* Set all the necessary GPK3[0:1] pins to special-function 2 */
	for (gpio = EXYNOS4_GPK3(0); gpio < EXYNOS4_GPK3(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
#if defined(CONFIG_MACH_U1) || defined(CONFIG_MACH_TRATS)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV2);
#elif defined(CONFIG_MACH_M0) || defined(CONFIG_MACH_C1_USA_ATT) || \
	defined(CONFIG_MACH_T0) || defined(CONFIG_MACH_M3)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV2);
#elif defined(CONFIG_MACH_MIDAS)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#elif defined(CONFIG_MACH_PX)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#else
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#endif
	}

#if defined(CONFIG_MACH_PX)
	s3c_gpio_setpull(EXYNOS4_GPK3(1), S3C_GPIO_PULL_UP);
#endif

	for (gpio = EXYNOS4_GPK3(3); gpio <= EXYNOS4_GPK3(6); gpio++) {
		/* Data pin GPK3[3:6] to special-function 2 */
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
#if defined(CONFIG_MACH_U1) || defined(CONFIG_MACH_TRATS)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV2);
#elif defined(CONFIG_MACH_M0) || defined(CONFIG_MACH_C1_USA_ATT) || \
	defined(CONFIG_MACH_T0) || defined(CONFIG_MACH_M3)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV2);
#elif defined(CONFIG_MACH_MIDAS)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#elif defined(CONFIG_MACH_PX)
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#else
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
#endif
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS4_GPK3(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS4_GPK3(2), S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV2);
	}
#endif
}

#endif /* CONFIG_ARCH_EXYNOS4 */

#if defined(CONFIG_ARCH_EXYNOS5)
void exynos5_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPC0[0:1] pins to special-function 2 */
	for (gpio = EXYNOS5_GPC0(0); gpio < EXYNOS5_GPC0(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	switch (width) {
	case 8:
		for (gpio = EXYNOS5_GPC1(3); gpio <= EXYNOS5_GPC1(6); gpio++) {
			/* Data pin GPK1[3:6] to special-function 3 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	case 4:
		for (gpio = EXYNOS5_GPC0(3); gpio <= EXYNOS5_GPC0(6); gpio++) {
			/* Data pin GPK0[3:6] to special-function 2 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	default:
		break;
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS5_GPC0(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS5_GPC0(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}

void exynos5_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK1[0:1] pins to special-function 2 */
	for (gpio = EXYNOS5_GPC1(0); gpio < EXYNOS5_GPC1(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	for (gpio = EXYNOS5_GPC1(3); gpio <= EXYNOS5_GPC1(6); gpio++) {
		/* Data pin GPK1[3:6] to special-function 2 */
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS5_GPC1(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS5_GPC1(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}

void exynos5_setup_sdhci2_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK2[0:1] pins to special-function 2 */
	for (gpio = EXYNOS5_GPC2(0); gpio < EXYNOS5_GPC2(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	switch (width) {
	case 8:
		for (gpio = EXYNOS5_GPC3(3); gpio <= EXYNOS5_GPC3(6); gpio++) {
			/* Data pin GPK3[3:6] to special-function 3 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	case 4:
		for (gpio = EXYNOS5_GPC2(3); gpio <= EXYNOS5_GPC2(6); gpio++) {
			/* Data pin GPK2[3:6] to special-function 2 */
			s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
			s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
			s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
		}
	default:
		break;
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS5_GPC2(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS5_GPC2(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}

void exynos5_setup_sdhci3_cfg_gpio(struct platform_device *dev, int width)
{
	struct s3c_sdhci_platdata *pdata = dev->dev.platform_data;
	unsigned int gpio;

	/* Set all the necessary GPK3[0:1] pins to special-function 2 */
	for (gpio = EXYNOS5_GPC3(0); gpio < EXYNOS5_GPC3(2); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	for (gpio = EXYNOS5_GPC3(3); gpio <= EXYNOS5_GPC3(6); gpio++) {
		/* Data pin GPK3[3:6] to special-function 2 */
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}

	if (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) {
		s3c_gpio_cfgpin(EXYNOS5_GPC3(2), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(EXYNOS5_GPC3(2), S3C_GPIO_PULL_UP);
		s5p_gpio_set_drvstr(gpio, S5P_GPIO_DRVSTR_LV4);
	}
}

#endif /* CONFIG_ARCH_EXYNOS5 */
