/* linux/arch/arm/mach-exynos/irq-eint.c
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS - IRQ EINT support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/gpio.h>

#include <asm/mach/irq.h>

#include <plat/pm.h>
#include <plat/cpu.h>
#include <plat/gpio-cfg.h>

#include <mach/regs-gpio.h>

