/*
 *  midas_wm1811.c
 *
 *  Copyright (c) 2011 Samsung Electronics Co. Ltd
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <device/linux/gpio.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/input.h>
#include <linux/wakelock.h>
#include <linux/suspend.h>

#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/jack.h>

#include <mach/regs-clock.h>
#include <mach/pmu.h>
#include <mach/midas-sound.h>

#include <linux/mfd/wm8994/core.h>
#include <linux/mfd/wm8994/registers.h>
#include <linux/mfd/wm8994/pdata.h>
#include <linux/mfd/wm8994/gpio.h>

#if defined(CONFIG_SND_USE_MUIC_SWITCH)
#include <linux/mfd/max77693-private.h>
#endif


#include "i2s.h"
#include "s3c-i2s-v2.h"
#include "../codecs/wm8994.h"


#define MIDAS_DEFAULT_MCLK1	24000000
#define MIDAS_DEFAULT_MCLK2	32768
#define MIDAS_DEFAULT_SYNC_CLK	11289600

#define WM1811_JACKDET_MODE_NONE  0x0000
#define WM1811_JACKDET_MODE_JACK  0x0100
#define WM1811_JACKDET_MODE_MIC   0x0080
#define WM1811_JACKDET_MODE_AUDIO 0x0180

#define WM1811_JACKDET_BTN0	0x04
#define WM1811_JACKDET_BTN1	0x10
#define WM1811_JACKDET_BTN2	0x08

#define JACK_ADC_CH		3
#define JACK_SAMPLE_SIZE	5

#define MAX_ZONE_LIMIT		10
/* keep this value if you support double-pressed concept */
#define WAKE_LOCK_TIME		(HZ * 5)	/* 5 sec */
#define EAR_CHECK_LOOP_CNT	10

struct wm1811_machine_priv {
	struct snd_soc_jack jack;
	struct snd_soc_codec *codec;
	struct wake_lock jackdet_wake_lock;
	void (*lineout_switch_f) (int on);
	void (*set_main_mic_f) (int on);
	void (*set_sub_mic_f) (int on);
	int (*get_g_det_value_f) (void);
	int (*get_g_det_irq_num_f) (void);
};

static struct wm8958_micd_rate midas_det_rates[] = {
	{ MIDAS_DEFAULT_MCLK2,     true,  0,  0 },
	{ MIDAS_DEFAULT_MCLK2,    false,  0,  0 },
	{ MIDAS_DEFAULT_SYNC_CLK,  true,  7,  7 },
	{ MIDAS_DEFAULT_SYNC_CLK, false,  7,  7 },
};

static struct wm8958_micd_rate midas_jackdet_rates[] = {
	{ MIDAS_DEFAULT_MCLK2,     true,  0,  0 },
	{ MIDAS_DEFAULT_MCLK2,    false,  0,  0 },
	{ MIDAS_DEFAULT_SYNC_CLK,  true, 12, 12 },
	{ MIDAS_DEFAULT_SYNC_CLK, false,  7,  8 },
};

static int aif2_mode;
const char *aif2_mode_text[] = {
	"Slave", "Master"
};

static struct platform_device *midas_snd_device;

static void midas_gpio_init(void)
{
	int err;
#ifdef CONFIG_SND_SOC_USE_EXTERNAL_MIC_BIAS
	/* Main Microphone BIAS */
	err = gpio_request(GPIO_MIC_BIAS_EN, "MAIN MIC");
	if (err) {
		pr_err(KERN_ERR "MIC_BIAS_EN GPIO set error!\n");
		return;
	}
	gpio_direction_output(GPIO_MIC_BIAS_EN, 1);
	gpio_set_value(GPIO_MIC_BIAS_EN, 0);
	gpio_free(GPIO_MIC_BIAS_EN);
#endif

#ifdef CONFIG_SND_USE_SUB_MIC
	/* Sub Microphone BIAS */
	err = gpio_request(GPIO_SUB_MIC_BIAS_EN, "SUB MIC");
	if (err) {
		pr_err(KERN_ERR "SUB_MIC_BIAS_EN GPIO set error!\n");
		return;
	}
	gpio_direction_output(GPIO_SUB_MIC_BIAS_EN, 1);
	gpio_set_value(GPIO_SUB_MIC_BIAS_EN, 0);
	gpio_free(GPIO_SUB_MIC_BIAS_EN);
#endif

#ifdef CONFIG_FM_RADIO
	/* FM/Third Mic GPIO */
	err = gpio_request(GPIO_FM_MIC_SW, "GPL0");
	if (err) {
		pr_err(KERN_ERR "FM/THIRD_MIC Switch GPIO set error!\n");
		return;
	}
	gpio_direction_output(GPIO_FM_MIC_SW, 1);
	gpio_set_value(GPIO_FM_MIC_SW, 0);
	gpio_free(GPIO_FM_MIC_SW);
#endif
}

static const struct soc_enum aif2_mode_enum[] = {
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(aif2_mode_text), aif2_mode_text),
};

static int get_aif2_mode(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	ucontrol->value.integer.value[0] = aif2_mode;
	return 0;
}

static int set_aif2_mode(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	if (aif2_mode == ucontrol->value.integer.value[0])
		return 0;

	aif2_mode = ucontrol->value.integer.value[0];

	pr_info("set aif2 mode : %s\n", aif2_mode_text[aif2_mode]);

	return 0;
}

static int midas_ext_micbias(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	dev_dbg(codec->dev, "%s event is %02X", w->name, event);

#ifdef CONFIG_SND_SOC_USE_EXTERNAL_MIC_BIAS
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		gpio_set_value(GPIO_MIC_BIAS_EN, 1);
		msleep(150);
		break;
	case SND_SOC_DAPM_POST_PMD:
		gpio_set_value(GPIO_MIC_BIAS_EN, 0);
		break;
	}
#endif
	return 0;
}

static int midas_ext_submicbias(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	dev_dbg(codec->dev, "%s event is %02X", w->name, event);

#ifdef CONFIG_SND_USE_SUB_MIC
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		gpio_set_value(GPIO_SUB_MIC_BIAS_EN, 1);
		msleep(150);
		break;
	case SND_SOC_DAPM_POST_PMD:
		gpio_set_value(GPIO_SUB_MIC_BIAS_EN, 0);
		break;
	}
#endif
	return 0;
}

/*
 * midas_ext_spkmode :
 * For phone device have 1 external speaker
 * should mix LR data in a speaker mixer (mono setting)
 */
static int midas_ext_spkmode(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	int ret = 0;
#ifndef CONFIG_SND_USE_STEREO_SPEAKER
	struct snd_soc_codec *codec = w->codec;

	ret = snd_soc_update_bits(codec, WM8994_SPKOUT_MIXERS,
				  WM8994_SPKMIXR_TO_SPKOUTL_MASK,
				  WM8994_SPKMIXR_TO_SPKOUTL);
#endif
	return ret;
}

static int midas_lineout_switch(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;

	pr_err("%s: %s event is %02X", __func__, w->name, event);
#if defined(CONFIG_SND_USE_MUIC_SWITCH)
	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		msleep(150);
		max77693_muic_set_audio_switch(1);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		max77693_muic_set_audio_switch(0);
		break;
	}
#endif
	return 0;
}

static void midas_micd_set_rate(struct snd_soc_codec *codec)
{
	struct wm8994_priv *wm8994 = snd_soc_codec_get_drvdata(codec);
	int best, i, sysclk, val;
	bool idle;
	const struct wm8958_micd_rate *rates = NULL;
	int num_rates = 0;

	idle = !wm8994->jack_mic;

	sysclk = snd_soc_read(codec, WM8994_CLOCKING_1);
	if (sysclk & WM8994_SYSCLK_SRC)
		sysclk = wm8994->aifclk[1];
	else
		sysclk = wm8994->aifclk[0];

	if (wm8994->jackdet) {
		rates = midas_jackdet_rates;
		num_rates = ARRAY_SIZE(midas_jackdet_rates);
		wm8994->pdata->micd_rates = midas_jackdet_rates;
		wm8994->pdata->num_micd_rates = num_rates;
	} else {
		rates = midas_det_rates;
		num_rates = ARRAY_SIZE(midas_det_rates);
		wm8994->pdata->micd_rates = midas_det_rates;
		wm8994->pdata->num_micd_rates = num_rates;
	}

	best = 0;
	for (i = 0; i < num_rates; i++) {
		if (rates[i].idle != idle)
			continue;
		if (abs(rates[i].sysclk - sysclk) <
		    abs(rates[best].sysclk - sysclk))
			best = i;
		else if (rates[best].idle != idle)
			best = i;
	}

	val = rates[best].start << WM8958_MICD_BIAS_STARTTIME_SHIFT
		| rates[best].rate << WM8958_MICD_RATE_SHIFT;

	snd_soc_update_bits(codec, WM8958_MIC_DETECT_1,
			    WM8958_MICD_BIAS_STARTTIME_MASK |
			    WM8958_MICD_RATE_MASK, val);
}

static int midas_wm1811_aif1_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	unsigned int pll_out;
	int ret;

	dev_info(codec_dai->dev, "%s ++\n", __func__);
	/* AIF1CLK should be >=3MHz for optimal performance */
	if (params_rate(params) == 8000 || params_rate(params) == 11025)
		pll_out = params_rate(params) * 512;
	else
		pll_out = params_rate(params) * 256;

	ret = snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_I2S
					| SND_SOC_DAIFMT_NB_NF
					| SND_SOC_DAIFMT_CBM_CFM);
	if (ret < 0)
		return ret;

	/* Set the cpu DAI configuration */
	ret = snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_I2S
					| SND_SOC_DAIFMT_NB_NF
					| SND_SOC_DAIFMT_CBM_CFM);
	if (ret < 0)
		return ret;

	/* Switch the FLL */
	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL1,
				  WM8994_FLL_SRC_MCLK1, MIDAS_DEFAULT_MCLK1,
				  pll_out);
	if (ret < 0)
		dev_err(codec_dai->dev, "Unable to start FLL1: %d\n", ret);

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_FLL1,
				     pll_out, SND_SOC_CLOCK_IN);
	if (ret < 0) {
		dev_err(codec_dai->dev, "Unable to switch to FLL1: %d\n", ret);
		return ret;
	}

	ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_OPCLK,
				     0, MOD_OPCLK_PCLK);
	if (ret < 0)
		return ret;

	dev_info(codec_dai->dev, "%s --\n", __func__);

	return 0;
}

/*
 * Midas WM1811 DAI operations.
 */
static struct snd_soc_ops midas_wm1811_aif1_ops = {
	.hw_params = midas_wm1811_aif1_hw_params,
};

static int midas_wm1811_aif2_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_codec *codec = rtd->codec;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	int ret;
	int prate;
	int bclk;

	dev_info(codec_dai->dev, "%s ++\n", __func__);
	prate = params_rate(params);
	switch (params_rate(params)) {
	case 8000:
	case 16000:
	       break;
	default:
		dev_warn(codec_dai->dev, "Unsupported LRCLK %d, falling back to 8000Hz\n",
				(int)params_rate(params));
		prate = 8000;
	}

	/* Set the codec DAI configuration, aif2_mode:0 is slave */
	if (aif2_mode == 0)
		ret = snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_I2S
					| SND_SOC_DAIFMT_NB_NF
					| SND_SOC_DAIFMT_CBS_CFS);
	else
		ret = snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_I2S
					| SND_SOC_DAIFMT_NB_NF
					| SND_SOC_DAIFMT_CBM_CFM);

	if (ret < 0)
		return ret;

	switch (prate) {
	case 8000:
		bclk = 256000;
		break;
	case 16000:
		bclk = 512000;
		break;
	default:
		return -EINVAL;
	}

	if (aif2_mode == 0) {
		ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL2,
					WM8994_FLL_SRC_BCLK,
					bclk, prate * 256);
	} else {
		ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL2,
					  WM8994_FLL_SRC_MCLK1,
					  MIDAS_DEFAULT_MCLK1, prate * 256);
	}

	if (ret < 0)
		dev_err(codec_dai->dev, "Unable to configure FLL2: %d\n", ret);

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_FLL2,
				     prate * 256, SND_SOC_CLOCK_IN);
	if (ret < 0)
		dev_err(codec_dai->dev, "Unable to switch to FLL2: %d\n", ret);

	if (!(snd_soc_read(codec, WM8994_INTERRUPT_RAW_STATUS_2)
		& WM8994_FLL2_LOCK_STS)) {
		dev_info(codec_dai->dev, "%s: use mclk1 for FLL2\n", __func__);
		ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL2,
			WM8994_FLL_SRC_MCLK1,
			MIDAS_DEFAULT_MCLK1, prate * 256);
	}

	dev_info(codec_dai->dev, "%s --\n", __func__);
	return 0;
}

static struct snd_soc_ops midas_wm1811_aif2_ops = {
	.hw_params = midas_wm1811_aif2_hw_params,
};

static int midas_wm1811_aif3_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *params)
{
	pr_err("%s: enter\n", __func__);
	return 0;
}

static struct snd_soc_ops midas_wm1811_aif3_ops = {
	.hw_params = midas_wm1811_aif3_hw_params,
};

static const struct snd_kcontrol_new midas_controls[] = {
	SOC_DAPM_PIN_SWITCH("HP"),
	SOC_DAPM_PIN_SWITCH("SPK"),
	SOC_DAPM_PIN_SWITCH("RCV"),
	SOC_DAPM_PIN_SWITCH("FM In"),
	SOC_DAPM_PIN_SWITCH("LINE"),
	SOC_DAPM_PIN_SWITCH("HDMI"),
	SOC_DAPM_PIN_SWITCH("Main Mic"),
	SOC_DAPM_PIN_SWITCH("Sub Mic"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),

	SOC_ENUM_EXT("AIF2 Mode", aif2_mode_enum[0],
		get_aif2_mode, set_aif2_mode),
};

const struct snd_soc_dapm_widget midas_dapm_widgets[] = {
	SND_SOC_DAPM_HP("HP", NULL),
	SND_SOC_DAPM_SPK("SPK", midas_ext_spkmode),
	SND_SOC_DAPM_SPK("RCV", NULL),
	SND_SOC_DAPM_LINE("LINE", midas_lineout_switch),
	SND_SOC_DAPM_LINE("HDMI", NULL),

	SND_SOC_DAPM_MIC("Headset Mic", NULL),
	SND_SOC_DAPM_MIC("Main Mic", midas_ext_micbias),
	SND_SOC_DAPM_MIC("Sub Mic", midas_ext_submicbias),
	SND_SOC_DAPM_LINE("FM In", NULL),
};

const struct snd_soc_dapm_route midas_dapm_routes[] = {
	{ "HP", NULL, "HPOUT1L" },
	{ "HP", NULL, "HPOUT1R" },

	{ "SPK", NULL, "SPKOUTLN" },
	{ "SPK", NULL, "SPKOUTLP" },
	{ "SPK", NULL, "SPKOUTRN" },
	{ "SPK", NULL, "SPKOUTRP" },

	{ "RCV", NULL, "HPOUT2N" },
	{ "RCV", NULL, "HPOUT2P" },
	{ "LINE", NULL, "LINEOUT2N" },
	{ "LINE", NULL, "LINEOUT2P" },
	{ "HDMI", NULL, "LINEOUT1N" },
	{ "HDMI", NULL, "LINEOUT1P" },

	{ "IN1LP", NULL, "MICBIAS1" },
	{ "IN1LN", NULL, "MICBIAS1" },
	{ "MICBIAS1", NULL, "Main Mic" },

	{ "IN1RP", NULL, "Sub Mic" },
	{ "IN1RN", NULL, "Sub Mic" },

	{ "IN2LP:VXRN", NULL, "MICBIAS2" },
	{ "MICBIAS2", NULL, "Headset Mic" },

	{ "IN2RN", NULL, "FM In" },
	{ "IN2RP:VXRP", NULL, "FM In" },
};

static struct snd_soc_dai_driver midas_ext_dai[] = {
	{
		.name = "midas.cp",
		.playback = {
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 16000,
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000,
			.formats = SNDRV_PCM_FMTBIT_S16_LE,
		},
		.capture = {
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 16000,
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000,
			.formats = SNDRV_PCM_FMTBIT_S16_LE,
		},
	},
	{
		.name = "midas.bt",
		.playback = {
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 16000,
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000,
			.formats = SNDRV_PCM_FMTBIT_S16_LE,
		},
		.capture = {
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 16000,
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000,
			.formats = SNDRV_PCM_FMTBIT_S16_LE,
		},
	},
};

static int midas_wm1811_init_paiftx(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_codec *codec = rtd->codec;
	struct wm1811_machine_priv *wm1811
		= snd_soc_card_get_drvdata(codec->card);
	struct snd_soc_dai *aif1_dai = rtd->codec_dai;
	struct wm8994 *control = codec->control_data;
	struct wm8994_priv *wm8994 = snd_soc_codec_get_drvdata(codec);
	int ret;

	midas_snd_set_mclk(true, false);

	rtd->codec_dai->driver->playback.channels_max =
				rtd->cpu_dai->driver->playback.channels_max;

	ret = snd_soc_add_controls(codec, midas_controls,
					ARRAY_SIZE(midas_controls));

	ret = snd_soc_dapm_new_controls(&codec->dapm, midas_dapm_widgets,
					   ARRAY_SIZE(midas_dapm_widgets));
	if (ret != 0)
		dev_err(codec->dev, "Failed to add DAPM widgets: %d\n", ret);

	ret = snd_soc_dapm_add_routes(&codec->dapm, midas_dapm_routes,
					   ARRAY_SIZE(midas_dapm_routes));
	if (ret != 0)
		dev_err(codec->dev, "Failed to add DAPM routes: %d\n", ret);

	ret = snd_soc_dai_set_sysclk(aif1_dai, WM8994_SYSCLK_MCLK2,
				     MIDAS_DEFAULT_MCLK2, SND_SOC_CLOCK_IN);
	if (ret < 0)
		dev_err(codec->dev, "Failed to boot clocking\n");

	/* Force AIF1CLK on as it will be master for jack detection */
	if (wm8994->revision > 1) {
		ret = snd_soc_dapm_force_enable_pin(&codec->dapm, "AIF1CLK");
		if (ret < 0)
			dev_err(codec->dev, "Failed to enable AIF1CLK: %d\n",
					ret);
	}

	snd_soc_dapm_ignore_suspend(&codec->dapm, "RCV");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "SPK");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "HP");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "Headset Mic");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "Sub Mic");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "Main Mic");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "AIF1DACDAT");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "AIF2DACDAT");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "AIF3DACDAT");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "AIF1ADCDAT");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "AIF2ADCDAT");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "AIF3ADCDAT");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "FM In");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "LINE");
	snd_soc_dapm_ignore_suspend(&codec->dapm, "HDMI");

	wm1811->codec = codec;

	midas_micd_set_rate(codec);

	wm1811->jack.status = 0;

	ret = snd_soc_jack_new(codec, "Midas Jack",
				SND_JACK_HEADSET | SND_JACK_BTN_0 |
				SND_JACK_BTN_1 | SND_JACK_BTN_2,
				&wm1811->jack);

	if (ret < 0)
		dev_err(codec->dev, "Failed to create jack: %d\n", ret);

	ret = snd_jack_set_key(wm1811->jack.jack, SND_JACK_BTN_0, KEY_MEDIA);

	if (ret < 0)
		dev_err(codec->dev, "Failed to set KEY_MEDIA: %d\n", ret);

	ret = snd_jack_set_key(wm1811->jack.jack, SND_JACK_BTN_1,
							KEY_VOLUMEUP);
	if (ret < 0)
		dev_err(codec->dev, "Failed to set KEY_VOLUMEUP: %d\n", ret);

	ret = snd_jack_set_key(wm1811->jack.jack, SND_JACK_BTN_2,
							KEY_VOLUMEDOWN);

	if (ret < 0)
		dev_err(codec->dev, "Failed to set KEY_VOLUMEDOWN: %d\n", ret);

	if (wm8994->revision > 1) {
		dev_info(codec->dev, "wm1811: Rev %c support mic detection\n",
			'A' + wm8994->revision);
		ret = wm8958_mic_detect(codec, &wm1811->jack, NULL,
					NULL, NULL, NULL);

		if (ret < 0)
			dev_err(codec->dev, "Failed start detection: %d\n",
				ret);
	} else {
		dev_info(codec->dev, "wm1811: Rev %c doesn't support mic detection\n",
			'A' + wm8994->revision);
		codec->dapm.idle_bias_off = 0;
	}
	/* To wakeup for earjack event in suspend mode */
	enable_irq_wake(control->irq);

	wake_lock_init(&wm1811->jackdet_wake_lock,
					WAKE_LOCK_SUSPEND, "midas_jackdet");

	return snd_soc_dapm_sync(&codec->dapm);
}

static struct snd_soc_dai_link midas_dai[] = {
	{ /* Sec_Fifo DAI i/f */
		.name = "Sec_FIFO TX",
		.stream_name = "Sec_Dai",
		.cpu_dai_name = "samsung-i2s.4",
		.codec_dai_name = "wm8994-aif1",
		.platform_name = "samsung-audio-idma",
		.codec_name = "wm8994-codec",
		.init = midas_wm1811_init_paiftx,
		.ops = &midas_wm1811_aif1_ops,
	},
	{
		.name = "Midas_WM1811 Voice",
		.stream_name = "Voice Tx/Rx",
		.cpu_dai_name = "midas.cp",
		.codec_dai_name = "wm8994-aif2",
		.platform_name = "snd-soc-dummy",
		.codec_name = "wm8994-codec",
		.ops = &midas_wm1811_aif2_ops,
		.ignore_suspend = 1,
	},
	{
		.name = "Midas_WM1811 BT",
		.stream_name = "BT Tx/Rx",
		.cpu_dai_name = "midas.bt",
		.codec_dai_name = "wm8994-aif3",
		.platform_name = "snd-soc-dummy",
		.codec_name = "wm8994-codec",
		.ops = &midas_wm1811_aif3_ops,
		.ignore_suspend = 1,
	},
	{ /* Primary DAI i/f */
		.name = "WM8994 AIF1",
		.stream_name = "Pri_Dai",
		.cpu_dai_name = "samsung-i2s.0",
		.codec_dai_name = "wm8994-aif1",
		.platform_name = "samsung-audio",
		.codec_name = "wm8994-codec",
		.ops = &midas_wm1811_aif1_ops,
	},
};

static int midas_card_suspend_pre(struct snd_soc_card *card)
{
	struct snd_soc_codec *codec = card->rtd->codec;
	struct wm8994_priv *wm8994 = snd_soc_codec_get_drvdata(codec);

	return 0;
}

static int midas_card_suspend_post(struct snd_soc_card *card)
{
	struct snd_soc_codec *codec = card->rtd->codec;
	struct snd_soc_dai *aif1_dai = card->rtd[0].codec_dai;
	struct snd_soc_dai *aif2_dai = card->rtd[1].codec_dai;
	int ret;

	if (!codec->active) {
		ret = snd_soc_dai_set_sysclk(aif2_dai,
					     WM8994_SYSCLK_MCLK2,
					     MIDAS_DEFAULT_MCLK2,
					     SND_SOC_CLOCK_IN);

		if (ret < 0)
			dev_err(codec->dev, "Unable to switch to MCLK2: %d\n",
				ret);

		ret = snd_soc_dai_set_pll(aif2_dai, WM8994_FLL2, 0, 0, 0);

		if (ret < 0)
			dev_err(codec->dev, "Unable to stop FLL2\n");

		ret = snd_soc_dai_set_sysclk(aif1_dai,
					     WM8994_SYSCLK_MCLK2,
					     MIDAS_DEFAULT_MCLK2,
					     SND_SOC_CLOCK_IN);
		if (ret < 0)
			dev_err(codec->dev, "Unable to switch to MCLK2\n");

		ret = snd_soc_dai_set_pll(aif1_dai, WM8994_FLL1, 0, 0, 0);

		if (ret < 0)
			dev_err(codec->dev, "Unable to stop FLL1\n");

		midas_snd_set_mclk(false, true);
	}

	return 0;
}

static int midas_card_resume_pre(struct snd_soc_card *card)
{
	struct snd_soc_codec *codec = card->rtd->codec;
	struct snd_soc_dai *aif1_dai = card->rtd[0].codec_dai;
	int ret;

	midas_snd_set_mclk(true, false);

	/* Switch the FLL */
	ret = snd_soc_dai_set_pll(aif1_dai, WM8994_FLL1,
				  WM8994_FLL_SRC_MCLK1,
				  MIDAS_DEFAULT_MCLK1,
				  MIDAS_DEFAULT_SYNC_CLK);

	if (ret < 0)
		dev_err(aif1_dai->dev, "Unable to start FLL1: %d\n", ret);

	/* Then switch AIF1CLK to it */
	ret = snd_soc_dai_set_sysclk(aif1_dai,
				     WM8994_SYSCLK_FLL1,
				     MIDAS_DEFAULT_SYNC_CLK,
				     SND_SOC_CLOCK_IN);

	if (ret < 0)
		dev_err(aif1_dai->dev, "Unable to switch to FLL1: %d\n", ret);

	return 0;
}

static int midas_card_resume_post(struct snd_soc_card *card)
{
	struct snd_soc_codec *codec = card->rtd->codec;
	struct wm8994_priv *wm8994 = snd_soc_codec_get_drvdata(codec);
	int reg = 0;

	/* workaround for jack detection
	 * sometimes WM8994_GPIO_1 type changed wrong function type
	 * so if type mismatched, update to IRQ type
	 */
	reg = snd_soc_read(codec, WM8994_GPIO_1);

	if ((reg & WM8994_GPN_FN_MASK) != WM8994_GP_FN_IRQ) {
		dev_err(codec->dev, "%s: GPIO1 type 0x%x\n", __func__, reg);
		snd_soc_write(codec, WM8994_GPIO_1, WM8994_GP_FN_IRQ);
	}

	return 0;
}

static struct snd_soc_card midas = {
	.name = "Midas_WM1811",
	.dai_link = midas_dai,

	/* If you want to use sec_fifo device,
	 * changes the num_link = 2 or ARRAY_SIZE(midas_dai). */
	.num_links = ARRAY_SIZE(midas_dai),

	.suspend_post = midas_card_suspend_post,
	.resume_pre = midas_card_resume_pre,
	.suspend_pre = midas_card_suspend_pre,
	.resume_post = midas_card_resume_post
};

static int __init midas_audio_init(void)
{
	struct wm1811_machine_priv *wm1811;
	int ret;

	wm1811 = kzalloc(sizeof *wm1811, GFP_KERNEL);
	if (!wm1811) {
		pr_err("Failed to allocate memory\n");
		ret = -ENOMEM;
		goto err_kzalloc;
	}
	snd_soc_card_set_drvdata(&midas, wm1811);

	midas_snd_device = platform_device_alloc("soc-audio", -1);
	if (!midas_snd_device) {
		ret = -ENOMEM;
		goto err_device_alloc;
	}

	ret = snd_soc_register_dais(&midas_snd_device->dev, midas_ext_dai,
						ARRAY_SIZE(midas_ext_dai));
	if (ret != 0)
		pr_err("Failed to register external DAIs: %d\n", ret);

	platform_set_drvdata(midas_snd_device, &midas);

	ret = platform_device_add(midas_snd_device);
	if (ret)
		platform_device_put(midas_snd_device);

	midas_gpio_init();

	return ret;

err_device_alloc:
	kfree(wm1811);
err_kzalloc:
	return ret;
}
module_init(midas_audio_init);

static void __exit midas_audio_exit(void)
{
	struct snd_soc_card *card = &midas;
	struct wm1811_machine_priv *wm1811 = snd_soc_card_get_drvdata(card);
	platform_device_unregister(midas_snd_device);
	kfree(wm1811);
}
module_exit(midas_audio_exit);

MODULE_AUTHOR("JS. Park <aitdark.park@samsung.com>");
MODULE_DESCRIPTION("ALSA SoC Midas WM1811");
MODULE_LICENSE("GPL");
