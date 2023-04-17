/*
 *  linux/arch/arm/kernel/smp.c
 *
 *  Copyright (C) 2002 ARM Limited, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/percpu.h>
#include <asm/cacheflush.h>

static void flush_all_cpu_cache(void *info)
{
	flush_cache_all();
}

void flush_all_cpu_caches(void)
{
	on_each_cpu(flush_all_cpu_cache, NULL, 1);
}
