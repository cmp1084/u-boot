#ifndef __ASM_AVR32_SRAM_H
#define __ASM_AVR32_SRAM_H
#include <asm/types.h>

struct sram_config {
	/* Number of data bits. */
	u8 data_bits;

	/* Chip select */
	u8 chip_select;

	/* Number of address bits */
	u8 address_bits;

	/* nwe/nrd waveforms */
	u8 nwe_setup, nwe_pulse, nwe_hold;
	u8 nrd_setup, nrd_pulse, nrd_hold;

	/* ncs waveforms */
	u8 ncs_wr_setup, ncs_wr_pulse, ncs_wr_hold;
	u8 ncs_rd_setup, ncs_rd_pulse, ncs_rd_hold;

	/* Cycle length */
	u16 nwe_cycle, nrd_cycle;

	/* mode */
	u8 read_mode, write_mode, exnw_mode;
	u8 bat, dbw, tdf_cycles, tdf_mode, pmen, ps;
};


unsigned long sram_init(const struct sram_config *config);

#endif /* __ASM_AVR32_SRAM_H */
