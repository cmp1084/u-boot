/*
 * Copyright (C) 2005-2008 Atmel Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>

#include <asm/io.h>

#include <asm/arch/clk.h>

#include <asm/arch/memory-map.h>
DECLARE_GLOBAL_DATA_PTR;
extern void flash_set_waitstate(int waitstate);
/* Rewrite from scratch 20100716 Mjan */
//~ #include <pm.h>

//~ void clk_init(void)
//~ {
	//~ /* From power on reset we are running from internal RC 115 kHz */
	//~ /* From soft reset we are running at least 12 Mhz OSC0 crystal */
	//~ /* Switch to 12 Mhz OSC0 crystal */
		//~ 0. write startup time in OSCCTRL0
		//~ 1. write osc0en in mcctrl
		//~ 2. Read the OSC0RDY in POSCSR, wait until it is zero
	//~
	//~
	//~ /* Switch to PLL */
//~ }

//~ #define SM_BF(name,value)				\
	//~ (((value) & ((1 << SM_##name##_SIZE) - 1))	\
	 //~ << SM_##name##_OFFSET)

#include "sm.h"

void clk_init(void)
{
	uint32_t cksel;

	/* in case of soft resets, disable watchdog */
	sm_writel(WDT_CTRL, SM_BF(KEY, 0x55));
	sm_writel(WDT_CTRL, SM_BF(KEY, 0xaa));

	/* osc0 is 12mhz (Mode 7), 560 us startup time */
	sm_writel(PM_OSCCTRL0, (SM_BF(MODE, 7)|SM_BF(STARTUP, 1)));

	/* enable osc0 */
	sm_writel(PM_MCCTRL, SM_BIT(OSC0EN));

	/* wait for osc0 */
	while (!(sm_readl(PM_POSCSR) & SM_BIT(OSC0RDY))) ;

	/* run from osc0 */
	sm_writel(PM_MCCTRL, SM_BF(MCSEL, 1) | SM_BIT(OSC0EN));

#ifdef CONFIG_PLL
	/* Initialize the PLL */
	//~ sm_writel(PM_PLL0, (SM_BF(PLLCOUNT, CFG_PLL0_SUPPRESS_CYCLES)
			    //~ | SM_BF(PLLMUL, CFG_PLL0_MUL - 1)
			    //~ | SM_BF(PLLDIV, CFG_PLL0_DIV)
			    //~ | SM_BF(PLLOPT, CFG_PLL0_OPT)
			    //~ | SM_BF(PLLOSC, 0)
			    //~ | SM_BIT(PLLEN)
			    //~ | SM_BIT(ERRATA)));//Rev. E errata PLL0/1 Lock control does not work

	sm_writel(PM_PLL0,
			(1 << SM_PLLEN_OFFSET) 	//Enable PLL
			| (CFG_PLL0_OPT << SM_PLLOPT_OFFSET) 	//Divide by 2 (output divider)
			| (0 << SM_PLLOSC_OFFSET) 	//Use OSC0 as source for PLL
			| (CFG_PLL0_DIV << SM_PLLDIV_OFFSET) 	//PLLDIV
			| ((CFG_PLL0_MUL - 1) << SM_PLLMUL_OFFSET) 	//PLLMUL 10
			| (CFG_PLL0_SUPPRESS_CYCLES << SM_PLLCOUNT_OFFSET) 	//Lock count, why 16 in AVR32 studio? why 64 here?
	//		| (1 << 7)	//Errata rev E. (rev K too?)
			);
	//0x40090149
	/* Wait for lock */
	while (!(sm_readl(PM_POSCSR) & SM_BIT(LOCK0))) ;
#endif

	/* We cannot write the CKSEL register before the ready-signal is set. */
	while (!(sm_readl(PM_POSCSR) & SM_BIT(CKRDY))) ;

	/* Set up clocks for the CPU and all peripheral buses */
	cksel = 0;
	if (CFG_CLKDIV_CPU)
		cksel |= SM_BIT(CPUDIV) | SM_BF(CPUSEL, CFG_CLKDIV_CPU - 1);
	if (CFG_CLKDIV_PBA)
		cksel |= SM_BIT(PBADIV) | SM_BF(PBASEL, CFG_CLKDIV_PBA - 1);
	if (CFG_CLKDIV_PBB)
		cksel |= SM_BIT(PBBDIV) | SM_BF(PBBSEL, CFG_CLKDIV_PBB - 1);

	sm_writel(PM_CKSEL, cksel);

	flash_set_waitstate(1);
#ifdef CONFIG_PLL
	/* Use PLL0 as main clock */
	sm_writel(PM_MCCTRL, SM_BF(MCSEL, 2) | SM_BIT(OSC0EN));
#endif
	//~ /* Update the CPU speed according to the PLL configuration */
	//~ gd->cpu_hz = get_cpu_clk_rate();	//Added 20100719 Mjan (from cpu.c)
}
   // Supported frequencies:
   // Fosc0 mul div PLL div2_en cpu_f pba_f   Comment
   //  12   15   1  192     1     12    12
   //  12    9   3   40     1     20    20    PLL out of spec
   //  12   15   1  192     1     24    12
   //  12    9   1  120     1     30    15
   //  12    9   3   40     0     40    20    PLL out of spec
   //  12   15   1  192     1     48    12
   //  12   15   1  192     1     48    24
   //  12    8   1  108     1     54    27
   //  12    9   1  120     1     60    15
   //  12    9   1  120     1     60    30
   //  12   10   1  132     1     66    16.5
