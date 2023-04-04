/*
 *  linux/device/i9300/arch/arm/mm/mmu.c
 *
 *  Copyright (C) 1995-2005 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <asm/mach/map.h>

extern void __init create_mapping(struct map_desc *md);

/*
 * Create the architecture specific mappings
 */
void __init iotable_init_legacy(struct map_desc *io_desc, int nr)
{
	int i;

	for (i = 0; i < nr; i++)
		create_mapping(io_desc + i);
}
