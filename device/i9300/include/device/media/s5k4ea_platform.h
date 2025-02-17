/* linux/include/media/s5k4ea_platform.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Driver for S5K4EA from Samsung Electronics
 * CMOS Image Sensor SoC with an Embedded Image Processor
 * supporting MIPI CSI-2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/device.h>
#include <device/media/v4l2-mediabus.h>

struct s5k4ea_platform_data {
	unsigned int default_width;
	unsigned int default_height;
	unsigned int pixelformat;
	int freq;	/* MCLK in KHz */

	/* This SoC supports Parallel & CSI-2 */
	int is_mipi;
};

struct s5k4ea_mbus_platform_data {
	int id;
	struct v4l2_mbus_framefmt fmt;
	unsigned int bus_width;
	unsigned long clk_rate;	/* master clock frequency in Hz */
	int (*set_power)(int on);
	int (*set_clock)(struct device *dev, int on);
};
