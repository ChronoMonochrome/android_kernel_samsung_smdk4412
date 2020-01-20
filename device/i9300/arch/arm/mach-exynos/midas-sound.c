/*
 * midas-sound.c - Sound Management of MIDAS Project
 *
 *  Copyright (C) 2012 Samsung Electrnoics
 *  JS Park <aitdark.park@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/i2c.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/fixed.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/i2c-gpio.h>
#include <mach/irqs.h>
#include <mach/pmu.h>
#include <plat/iic.h>

#include <plat/gpio-cfg.h>
#include <mach/gpio-midas.h>

#ifdef CONFIG_SND_SOC_WM8994
#include <linux/mfd/wm8994/pdata.h>
#include <linux/mfd/wm8994/gpio.h>
#endif

#if defined(CONFIG_FM_SI4709_MODULE) || defined(CONFIG_FM_SI4705) || \
	defined(CONFIG_FM_SI4705_MODULE)
#include <linux/i2c/si47xx_common.h>
#endif

static bool midas_snd_mclk_enabled;

#if defined(CONFIG_FM_SI4705)
struct si47xx_info {
#if defined(CONFIG_MACH_M0) || defined(CONFIG_MACH_M0_CTC)
	int gpio_sw;
#endif
	int gpio_int;
	int gpio_rst;
} si47xx_data;

#endif

#define I2C_NUM_2MIC	6
#define I2C_NUM_CODEC	4
#define SET_PLATDATA_2MIC(i2c_pd)	s3c_i2c6_set_platdata(i2c_pd)
#define SET_PLATDATA_CODEC(i2c_pd)	s3c_i2c4_set_platdata(i2c_pd)

static DEFINE_SPINLOCK(midas_snd_spinlock);

void midas_snd_set_mclk(bool on, bool forced)
{
	static int use_cnt;

	spin_lock(&midas_snd_spinlock);

	midas_snd_mclk_enabled = on;

	if (midas_snd_mclk_enabled) {
		if (use_cnt++ == 0 || forced) {
			printk(KERN_INFO "Sound: enabled mclk\n");
			exynos4_pmu_xclkout_set(midas_snd_mclk_enabled,
							XCLKOUT_XUSBXTI);
			mdelay(10);
		}
	} else {
		if ((--use_cnt <= 0) || forced) {
			printk(KERN_INFO "Sound: disabled mclk\n");
			exynos4_pmu_xclkout_set(midas_snd_mclk_enabled,
							XCLKOUT_XUSBXTI);
			use_cnt = 0;
		}
	}

	spin_unlock(&midas_snd_spinlock);

	printk(KERN_INFO "Sound: state: %d, use_cnt: %d\n",
					midas_snd_mclk_enabled, use_cnt);
}

bool midas_snd_get_mclk(void)
{
	return midas_snd_mclk_enabled;
}

#ifdef CONFIG_SND_SOC_WM8994
/* vbatt_devices */
static struct regulator_consumer_supply vbatt_supplies[] = {
	REGULATOR_SUPPLY("LDO1VDD", NULL),
	REGULATOR_SUPPLY("SPKVDD1", NULL),
	REGULATOR_SUPPLY("SPKVDD2", NULL),
};

static struct regulator_init_data vbatt_initdata = {
	.constraints = {
		.always_on = 1,
	},
	.num_consumer_supplies = ARRAY_SIZE(vbatt_supplies),
	.consumer_supplies = vbatt_supplies,
};

static struct fixed_voltage_config vbatt_config = {
	.init_data = &vbatt_initdata,
	.microvolts = 5000000,
	.supply_name = "VBATT",
	.gpio = -EINVAL,
};

struct platform_device vbatt_device = {
	.name = "reg-fixed-voltage",
	.id = -1,
	.dev = {
		.platform_data = &vbatt_config,
	},
};

/* wm1811 ldo1 */
static struct regulator_consumer_supply wm1811_ldo1_supplies[] = {
	REGULATOR_SUPPLY("AVDD1", NULL),
};

static struct regulator_init_data wm1811_ldo1_initdata = {
	.constraints = {
		.name = "WM1811 LDO1",
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies = ARRAY_SIZE(wm1811_ldo1_supplies),
	.consumer_supplies = wm1811_ldo1_supplies,
};

/* wm1811 ldo2 */
static struct regulator_consumer_supply wm1811_ldo2_supplies[] = {
	REGULATOR_SUPPLY("DCVDD", NULL),
};

static struct regulator_init_data wm1811_ldo2_initdata = {
	.constraints = {
		.name = "WM1811 LDO2",
		.always_on = true, /* Actually status changed by LDO1 */
	},
	.num_consumer_supplies = ARRAY_SIZE(wm1811_ldo2_supplies),
	.consumer_supplies = wm1811_ldo2_supplies,
};

static struct wm8994_drc_cfg drc_value[] = {
	{
		.name = "voice call DRC",
		.regs[0] = 0x009B,
		.regs[1] = 0x0844,
		.regs[2] = 0x00E8,
		.regs[3] = 0x0210,
		.regs[4] = 0x0000,
	},
};

static struct wm8994_pdata wm1811_pdata = {
	.gpio_defaults = {
		[0] = WM8994_GP_FN_IRQ,	  /* GPIO1 IRQ output, CMOS mode */
		[7] = WM8994_GPN_DIR | WM8994_GP_FN_PIN_SPECIFIC, /* DACDAT3 */
	},

	.irq_base = IRQ_BOARD_CODEC_START,

	/* The enable is shared but assign it to LDO1 for software */
	.ldo = {
		{
			.enable = GPIO_WM8994_LDO,
			.init_data = &wm1811_ldo1_initdata,
		},
		{
			.init_data = &wm1811_ldo2_initdata,
		},
	},
	/* Apply DRC Value */
	.drc_cfgs = drc_value,
	.num_drc_cfgs = ARRAY_SIZE(drc_value),

	/* Support external capacitors*/
	.jd_ext_cap = 1,

	/* Regulated mode at highest output voltage */
	.micbias = {0x2f, 0x2b},

	.micd_lvl_sel = 0xFF,

	.ldo_ena_always_driven = true,
	.ldo_ena_delay = 30000,
	.lineout1fb = 1,
	.lineout2fb = 0,
};

static struct i2c_board_info i2c_wm1811[] __initdata = {
	{
		I2C_BOARD_INFO("wm1811", (0x34 >> 1)),	/* Audio CODEC */
		.platform_data = &wm1811_pdata,
		.irq = IRQ_EINT(30),
	},
};

#endif

#if defined(CONFIG_FM_SI4709_MODULE) || \
	defined(CONFIG_FM_SI4705_MODULE)
static void fmradio_power(int on)
{
	int err;
#if defined(CONFIG_MACH_M0) || defined(CONFIG_MACH_M0_CTC)
	gpio_set_value(si47xx_data.gpio_sw, GPIO_LEVEL_HIGH);
#endif
	if (on) {
		err = gpio_request(GPIO_FM_INT, "GPC1");
		if (err) {
			pr_err(KERN_ERR "GPIO_FM_INT GPIO set error!\n");
			return;
		}
		gpio_direction_output(GPIO_FM_INT, 1);
		gpio_set_value(si47xx_data.gpio_rst, GPIO_LEVEL_LOW);
		gpio_set_value(GPIO_FM_INT, GPIO_LEVEL_LOW);
		usleep_range(5, 10);
		gpio_set_value(si47xx_data.gpio_rst, GPIO_LEVEL_HIGH);
		usleep_range(10, 15);
		gpio_set_value(GPIO_FM_INT, GPIO_LEVEL_HIGH);

		s3c_gpio_cfgpin(GPIO_FM_INT, S3C_GPIO_SFN(0xF));
		gpio_free(GPIO_FM_INT);
	} else {
		gpio_set_value(si47xx_data.gpio_rst, GPIO_LEVEL_LOW);
	}
}

static struct si47xx_platform_data si47xx_pdata = {
	.rx_vol = {0x0, 0x13, 0x16, 0x19, 0x1C, 0x1F, 0x22, 0x25,
		0x28, 0x2B, 0x2E, 0x31, 0x34, 0x37, 0x3A, 0x3D},
	.power = fmradio_power,
};

/* I2C19 */
static struct i2c_board_info i2c_devs19_emul[] __initdata = {
#if defined(CONFIG_FM_SI4705) || defined(CONFIG_FM_SI4705_MODULE)
	{
		I2C_BOARD_INFO("Si47xx", (0x22 >> 1)),
		.platform_data = &si47xx_pdata,
#if defined(CONFIG_MACH_M0_DUOSCTC)
		.irq = IRQ_EINT(4),
#else
		.irq = IRQ_EINT(11),
#endif
	},
#endif
#ifdef CONFIG_FM_SI4709_MODULE
	{
		I2C_BOARD_INFO("Si4709", (0x20 >> 1)),
	},
#endif

};
#endif

static void m0_gpio_init(void)
{
#ifdef CONFIG_FM_SI4705
#if defined(CONFIG_MACH_M0) || defined(CONFIG_MACH_M0_CTC)
	si47xx_data.gpio_sw = GPIO_FM_MIC_SW;
#endif

	si47xx_data.gpio_rst = GPIO_FM_RST;
	s3c_gpio_setpull(GPIO_FM_INT, S3C_GPIO_PULL_UP);

	if (gpio_is_valid(si47xx_data.gpio_rst)) {
		if (gpio_request(si47xx_data.gpio_rst, "GPC1"))
			debug(KERN_ERR "Failed to request "
			"FM_RST!\n\n");
		gpio_direction_output(si47xx_data.gpio_rst, GPIO_LEVEL_LOW);
	}
#endif
}

static struct i2c_gpio_platform_data gpio_i2c_data19 = {
	.sda_pin = GPIO_FM_SDA,
	.scl_pin = GPIO_FM_SCL,
};

struct platform_device s3c_device_i2c19 = {
	.name = "i2c-gpio",
	.id = 19,
	.dev.platform_data = &gpio_i2c_data19,
};

static struct platform_device *midas_sound_devices[] __initdata = {
#if defined(CONFIG_FM_SI4709_MODULE) || \
	defined(CONFIG_FM_SI4705_MODULE)
	&s3c_device_i2c19,
#endif
};

void __init midas_sound_init(void)
{
	printk(KERN_INFO "Sound: start %s\n", __func__);

	m0_gpio_init();

	platform_add_devices(midas_sound_devices,
		ARRAY_SIZE(midas_sound_devices));

	if (system_rev != 3 && system_rev >= 0) {
		SET_PLATDATA_CODEC(NULL);
		i2c_register_board_info(I2C_NUM_CODEC, i2c_wm1811,
						ARRAY_SIZE(i2c_wm1811));
	}

#if defined(CONFIG_FM_SI4709_MODULE) || \
	defined(CONFIG_FM_SI4705_MODULE)
	i2c_register_board_info(19, i2c_devs19_emul,
				ARRAY_SIZE(i2c_devs19_emul));
#endif

}

