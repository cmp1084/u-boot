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

#include <asm/io.h>
#include <asm/sram.h>
#include <asm/arch/clk.h>
#include <asm/arch/hmatrix.h>
#include <asm/arch/portmux.h>

DECLARE_GLOBAL_DATA_PTR;

static const struct sram_config sram_config = {
	/* 2x16MBit, CY7C1069AV33-10ZXC */
	.data_bits	= 16,
	.address_bits	= 21,
	.ncs_rd_setup	= 0,
	.ncs_wr_setup 	= 0,
	.nwe_setup	= 0,
	.nrd_setup	= 0,
	/*
	 * These settings works when running at 33Mhz,
	 * but fails at 54MHz
	 */

	/*
	.ncs_wr_pulse 	= 1,
	.ncs_rd_pulse	= 1,
	.nwe_pulse	= 1,
	.nrd_pulse	= 1,
	.nwe_cycle	= 2,
	.nrd_cycle	= 2,
	*/
	.ncs_wr_pulse 	= 2,
	.ncs_rd_pulse	= 2,
	.nwe_pulse	= 2,
	.nrd_pulse	= 2,
	.nwe_cycle	= 3,
	.nrd_cycle	= 3,
	.chip_select	= 2,
	.read_mode	= 1,
	.write_mode	= 1,
	.exnw_mode	= 0,
	.bat		= 1,
	.tdf_cycles	= 0,
	.tdf_mode	= 0,
	.pmen		= 0,
	.ps		= 1,

};
int board_early_init_f(void)
{
	/* Enable SDRAM in the EBI mux according to AP7000 datasheet */
	hmatrix_slave_write(EBI, SFR, HMATRIX_BIT(EBI_SDRAM_ENABLE));

	/* 16 bit data, 24 bit address */
	portmux_enable_ebi(16, 23, 0, PORTMUX_DRIVE_HIGH);
	portmux_enable_usart0(PORTMUX_DRIVE_MIN);
#if defined(CONFIG_MACB)
	portmux_enable_macb(0, PORTMUX_DRIVE_HIGH);
#endif

	return 0;
}

phys_size_t initdram(int board_type)
{
	unsigned long expected_size;
	unsigned long actual_size;
	void *sram_base;

	sram_base = map_physmem(EBI_SRAM_CS2_BASE, EBI_SRAM_CS2_SIZE, MAP_NOCACHE);

	expected_size = sram_init(&sram_config);
	actual_size = get_ram_size(sram_base, expected_size);

	unmap_physmem(sram_base, EBI_SRAM_CS2_SIZE);

	if (expected_size != actual_size)
		printf("Warning: Only %lu of %lu MiB SDRAM is working\n",
				actual_size >> 20, expected_size >> 20);

	return actual_size;
}

int board_early_init_r(void)
{
	/* Physical address of phy (0xff = auto-detect) */
	gd->bd->bi_phy_id[0] = 0xff;
	return 0;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bi)
{
	macb_eth_initialize(0, (void *)MACB_BASE, bi->bi_phy_id[0]);
	return 0;
}
#endif
