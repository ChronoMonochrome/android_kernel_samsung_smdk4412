/* fsmgr_helper.c
**
** Android helper providing fstab file to fsmgr
**
** Copyright (C) 2019
**
** Shilin Victor <chrono.monochrome@gmail.com>
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

static char fstab_smdk4x12[2048] =
"# Android fstab file.\n"
"# <src>						<mnt_point>		<type>		<mnt_flags and options>		<fs_mgr_flags>\n"
"# The filesystem that contains the filesystem checker binary (typically /system) cannot\n"
"# specify MF_CHECK, and must come before any filesystems that do specify MF_CHECK\n"
"/dev/block/platform/dw_mmc/by-name/EFS			/efs			ext4		noatime,nosuid,nodev,journal_async_commit,errors=panicwait\n"
"/dev/block/platform/dw_mmc/by-name/SYSTEM		/			ext4		ro,noatime		wait\n"
"/dev/block/platform/dw_mmc/by-name/CACHE		/cache			f2fs		noatime,discard,inline_xattr,inline_data,nosuid,nodevwait\n"
"/dev/block/platform/dw_mmc/by-name/CACHE		/cache			ext4		noatime,nosuid,nodev,journal_async_commit,errors=panicwait\n"
"/dev/block/platform/dw_mmc/by-name/HIDDEN		/preload		ext4		noatime,nosuid,nodev,journal_async_commit		wait\n"
"/dev/block/platform/dw_mmc/by-name/USERDATA		/data			f2fs		noatime,discard,inline_xattr,inline_data,nosuid,nodevwait,check,encryptable=footer\n"
"/dev/block/platform/dw_mmc/by-name/USERDATA		/data			ext4		noatime,nosuid,nodev,noauto_da_alloc,journal_async_commit,errors=panic		wait,check,encryptable=footer\n"
"/dev/block/platform/dw_mmc/by-name/OTA 			/misc 				emmc		defaults					defaults \n"
"# vold-managed volumes (\"block device\" is actually a sysfs devpath)\n"
"/devices/platform/s3c-sdhci.2/mmc_host/mmc1*/mmcblk1		auto		auto		defaults		voldmanaged=sdcard1:auto,encryptable=userdata\n"
"/devices/platform/s5p-ehci*					auto		auto		defaults		voldmanaged=usb:auto\n"
"# recovery\n"
"/dev/block/platform/dw_mmc/by-name/BOOT			/boot				emmc		defaults		recoveryonly\n"
"/dev/block/platform/dw_mmc/by-name/RECOVERY		/recovery			emmc		defaults		recoveryonly\n"
"/dev/block/platform/dw_mmc/by-name/RADIO		/modem				emmc		defaults		recoveryonly\n"
"# zram\n"
"/dev/block/zram0			none				swap		defaults		zramsize=314572800,zramstreams=2\n";

module_param_string(fstab_smdk4x12, fstab_smdk4x12, sizeof(fstab_smdk4x12), 0644);

/*
static char image_type[MAX_IMAGE_LENGTH + 1] = "mono";
module_param_string(image_type, image_type, sizeof (image_type), 0);
*/
