#include <common.h>
#include <asm/sram.h>
#include "smc.h"

unsigned long sram_init(const struct sram_config *config)
{
	u32 cfgreg;
	u32 dbw;
	u32 sram_size;

	cfgreg = SMC_BF(NWE_SETUP, config->nwe_setup)
		|SMC_BF(NRD_SETUP, config->nrd_setup)
		|SMC_BF(NCS_WR_SETUP, config->ncs_wr_setup)
		|SMC_BF(NCS_RD_SETUP, config->ncs_rd_setup);
	smc_writel(config->chip_select, SETUP, cfgreg);

	cfgreg = SMC_BF(NWE_PULSE, config->nwe_pulse)
		|SMC_BF(NRD_PULSE, config->nrd_pulse)
		|SMC_BF(NCS_WR_PULSE, config->ncs_wr_pulse)
		|SMC_BF(NCS_RD_PULSE, config->ncs_rd_pulse);
	smc_writel(config->chip_select, PULSE, cfgreg);

	cfgreg = SMC_BF(NWE_CYCLE, config->nwe_cycle)
		|SMC_BF(NRD_CYCLE, config->nrd_cycle);
	smc_writel(config->chip_select, CYCLE, cfgreg);

	switch (config->data_bits) {
	case 8:
		dbw=0;
		break;
	case 16:
		dbw=1;
		break;
	case 32:
		dbw=2;
		break;
	default:
		panic("Invalid number of databits for SRAM");

	}
	cfgreg = SMC_BF(READ_MODE, config->read_mode)
		|SMC_BF(WRITE_MODE, config->write_mode)
		|SMC_BF(EXNW_MODE, config->exnw_mode)
		|SMC_BF(BAT, config->bat)
		|SMC_BF(DBW, dbw)
		|SMC_BF(TDF_CYCLES, config->tdf_cycles)
		|SMC_BF(TDF_MODE, config->tdf_mode)
		|SMC_BF(PMEN, config->pmen)
		|SMC_BF(PS, config->ps);




	smc_writel(config->chip_select, MODE, cfgreg);
	sram_size= (1<<config->address_bits) * (config->data_bits/8);


	return sram_size;
}


