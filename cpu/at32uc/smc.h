/*
 * Register definitions for Static Memory Controller
 */
#ifndef __CPU_AT32UC3_SMC_H__
#define __CPU_AT32UC3_SMC_H__

#include <asm/arch/memory-map.h>
#include <asm/io.h>

/* SMC register offsets */
#define SMC_SETUP(x)				0x0000+(x)*0x10
#define SMC_PULSE(x)				0x0004+(x)*0x10
#define SMC_CYCLE(x)				0x0008+(x)*0x10
#define SMC_MODE(x)				0x000c+(x)*0x10

/* Bitfields in SETUP0..3 */
#define SMC_NWE_SETUP_OFFSET			0
#define SMC_NWE_SETUP_SIZE			6
#define SMC_NCS_WR_SETUP_OFFSET			8
#define SMC_NCS_WR_SETUP_SIZE			6
#define SMC_NRD_SETUP_OFFSET			16
#define SMC_NRD_SETUP_SIZE			6
#define SMC_NCS_RD_SETUP_OFFSET			24
#define SMC_NCS_RD_SETUP_SIZE			6

/* Bitfields in PULSE0..3 */
#define SMC_NWE_PULSE_OFFSET			0
#define SMC_NWE_PULSE_SIZE			7
#define SMC_NCS_WR_PULSE_OFFSET			8
#define SMC_NCS_WR_PULSE_SIZE			7
#define SMC_NRD_PULSE_OFFSET			16
#define SMC_NRD_PULSE_SIZE			7
#define SMC_NCS_RD_PULSE_OFFSET			24
#define SMC_NCS_RD_PULSE_SIZE			7

/* Bitfields in CYCLE0..3 */
#define SMC_NWE_CYCLE_OFFSET			0
#define SMC_NWE_CYCLE_SIZE			9
#define SMC_NRD_CYCLE_OFFSET			16
#define SMC_NRD_CYCLE_SIZE			9

/* Bitfields in MODE0..3 */
#define SMC_READ_MODE_OFFSET			0
#define SMC_READ_MODE_SIZE			1
#define SMC_WRITE_MODE_OFFSET			1
#define SMC_WRITE_MODE_SIZE			1
#define SMC_EXNW_MODE_OFFSET			4
#define SMC_EXNW_MODE_SIZE			2
#define SMC_BAT_OFFSET				8
#define SMC_BAT_SIZE				1
#define SMC_DBW_OFFSET				12
#define SMC_DBW_SIZE				2
#define SMC_TDF_CYCLES_OFFSET			16
#define SMC_TDF_CYCLES_SIZE			4
#define SMC_TDF_MODE_OFFSET			20
#define SMC_TDF_MODE_SIZE			1
#define SMC_PMEN_OFFSET				24
#define SMC_PMEN_SIZE				1
#define SMC_PS_OFFSET				28
#define SMC_PS_SIZE				2

/* Constants for READ_MODE */
#define SMC_READ_MODE_NCS_CONTROLLED		0
#define SMC_READ_MODE_NRD_CONTROLLED		1

/* Constants for WRITE_MODE */
#define SMC_WRITE_MODE_NCS_CONTROLLED		0
#define SMC_WRITE_MODE_NWE_CONTROLLED		1

/* Constants for EXNW_MODE */
#define SMC_EXNW_MODE_DISABLED			0
#define SMC_EXNW_MODE_RESERVED			1
#define SMC_EXNW_MODE_FROZEN			2
#define SMC_EXNW_MODE_READY			3

/* Constants for BAT */
#define SMC_BAT_BYTE_SELECT			0
#define SMC_BAT_BYTE_WRITE			1

/* Constants for DBW */
#define SMC_DBW_8_BITS				0
#define SMC_DBW_16_BITS				1
#define SMC_DBW_32_BITS				2

/* Bit manipulation macros */
#define SMC_BIT(name)						\
	(1 << SMC_##name##_OFFSET)
#define SMC_BF(name,value)					\
	(((value) & ((1 << SMC_##name##_SIZE) - 1))		\
	 << SMC_##name##_OFFSET)
#define SMC_BFEXT(name,value)					\
	(((value) >> SMC_##name##_OFFSET)			\
	 & ((1 << SMC_##name##_SIZE) - 1))
#define SMC_BFINS(name,value,old)\
	(((old) & ~(((1 << SMC_##name##_SIZE) - 1)		\
		    << SMC_##name##_OFFSET))			\
	 | SMC_BF(name,value))

/* Register access macros */
#define smc_readl(cs,reg)					\
	readl((void *)SMC_BASE + SMC_##reg(cs))
#define smc_writel(cs,reg,value)				\
	writel((value), (void *)SMC_BASE + SMC_##reg(cs))

#endif /* __CPU_AT32UC3_SMC_H__ */
