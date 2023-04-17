/*
 *  linux/arch/arm/mm/proc-v7.S
 *
 *  Copyright (C) 2001 Deep Blue Solutions Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  This is the "shell" of the ARMv7 processor support.
 */
#include <linux/init.h>
#include <linux/linkage.h>
#include <asm/assembler.h>
#include <asm/asm-offsets.h>
#include <asm/hwcap.h>
#include <asm/pgtable-hwdef.h>
#include <asm/pgtable.h>

#include "proc-macros.S"
#include "proc-v7-2level.S"

/* Suspend/resume support: derived from arch/arm/mach-s5pv210/sleep.S */
.globl	cpu_v7_suspend_size_legacy
.equ	cpu_v7_suspend_size_legacy, 4 * 9
#ifdef CONFIG_ARM_CPU_SUSPEND
ENTRY(cpu_v7_do_suspend_legacy)
	stmfd	sp!, {r4 - r11, lr}
	mrc	p15, 0, r4, c13, c0, 0	@ FCSE/PID
	mrc	p15, 0, r5, c13, c0, 1	@ Context ID
	mrc	p15, 0, r6, c13, c0, 3	@ User r/o thread ID
	stmia	r0!, {r4 - r6}
	mrc	p15, 0, r6, c3, c0, 0	@ Domain ID
	mrc	p15, 0, r7, c2, c0, 0	@ TTB 0
	mrc	p15, 0, r8, c2, c0, 1	@ TTB 1
	mrc	p15, 0, r9, c1, c0, 0	@ Control register
	mrc	p15, 0, r10, c1, c0, 1	@ Auxiliary control register
	mrc	p15, 0, r11, c1, c0, 2	@ Co-processor access control
	stmia	r0, {r6 - r11}
	ldmfd	sp!, {r4 - r11, pc}
ENDPROC(cpu_v7_do_suspend_legacy)

ENTRY(cpu_v7_do_resume_legacy)
	mov	ip, #0
	mcr	p15, 0, ip, c8, c7, 0	@ invalidate TLBs
	mcr	p15, 0, ip, c7, c5, 0	@ invalidate I cache
	ldmia	r0!, {r4 - r6}
	mcr	p15, 0, r4, c13, c0, 0	@ FCSE/PID
	mcr	p15, 0, r5, c13, c0, 1	@ Context ID
	mcr	p15, 0, r6, c13, c0, 3	@ User r/o thread ID
	ldmia	r0, {r6 - r11}
	mcr	p15, 0, r6, c3, c0, 0	@ Domain ID
	mcr	p15, 0, r7, c2, c0, 0	@ TTB 0
	mcr	p15, 0, r8, c2, c0, 1	@ TTB 1
	mcr	p15, 0, ip, c2, c0, 2	@ TTB control register
	mrc	p15, 0, r4, c1, c0, 1	@ Read Auxiliary control register
	teq	r4, r10			@ Is it already set?
	mcrne	p15, 0, r10, c1, c0, 1	@ No, so write it
	mcr	p15, 0, r11, c1, c0, 2	@ Co-processor access control
	ldr	r4, =PRRR		@ PRRR
	ldr	r5, =NMRR		@ NMRR
	mcr	p15, 0, r4, c10, c2, 0	@ write PRRR
	mcr	p15, 0, r5, c10, c2, 1	@ write NMRR
	isb
	dsb
	mov	r0, r9			@ control register
	mov	r2, r7, lsr #14		@ get TTB0 base
	mov	r2, r2, lsl #14
	ldr	r3, cpu_resume_l1_flags
	b	cpu_resume_mmu
ENDPROC(cpu_v7_do_resume_legacy)
cpu_resume_l1_flags:
	ALT_SMP(.long PMD_TYPE_SECT | PMD_SECT_AP_WRITE | PMD_FLAGS_SMP)
	ALT_UP(.long  PMD_TYPE_SECT | PMD_SECT_AP_WRITE | PMD_FLAGS_UP)
#endif
