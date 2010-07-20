/*
 * Copyright (C) 2005-2006 Atmel Corporation
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
#include <command.h>

#include <asm/io.h>
#include <asm/sections.h>
#include <asm/sysreg.h>

#include <asm/arch/clk.h>
#include <asm/arch/memory-map.h>

/* Sanity checks */
#if ((CFG_CLKDIV_CPU > CFG_CLKDIV_PBA)	\
	|| (CFG_CLKDIV_CPU > CFG_CLKDIV_PBB))
# error Constraint fCPU >= fPB{A,B} violated
#endif
#if defined(CONFIG_PLL) && ((CFG_PLL0_MUL < 1) || (CFG_PLL0_DIV < 0))
# error Invalid PLL multiplier and/or divider
#endif

DECLARE_GLOBAL_DATA_PTR;

int cpu_init(void)
{
	extern void _evba(void);

	gd->cpu_hz = CFG_OSC0_HZ; //removed 20100716 Mjan, due to clk_init() moved

	clk_init(); //Move out to run first of all in board_init_f 20100716 Mjan

	/* Update the CPU speed according to the PLL configuration */
	gd->cpu_hz = get_cpu_clk_rate();

	/* Set up the exception handler table and enable exceptions */
	sysreg_write(EVBA, (unsigned long)&_evba);
	asm volatile("csrf	%0" : : "i"(SYSREG_EM_OFFSET));

	//~ if(gclk_init)	//What does this do? 20100712 Mjan , it doesnt do nothing for the uc3. Removed.
		//~ gclk_init();

	return 0;
}

void prepare_to_boot(void)
{
	/* No caches to flush on this cpu. */
}

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	/* This will reset the CPU core, caches, MMU and all internal busses */
	__builtin_mtdr(8, 1 << 13);	/* set DC:DBE */
	__builtin_mtdr(8, 1 << 30);	/* set DC:RES */

	/* Flush the pipeline before we declare it a failure */
	asm volatile("sub   pc, pc, -4");

	return -1;
}
