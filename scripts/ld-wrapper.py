#! /usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of The Linux Foundation nor
#       the names of its contributors may be used to endorse or promote
#       products derived from this software without specific prior written
#       permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Invoke ld, check if we are linking built-in.o, and add the necessary
# object files in the corresponding device-specific directory

import errno
import re
import os
import sys
import subprocess

# Capture the name of the object file, can find it.
ofile = None

additional_build_rules = {
    "arch/arm/common/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/arch/arm/common/pl330.o",
            "device/i9300/lib/bitmap.o",
            "device/i9300/lib/genalloc.o",
        ],
    }],
    "arch/arm/kernel/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/arch/arm/kernel/idiv_emulate.o",
            "device/i9300/arch/arm/kernel/smp.o",
        ],
    }],
    "kernel/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/kernel/freezer.o",
            "device/i9300/kernel/cgroup_freezer.o",
            "device/i9300/kernel/irq/built-in.o",
            "device/i9300/kernel/power/built-in.o",
        ],
        "removed_objects":
        [
           "kernel/cgroup_freezer.o",
           "kernel/freezer.o",
           "kernel/power/built-in.o",
        ]
    }],
    "mm/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/mm/built-in.o",
        ],
        "removed_objects":
        [
            "device/i9300/mm/ashmem.o",
        ],
    }],
    "drivers/base/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/base/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/base/iommu.o",
            "drivers/base/s5p-iommu.o",
            "drivers/base/sync.o",
            "drivers/base/sw_sync.o",
            "drivers/base/platform.o",
            "drivers/base/power/built-in.o",
        ],
    }],
    "drivers/char/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/char/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/char/mem.o",
        ],
    }],
    "drivers/cpufreq/built-in.o" :
    [{
        "removed_objects":
        [
            "drivers/cpufreq/exynos-cpufreq.o",
        ],
    }],
    "drivers/gpio/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/gpio/gpiolib.o",
            "device/i9300/drivers/gpio/gpio-exynos4.o",
            "device/i9300/drivers/gpio/gpio-plat-samsung.o",
        ],
        "removed_objects":
        [
            "drivers/gpio/gpiolib.o",
            "drivers/gpio/gpio-exynos4.o",
            "drivers/gpio/gpio-plat-samsung.o",
        ],
    }],
    "drivers/gpu/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/gpu/built-in.o",
        ],
    }],
    "drivers/i2c/busses/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/i2c/busses/i2c-s3c2410.o",
        ],
        "removed_objects":
        [
            "drivers/i2c/busses/i2c-s3c2410.o",
        ],
    }],
    "drivers/input/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/input/keyboard/gpio_keys.o",
            "device/i9300/drivers/input/keyboard/cypress/built-in.o",
            "device/i9300/drivers/input/misc/built-in.o",
            "device/i9300/drivers/input/touchscreen/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/input/keyboard/gpio_keys.o",
        ],
    }],
    "drivers/media/video/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/media/video/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/media/video/exynos/built-in.o",
            "drivers/media/video/mhl/built-in.o",
            "drivers/media/video/samsung/built-in.o",
            "drivers/media/video/s5c73m3.o",
            "drivers/media/video/s5c73m3_spi.o",
            "drivers/media/video/videodev.o",
            "drivers/media/video/v4l2-mem2mem.o",
            "drivers/media/video/videobuf-core.o",
            "drivers/media/video/videobuf2-core.o",
            "drivers/media/video/videobuf2-dma-contig.o",
        ],
    }],
    "drivers/mfd/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/mfd/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/mfd/wm8994-core.o",
            "drivers/mfd/wm8994-irq.o",
            "drivers/mfd/max77686.o",
            "drivers/mfd/max77693.o",
            "drivers/mfd/max77686-irq.o",
            "drivers/mfd/max77693-irq.o",
        ],
    }],
    "drivers/misc/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/misc/built-in.o",
        ],
        "removed_objects":
        [
            "device/i9300/drivers/misc/uid_cputime.o",
            "device/i9300/drivers/misc/uid_stat.o",
        ],
    }],
    "drivers/mmc/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/mmc/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/mmc/core/built-in.o",
            "drivers/mmc/card/built-in.o",
            "drivers/mmc/host/built-in.o",
        ],
    }],
    "drivers/nfc/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/nfc/built-in.o",
        ],
    }],
    "drivers/power/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/power/built-in.o",
            "device/i9300/drivers/battery/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/power/power_supply.o",
            "drivers/power/samsung_fake_battery.o",
        ],
    }],
    "drivers/regulator/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/regulator/core.o",
            "device/i9300/drivers/regulator/dummy.o",
            "device/i9300/drivers/regulator/fixed.o",
            "device/i9300/drivers/regulator/max77686.o",
            "device/i9300/drivers/regulator/max77693.o",
            "device/i9300/drivers/regulator/stub.o",
            "device/i9300/drivers/regulator/wm8994-regulator.o",
        ],
        "removed_objects":
        [
            "drivers/regulator/core.o",
            "drivers/regulator/dummy.o",
            "drivers/regulator/fixed.o",
            "drivers/regulator/wm8994-regulator.o",
        ],
    }],
    "drivers/rtc/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/rtc/alarm.o",
            "device/i9300/drivers/rtc/alarm-dev.o",
            "device/i9300/drivers/rtc/rtc-max77686.o",
            "device/i9300/drivers/rtc/rtc-s3c.o",
        ],
        "removed_objects":
        [
            "drivers/rtc/rtc-s3c.o",
        ],
    }],
    "drivers/spi/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/spi/spi_s3c64xx.o",
        ],
        "removed_objects":
        [
            "drivers/spi/spi_s3c64xx.o"
        ]
    }],
    "drivers/staging/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/staging/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/staging/android/built-in.o"
        ]
    }],
    "drivers/tty/serial/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/tty/serial/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/tty/serial/8250/built-in.o",
            "drivers/tty/serial/samsung.o",
            "drivers/tty/serial/s5pv210.o",
        ],
    }],
    "drivers/usb/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/usb/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/usb/class/built-in.o",
            "drivers/usb/core/built-in.o",
            "drivers/usb/gadget/built-in.o",
            "drivers/usb/host/built-in.o",
            "drivers/usb/misc/built-in.o",
            "drivers/usb/mon/built-in.o",
            "drivers/usb/notify/built-in.o",
            "drivers/usb/serial/built-in.o",
            "drivers/usb/storage/built-in.o",
        ]
    }],
    "drivers/video/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/video/backlight/built-in.o",
            "device/i9300/drivers/video/samsung/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/video/backlight/built-in.o"
        ]
    }],
    "drivers/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/amba/built-in.o",
            "device/i9300/drivers/leds/built-in.o",
            "device/i9300/drivers/motor/built-in.o",
            "device/i9300/drivers/net/built-in.o",
            "device/i9300/drivers/samsung/built-in.o",
            "device/i9300/drivers/sensor/built-in.o",
            "device/i9300/drivers/switch/built-in.o",
            "device/i9300/drivers/thermal/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/amba/built-in.o",
            "drivers/thermal/built-in.o"
        ],
    }],
    "net/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/net/activity_stats.o",
            "device/i9300/net/phonet/built-in.o",
        ],
        "removed_objects":
        [
            "net/activity_stats.o",
            "net/phonet/built-in.o",
        ],
    }],
    "sound/soc/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/sound/soc/codecs/built-in.o",
            "device/i9300/sound/soc/samsung/built-in.o",
        ],
        "removed_objects":
        [
            "sound/soc/codecs/built-in.o",
            "sound/soc/samsung/built-in.o",
        ]
    }],
}

# Check if the config is enabled
def check_config(s_config):
    CONFIG_FILE = ".config"

    if not os.path.isfile(CONFIG_FILE):
        print("Could not locate config file %s, giving up!" % CONFIG_FILE)
        sys.exit(1)

    config = open(CONFIG_FILE, "r").read()
    return config.find("%s=y" % s_config) > 0 or config.find("%s=m" % s_config) > 0

def run_ld():
    args = sys.argv[1:]
    # Look for -o
    try:
        i = args.index('-o')
        global ofile
        ofile = args[i+1]
    except (ValueError, IndexError):
        pass

    ld = sys.argv[0]

    try:
        if ofile in additional_build_rules:
            build_rules = additional_build_rules[ofile]
            injected_objects = []
            removed_objects = []
            for build_rule in build_rules:
                build_config = build_rule.get("config")
                build_config_activated = True

                if build_config:
                    build_config_activated = check_config(build_config)

                if build_config_activated:
                    injected_objects += build_rule.get("injected_objects", [])
                    removed_objects += build_rule.get("removed_objects", [])

            print("linking %s: inject the following files: %s, removing %s from build" % (ofile, str(injected_objects), str(removed_objects)))
            for obj in removed_objects:
                if obj in args:
                    args.remove(obj)
            args += injected_objects

        #print(args)
        proc = subprocess.Popen(args, stderr=subprocess.PIPE)
        for line in proc.stderr:
            print(line)
        result = proc.wait()
    except OSError as e:
        result = e.errno
        if result == errno.ENOENT:
            print args[0] + ':',e.strerror
            print 'Is your PATH set correctly?'
        else:
            print ' '.join(args), str(e)

    return result

if __name__ == '__main__':
    status = run_ld()
    sys.exit(status)
