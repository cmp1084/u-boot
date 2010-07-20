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

#ifdef CFG_SDRAMC
#include <asm/io.h>
#include <asm/sdram.h>

#include <asm/arch/clk.h>
#include <asm/arch/memory-map.h>
#include <asm/hmatrix-common.h>
#include <asm/sysreg.h>
#include <asm/arch/portmux.h>
#include "sdramc.h"

//~ #include <asm/arch/hmatrix.h>

/* From asm/sdram.h */
//~ struct sdram_config {
	//~ /* Number of data bits. */
	//~ enum {
		//~ SDRAM_DATA_16BIT = 16,
		//~ SDRAM_DATA_32BIT = 32,
	//~ } data_bits;
//~
	//~ /* Number of address bits */
	//~ uint8_t row_bits, col_bits, bank_bits;
//~
	//~ /* SDRAM timings in cycles */
	//~ uint8_t cas, twr, trc, trp, trcd, tras, txsr;
//~
	//~ /* SDRAM refresh period in cycles */
	//~ unsigned long refresh_period;
//~ };

/* From initsdram board/atmel/mizar.c (or similar) */
//~ static const struct sdram_config sdramconfig = {
	//~ /* 2x16MBit, MT48LC16M16A2TG7E */
	//~ .data_bits = 16,
	//~ .row_bits = 13,
	//~ .col_bits = 9,
	//~ .cas = 2,
	//~ .twr = 14,
	//~ .trc = 60,
	//~ .trp = 15,
	//~ .trcd = 15,
	//~ .tras = 37,
	//~ .txsr = 67,
//~ };
void sdramc_ns_delay(unsigned long ck)
{
  // Use the CPU cycle counter (CPU and HSB clocks are the same).
  unsigned long delay_start_cycle = (unsigned long)sysreg_read(COUNT);
  unsigned long delay_end_cycle = delay_start_cycle + ck;

  // To be safer, the end of wait is based on an inequality test, so CPU cycle
  // counter wrap around is checked.
  if (delay_start_cycle > delay_end_cycle)
  {
    while ((unsigned long)sysreg_read(COUNT) > delay_end_cycle);
  }
  while ((unsigned long)sysreg_read(COUNT) < delay_end_cycle);
}

#define SDRAM_TR 7812

unsigned long sdram_init(void * sdram_base, const struct sdram_config * config)
{
	unsigned int sdram_size;
	uint32_t cfgreg;
	unsigned long hsb_hz;
	unsigned long hsb_mhz_dn;
	unsigned long hsb_mhz_up;
	volatile unsigned long * sdram;
	unsigned long i;
	//unsigned long j, progress_inc, tmp, foo, noErrors;

	sdram = (void *) 0xd0000000;
	hsb_hz = get_hsb_clk_rate();	//was: CFG_OSC0_HZ; 20100716 Mjan
	hsb_mhz_dn = hsb_hz / 1000000;
	hsb_mhz_up = (hsb_hz + 999999) / 1000000;

	hmatrix_write(SFR[5], hmatrix_read(SFR[5] | (1 << 1)));
	hmatrix_read(SFR[5]);

	cfgreg = (SDRAMC_BF(NC, config->col_bits - 8)
				| SDRAMC_BF(NR, config->row_bits - 11)
				| SDRAMC_BF(NB, config->bank_bits - 1)
				| SDRAMC_BF(CAS, config->cas)
				| SDRAMC_BF(TWR, config->twr)
				| SDRAMC_BF(TRC, config->trc)
				| SDRAMC_BF(TRP, config->trp)
				| SDRAMC_BF(TRCD, config->trcd)
				| SDRAMC_BF(TRAS, config->tras)
				| SDRAMC_BF(TXSR, config->txsr));
				// =0x35ffce59 ? 20100629 Mjan
				//AVR32 Studio get 0x111111d9
	if(config->data_bits == SDRAM_DATA_16BIT) {
		cfgreg |= SDRAMC_BIT(DBW);
		//cfgreg = 0x35ffced9
	}

	//~ cfgreg = 0x111111d9;	//Snatched from AVR32 Studio
	/* Interrupts should be turned off at this point */
	sdramc_writel(CR, cfgreg);
	sdramc_readl(CR);

	/* Set the Memory Device Register to SDRAM */
	sdramc_writel(MDR, SDRAMC_MDR_SDRAM);

	/* Send a NOP to turn on the clock (necessary on some chips) */
	sdramc_writel(MR, SDRAMC_MODE_NOP);
	sdramc_readl(MR);
	readl(sdram_base);

	/*
	 * Initialization sequence for SDRAM, from the data sheet:
	 *
	 * 1. A minimum pause of 200 us is provided to precede any
	 *    signal toggle.
	 */
	udelay(200);	//Was: udelay(200) 20100716 Mjan.

	/*
	 * 2. A Precharge All command is issued to the SDRAM
	 */
	sdramc_writel(MR, SDRAMC_MODE_BANKS_PRECHARGE);
	sdramc_readl(MR);
	readl(sdram_base);
	sdramc_ns_delay(((15) * (hsb_mhz_up) + 999) / 1000);

	/*
	 * 3. Eight auto-refresh (CBR) cycles are provided, (only two should be necessary)
	 */
	sdramc_writel(MR, SDRAMC_MODE_AUTO_REFRESH);
	sdramc_readl(MR);
	for(i = 0; i < 8; i++) {	//Was: i < 8; 20100629 Mjan
		readl(sdram_base);
		sdramc_ns_delay(((66) * (hsb_mhz_up) + 999) / 1000);
	}

	/*
	 * 4. A mode register set (MRS) cycle is issued to program
	 *    SDRAM parameters, in particular CAS latency and burst
	 *    length.
	 *
	 * The address will be chosen by the SDRAMC automatically; we
	 * just have to make sure BA[1:0] are set to 0.
	 */
	sdramc_writel(MR, SDRAMC_MODE_LOAD_MODE);
	sdramc_readl(MR);
	readl(sdram_base);
	sdramc_ns_delay(((2) * (hsb_mhz_up) + 999) / 1000);

	/*
	 * 5. The application must go into Normal Mode, setting Mode
	 *    to 0 in the Mode Register and performing a write access
	 *    at any location in the SDRAM.
	 */
	sdramc_writel(MR, SDRAMC_MODE_NORMAL);
	sdramc_readl(MR);
	readl(sdram_base);

	/*
	 * 6. Write refresh rate into SDRAMC refresh timer count
	 *    register (refresh rate = timing between refresh cycles).
	 */
	//This value should be 0x5d, at least AVR32 studio example show this value.
	sdramc_writel(TR, (SDRAM_TR * hsb_mhz_dn) / 1000); //config->refresh_period);
	sdramc_readl(TR);

	if (config->data_bits == SDRAM_DATA_16BIT)
		sdram_size = 1 << (config->row_bits + config->col_bits + config->bank_bits + 1);
	else
		sdram_size = 1 << (config->row_bits + config->col_bits + config->bank_bits + 2);

	//Below is code for simple memory test
	//Caution serial is not initialized yet.
	//printf("sdram_init done\n");
	//udelay(1000000);
	//~ sdram_size >>= 2;
	//~ progress_inc = (sdram_size + 50) / 100;
	//~ do {
		//~ noErrors = 0;
	  //~ for (i = 0, j = 0; i < sdram_size; i++)
  //~ {
    //~ if (i == j * progress_inc)
    //~ {
      //~ printf("\rFilling SDRAM with test pattern: ");
      //~ printf("%i", j++);
      //~ printf("%%");
      //~ printf("   0x%08x", &sdram[i]);
    //~ }
//~
    //~ *(sdram+i) = i;
	//~ tmp = *(sdram+i);
	//~ if (tmp != i)
	//~ {
		//~ printf("  Fail: 0x%08x = 0x%08x, should be 0x%08x\n", &sdram[i], sdram[i], i);
		//~ noErrors++;
	//~ }
  //~ }
  //~ printf("\nSDRAM filled with test pattern       \n");
//~
  //~ // Recover the test pattern from the SDRAM and verify it.
  //~ for (i = 0, j = 0; i < sdram_size; i++)
  //~ {
    //~ if (i == j * progress_inc)
    //~ {
      //~ printf("\rRecovering test pattern from SDRAM: ");
      //~ printf("%i", j++);
      //~ printf("%%");
      //~ printf("   0x%08x", &sdram[i]);
    //~ }
    //~ tmp = *(sdram+i);
    //~ if (tmp != i)
    //~ {
		//~ printf("  Fail: 0x%08x = 0x%08x, should be 0x%08x\n", &sdram[i], sdram[i], i);
		//~ noErrors++;
    //~ }
  //~ }
  //~ printf("\rSDRAM tested: ");
  //~ printf("0x%x", noErrors);
  //~ printf(" corrupted word(s)\n");
	//~ } while(noErrors);

	return sdram_size;
}

#endif /* CFG_SDRAMC */
