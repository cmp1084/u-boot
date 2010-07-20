/*
 * Register definitions for SDRAM Controller
 */
#ifndef __ASM_AVR32_SDRAMC_H__
#define __ASM_AVR32_SDRAMC_H__

/* SDRAMC register offsets */
#define SDRAMC_MR				0x0000
#define SDRAMC_TR				0x0004
#define SDRAMC_CR				0x0008
#define SDRAMC_HSR				0x000c
#define SDRAMC_LPR				0x0010
#define SDRAMC_IER				0x0014
#define SDRAMC_IDR				0x0018
#define SDRAMC_IMR				0x001c
#define SDRAMC_ISR				0x0020
#define SDRAMC_MDR				0x0024

/* Bitfields in MR */
#define SDRAMC_MODE_OFFSET		0
#define SDRAMC_MODE_SIZE		3

/* Bitfields in TR */
#define SDRAMC_COUNT_OFFSET		0
#define SDRAMC_COUNT_SIZE		12

/* Bitfields in CR */
#define SDRAMC_NC_OFFSET		0
#define SDRAMC_NC_SIZE			2
#define SDRAMC_NR_OFFSET		2
#define SDRAMC_NR_SIZE			2
#define SDRAMC_NB_OFFSET		4
#define SDRAMC_NB_SIZE			1
#define SDRAMC_CAS_OFFSET		5
#define SDRAMC_CAS_SIZE			2
#define SDRAMC_DBW_OFFSET		7
#define SDRAMC_DBW_SIZE			1
#define SDRAMC_TWR_OFFSET		8
#define SDRAMC_TWR_SIZE			4
#define SDRAMC_TRC_OFFSET		12
#define SDRAMC_TRC_SIZE			4
#define SDRAMC_TRP_OFFSET		16
#define SDRAMC_TRP_SIZE			4
#define SDRAMC_TRCD_OFFSET		20
#define SDRAMC_TRCD_SIZE		4
#define SDRAMC_TRAS_OFFSET		24
#define SDRAMC_TRAS_SIZE		4
#define SDRAMC_TXSR_OFFSET		28
#define SDRAMC_TXSR_SIZE		4

/* Bitfields in HSR */
#define SDRAMC_DA_OFFSET		0
#define SDRAMC_DA_SIZE			1

/* Bitfields in LPR */
#define SDRAMC_LPCB_OFFSET		0
#define SDRAMC_LPCB_SIZE		2
#define SDRAMC_PASR_OFFSET		4
#define SDRAMC_PASR_SIZE		3
#define SDRAMC_TCSR_OFFSET		8
#define SDRAMC_TCSR_SIZE		2
#define SDRAMC_DS_OFFSET		10
#define SDRAMC_DS_SIZE			2
#define SDRAMC_TIMEOUT_OFFSET	12
#define SDRAMC_TIMEOUT_SIZE		2

/* Bitfields in IDR */
#define SDRAMC_RES_OFFSET		0
#define SDRAMC_RES_SIZE			1

/* Bitfields in MDR */
#define SDRAMC_MD_OFFSET		0
#define SDRAMC_MD_SIZE			2

/* Constants for MODE */
#define SDRAMC_MODE_NORMAL			0
#define SDRAMC_MODE_NOP				1
#define SDRAMC_MODE_BANKS_PRECHARGE	2
#define SDRAMC_MODE_LOAD_MODE		3
#define SDRAMC_MODE_AUTO_REFRESH	4
#define SDRAMC_MODE_EXT_LOAD_MODE	5
#define SDRAMC_MODE_POWER_DOWN		6

/* Constants for NC */
#define SDRAMC_NC_8_COLUMN_BITS		0
#define SDRAMC_NC_9_COLUMN_BITS		1
#define SDRAMC_NC_10_COLUMN_BITS	2
#define SDRAMC_NC_11_COLUMN_BITS	3

/* Constants for NR */
#define SDRAMC_NR_11_ROW_BITS		0
#define SDRAMC_NR_12_ROW_BITS		1
#define SDRAMC_NR_13_ROW_BITS		2

/* Constants for NB */
#define SDRAMC_NB_TWO_BANKS			0
#define SDRAMC_NB_FOUR_BANKS		1

/* Constants for CAS */
#define SDRAMC_CAS_ONE_CYCLE		1
#define SDRAMC_CAS_TWO_CYCLES		2
#define SDRAMC_CAS_THREE_CYCLES		3

/* Constants for DBW */
#define SDRAMC_DBW_32_BITS			0
#define SDRAMC_DBW_16_BITS			1

/* Constants for TIMEOUT */
#define SDRAMC_TIMEOUT_AFTER_END			0
#define SDRAMC_TIMEOUT_64_CYC_AFTER_END		1
#define SDRAMC_TIMEOUT_128_CYC_AFTER_END	2

/* Constants for MD */
//TODO: I think this should be named SDRAMC_MDR_SDRAM etc. instead of SDRAMC_MD_SDRAM etc.
//So I changed it. Ok? Not used by anyone else. 20100630 Mjan
#define SDRAMC_MDR_SDRAM			0
#define SDRAMC_MDR_LOW_POWER_SDRAM	1

/* Bit manipulation macros */
#define SDRAMC_BIT(name) (1 << SDRAMC_##name##_OFFSET)
#define SDRAMC_BF(name,value) (((value) & ((1 << SDRAMC_##name##_SIZE) - 1)) \
			 << SDRAMC_##name##_OFFSET)
#define SDRAMC_BFEXT(name,value) (((value) >> SDRAMC_##name##_OFFSET) \
			 & ((1 << SDRAMC_##name##_SIZE) - 1))
#define SDRAMC_BFINS(name,value,old) (((old) & ~(((1 << SDRAMC_##name##_SIZE) - 1) \
		    << SDRAMC_##name##_OFFSET)) | SDRAMC_BF(name,value))

/* Register access macros */
#define sdramc_readl(reg) readl((void *)(SDRAMC_BASE + SDRAMC_##reg))
#define sdramc_writel(reg,value) writel((value), (void *)SDRAMC_BASE + SDRAMC_##reg)

#endif /* __ASM_AVR32_SDRAMC_H__ */
