/* doze_helper.c
**
** Android Doze powesaving helper module
**
** Copyright (C) 2016
**
** Yaroslav Zvezda <acroreiser@gmail.com>
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/fb.h>
#include <linux/notifier.h>
#include <linux/kmod.h>

static unsigned int fb_suspended;
static struct notifier_block fb_notif;

static bool doze_hlp = true;
static bool restrict_sensors = true;

static char * envp[] = { "HOME=/", NULL };
static char * argv1[] = { "dumpsys", "deviceidle", "force-idle", "deep", NULL };
static char * argv2[] = { "dumpsys", "deviceidle", "unforce", NULL };
static char * argv3[] = { "dumpsys", "sensorservice", "restrict", NULL };
static char * argv4[] = { "dumpsys", "sensorservice", "enable", NULL };

static void turn_doze(bool trigger)
{
	if(trigger)
	{
		printk("doze_hlp: entering Doze\n");
		call_usermodehelper("/system/bin/dumpsys", argv1, envp, UMH_WAIT_EXEC);
		if(restrict_sensors)
			call_usermodehelper("/system/bin/dumpsys", argv3, envp, UMH_WAIT_EXEC);

	}
	else
	{
		call_usermodehelper("/system/bin/dumpsys", argv2, envp, UMH_WAIT_EXEC);
		if(restrict_sensors)
			call_usermodehelper("/system/bin/dumpsys", argv4, envp, UMH_WAIT_EXEC);

		printk("doze_hlp: exiting Doze\n");
	}
}

static void doze_hlp_fb_suspend(void)
{
	if (fb_suspended)
		return;

	if (doze_hlp)
		turn_doze(true);

	fb_suspended = 1;
}

static void doze_hlp_fb_resume(void)
{
	if (!fb_suspended)
		return;

	if (doze_hlp)
		turn_doze(false);

	fb_suspended = 0;
}

static int fb_notifier_callback(struct notifier_block *self,
                               unsigned long event, void *data)
{
       struct fb_event *evdata = data;
       int *blank;
       if (evdata && evdata->data) {
               if (event == FB_EVENT_BLANK) {
                       blank = evdata->data;
                       switch (*blank) {
                               case FB_BLANK_UNBLANK:
                               case FB_BLANK_NORMAL:
                               case FB_BLANK_VSYNC_SUSPEND:
                               case FB_BLANK_HSYNC_SUSPEND:
                                       doze_hlp_fb_suspend();
                                       break;
                               default:
                               case FB_BLANK_POWERDOWN:
                                       doze_hlp_fb_resume();
                                       break;
                       }
               }
       }

       return 0;
}

static int doze_hlp_init(void)
{
	fb_suspended = 0;
	fb_notif.notifier_call = fb_notifier_callback;
	fb_register_client(&fb_notif);

	return 0;
}

static void doze_hlp_exit(void)
{
	fb_unregister_client(&fb_notif);
}
module_param(doze_hlp, bool, 0644);
module_param(restrict_sensors, bool, 0644);

module_init(doze_hlp_init);
module_exit(doze_hlp_exit);

MODULE_LICENSE("GPL");

