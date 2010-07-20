/*
 * Copyright (C) 2010 SimpleMachine
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
#include <asm/sdram.h>
#include <asm/arch/clk.h>
#include <asm/arch/hmatrix.h>
#include <asm/arch/portmux.h>

DECLARE_GLOBAL_DATA_PTR;

static const struct sram_config sram_config = {
	/* 2x16MBit, CY7C1069AV33-10ZXC */
	.data_bits		= 16,
	.address_bits	= 21,
	.ncs_rd_setup	= 0,
	.ncs_wr_setup 	= 0,
	.nwe_setup		= 0,
	.nrd_setup		= 0,
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
	.nwe_pulse		= 2,
	.nrd_pulse		= 2,
	.nwe_cycle		= 3,
	.nrd_cycle		= 3,
	.chip_select	= 2,
	.read_mode		= 1,
	.write_mode		= 1,
	.exnw_mode		= 0,
	.bat			= 1,
	.tdf_cycles		= 0,
	.tdf_mode		= 0,
	.pmen			= 0,
	.ps				= 1,

};

int board_early_init_f(void)
{
	int cs_mask;
	cs_mask = 1;

	portmux_enable_spi1(cs_mask, 0);

	/* This activates the SDRAM, 16 bit data, 24 bit address */
	portmux_enable_ebi(0, 0, 0, 0);
	portmux_enable_usart0(PORTMUX_DRIVE_MIN);	//Drive strenght 0
#if defined(CONFIG_MACB)
	portmux_enable_macb(0, PORTMUX_DRIVE_HIGH);
#endif

	return 0;
}

phys_size_t initdram(int board_type)
{
	unsigned long expected_size;
	unsigned long actual_size;
	void * sram_base;

	sram_base = map_physmem(EBI_SRAM_CS2_BASE, EBI_SRAM_CS2_SIZE, MAP_NOCACHE);

	expected_size = sram_init(&sram_config);
	actual_size = get_ram_size(sram_base, expected_size);

	unmap_physmem(sram_base, EBI_SRAM_CS2_SIZE);

	if (expected_size != actual_size)
		printf("Warning: Only %lu of %lu MiB SDRAM is working\n",
				actual_size >> 20, expected_size >> 20);

	return actual_size;
}

/* initsdram added 20100624 mjan */
phys_size_t initsdram(int board_type)
{
	static const struct sdram_config sdramconfig = {
		/* MT48LC16M16A2TG7E */
		.data_bits = 16,
		.row_bits = 13,
		.col_bits = 9,
		.bank_bits = 2,
		.cas = 2,
		.twr = 14,
		.trc = 60,
		.trp = 15,
		.trcd = 15,
		.txsr = 67,
		.tras = 37,
		.refresh_period = 7812 * 12 / 1000,
		//~ //.refresh_period = (781 * (SDRAMC_BUS_HZ / 1000)) / 100000,  //depends on PLL
		//~ /* NGW100, same MT48LC16M16A SDRAM
		//~ .data_bits      = SDRAM_DATA_16BIT,
		//~ .row_bits = 13,
		//~ .col_bits = 9,
		//~ .bank_bits = 2,
		//~ .cas = 3,
		//~ .twr = 2,
		//~ .trc = 7,
		//~ .trp = 2,
		//~ .trcd = 2,
		//~ .tras = 5,
		//~ .txsr = 5,
		//~ */
	};

//~ static const struct sdram_config sdramconfig = {
	//~ .data_bits	= SDRAM_DATA_16BIT,
	//~ .row_bits	= 13,
	//~ .col_bits	= 9,
	//~ .bank_bits	= 2,
	//~ .cas		= 3,
	//~ .twr		= 2,
	//~ .trc		= 7,
	//~ .trp		= 2,
	//~ .trcd		= 2,
	//~ .tras		= 5,
	//~ .txsr		= 5,
	//~ /* 7.81 us */
	//~ .refresh_period	= (781 * (SDRAMC_BUS_HZ / 1000)) / 100000,
//~ };

	unsigned long expected_size;
	unsigned long actual_size;
	void * sdram_base;
	volatile void * ebi_sdram_base;

	ebi_sdram_base = (void *)0xd0000000;

	sdram_base = map_physmem(SDRAMC_BASE, EBI_SDRAM_SIZE, MAP_NOCACHE);
	//~ printf("sdram_base @ 0x%08x, ebi_sdram_base @ 0x%08x\n", (unsigned int) sdram_base, (unsigned int) ebi_sdram_base);

	expected_size = sdram_init(sdram_base, &sdramconfig);
	//printf("expected_size 0x%08x bytes of SDRAM\n", (unsigned int) expected_size);

	//~ actual_size = get_ram_size(&ebi_sdram_base, EBI_SDRAM_SIZE);
	actual_size = expected_size; //EBI_SDRAM_SIZE;
	//printf("actual_size 0x%08x bytes of SDRAM\n", (unsigned int) actual_size);

	unmap_physmem(sdram_base, EBI_SDRAM_SIZE);

	//if (expected_size != actual_size)
			//printf("Warning: Only %lu of %lu MiB SDRAM is working\n",
			//		actual_size >> 20, expected_size >> 20);

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
	//macb_eth_initialize(0, (void *)MACB_BASE, bi->bi_phy_id[0]); removed 20100701 Mjan
	return 0;
}

/* SPI chip select control */
#ifdef CONFIG_ATMEL_SPI
#include <spi.h>

#define ATNGW100_DATAFLASH_CS_PIN	1//GPIO_PIN_PA(3)

int spi_cs_is_valid(unsigned int bus, unsigned int cs)
{
	return bus == 0 && cs == 0;
}

void spi_cs_activate(struct spi_slave *slave)
{
	//~ gpio_set_value(ATNGW100_DATAFLASH_CS_PIN, 0);
}

void spi_cs_deactivate(struct spi_slave *slave)
{
	//~ gpio_set_value(ATNGW100_DATAFLASH_CS_PIN, 1);
}
#endif /* CONFIG_ATMEL_SPI */
#endif
