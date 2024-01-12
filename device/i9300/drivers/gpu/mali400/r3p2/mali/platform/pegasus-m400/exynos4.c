/* drivers/gpu/mali400/mali/platform/pegasus-m400/exynos4.c
 *
 * Copyright 2011 by S.LSI. Samsung Electronics Inc.
 * San#24, Nongseo-Dong, Giheung-Gu, Yongin, Korea
 *
 * Samsung SoC Mali400 DVFS driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software FoundatIon.
 */

/**
 * @file exynos4.c
 * Platform specific Mali driver functions for the exynos 4XXX based platforms
 */
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/pm.h>
#include <device/linux/suspend.h>

#ifdef CONFIG_PM_RUNTIME
#include <linux/pm_runtime.h>
#endif

#ifdef CONFIG_MALI_DVFS
#include "mali_kernel_utilization.h"
#endif /* CONFIG_MALI_DVFS */

#include <linux/mali/mali_utgard.h>
#include "mali_kernel_common.h"
#include "mali_kernel_linux.h"
#include "mali_pm.h"

#include <plat/pd.h>

#include "exynos4_pmm.h"

extern struct platform_device exynos4_device_pd[];
static void mali_platform_device_release(struct device *device);

/* This is for the Odroid boards */
#define MALI_BASE_IRQ 182

#define MALI_GP_IRQ	   MALI_BASE_IRQ + 9
#define MALI_PP0_IRQ	  MALI_BASE_IRQ + 5
#define MALI_PP1_IRQ	  MALI_BASE_IRQ + 6
#define MALI_PP2_IRQ	  MALI_BASE_IRQ + 7
#define MALI_PP3_IRQ	  MALI_BASE_IRQ + 8
#define MALI_GP_MMU_IRQ   MALI_BASE_IRQ + 4
#define MALI_PP0_MMU_IRQ  MALI_BASE_IRQ + 0
#define MALI_PP1_MMU_IRQ  MALI_BASE_IRQ + 1
#define MALI_PP2_MMU_IRQ  MALI_BASE_IRQ + 2
#define MALI_PP3_MMU_IRQ  MALI_BASE_IRQ + 3

static struct resource mali_gpu_resources[] =
{
	MALI_GPU_RESOURCES_MALI400_MP4(0x13000000,
								   MALI_GP_IRQ, MALI_GP_MMU_IRQ,
								   MALI_PP0_IRQ, MALI_PP0_MMU_IRQ,
								   MALI_PP1_IRQ, MALI_PP1_MMU_IRQ,
								   MALI_PP2_IRQ, MALI_PP2_MMU_IRQ,
								   MALI_PP3_IRQ, MALI_PP3_MMU_IRQ)
};

static struct platform_device mali_gpu_device =
{
	.name = "mali_dev", /* MALI_SEC MALI_GPU_NAME_UTGARD, */
	.id = 0,
	.dev.parent = &exynos4_device_pd[PD_G3D].dev,
	.dev.release = mali_platform_device_release,
};

static struct mali_gpu_device_data mali_gpu_data =
{
	.shared_mem_size = 256 * 1024 * 1024, /* 256MB */
	.fb_start = 0x40000000,
	.fb_size = 0xb1000000,
	.utilization_interval = 100, /* 100ms */
	.utilization_callback = mali_gpu_utilization_handler,
};

int mali_platform_device_register(void)
{
	int err;

	MALI_DEBUG_PRINT(4, ("mali_platform_device_register() called\n"));

	/* Connect resources to the device */
	err = platform_device_add_resources(&mali_gpu_device, mali_gpu_resources, sizeof(mali_gpu_resources) / sizeof(mali_gpu_resources[0]));
	if (0 == err)
	{
		err = platform_device_add_data(&mali_gpu_device, &mali_gpu_data, sizeof(mali_gpu_data));
		if (0 == err)
		{
			/* Register the platform device */
			err = platform_device_register(&mali_gpu_device);
			if (0 == err)
			{
				mali_platform_init(&(mali_gpu_device.dev));

#ifdef CONFIG_PM_RUNTIME
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
				pm_runtime_set_autosuspend_delay(&(mali_gpu_device.dev), 1000);
				pm_runtime_use_autosuspend(&(mali_gpu_device.dev));
#endif
				pm_runtime_enable(&(mali_gpu_device.dev));
#endif

				return 0;
			}
		}
		platform_device_unregister(&mali_gpu_device);
	}

	return err;
}

void mali_platform_device_unregister(void)
{
	MALI_DEBUG_PRINT(4, ("mali_platform_device_unregister() called\n"));

	mali_platform_deinit(&(mali_gpu_device.dev));

	platform_device_unregister(&mali_gpu_device);
}

static void mali_platform_device_release(struct device *device)
{
	MALI_DEBUG_PRINT(4, ("mali_platform_device_release() called\n"));
}
