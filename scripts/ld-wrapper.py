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
    "arch/arm/mm/built-in.o" :
    [{
        "config": "CONFIG_DMA_CMA",
        "injected_objects":
        [
            "device/i9300/arch/arm/mm/init-cma.o",
            "device/i9300/arch/arm/mm/dma-mapping-cma.o",
            "device/i9300/arch/arm/mm/mmu-cma.o",
        ],
        "removed_objects":
        [
           "arch/arm/mm/init.o",
           "arch/arm/mm/dma-mapping.o",
           "arch/arm/mm/mmu.o",
        ]
    }],
    "drivers/gpu/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/gpu/built-in.o",
        ],
    }],
    "drivers/usb/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/usb/built-in.o",
        ],
    }],
    "drivers/tty/serial/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/tty/serial/built-in.o",
        ],
        "removed_objects":
        [
            "drivers/tty/serial/samsung.o",
            "drivers/tty/serial/s5pv210.o",
        ],
    }],
    "drivers/built-in.o" :
    [{
        "injected_objects":
        [
            "device/i9300/drivers/samsung/built-in.o",
        ],
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
