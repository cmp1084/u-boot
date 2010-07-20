/*
 * Register definitions for System Manager
 */
#ifndef __CPU_AT32UC_SM_H__
#define __CPU_AT32UC_SM_H__

/* SM register offsets */
/* PM starts at 0xFFFF0C00 */
#define SM_PM_REGS_OFFSET			0x0c00
#define SM_PM_MCCTRL				(SM_PM_REGS_OFFSET + 0x0000)
#define SM_PM_CKSEL				(SM_PM_REGS_OFFSET + 0x0004)
#define SM_PM_CPU_MASK				(SM_PM_REGS_OFFSET + 0x0008)
#define SM_PM_HSB_MASK				(SM_PM_REGS_OFFSET + 0x000c)
#define SM_PM_PBA_MASK				(SM_PM_REGS_OFFSET + 0x0010)
#define SM_PM_PBB_MASK				(SM_PM_REGS_OFFSET + 0x0014)
#define SM_PM_PLL0				(SM_PM_REGS_OFFSET + 0x0020)
#define SM_PM_PLL1				(SM_PM_REGS_OFFSET + 0x0024)
#define SM_PM_OSCCTRL0				(SM_PM_REGS_OFFSET + 0x0028)
#define SM_PM_OSCCTRL1				(SM_PM_REGS_OFFSET + 0x002c)
#define SM_PM_OSCCTRL32				(SM_PM_REGS_OFFSET + 0x0030)
#define SM_PM_IER				(SM_PM_REGS_OFFSET + 0x0040)
#define SM_PM_IDR				(SM_PM_REGS_OFFSET + 0x0044)
#define SM_PM_IMR				(SM_PM_REGS_OFFSET + 0x0048)
#define SM_PM_ISR				(SM_PM_REGS_OFFSET + 0x004c)
#define SM_PM_ICR				(SM_PM_REGS_OFFSET + 0x0050)
#define SM_PM_POSCSR				(SM_PM_REGS_OFFSET + 0x0054)
#define SM_PM_GCCTRL				(SM_PM_REGS_OFFSET + 0x0060)
#define SM_PM_RCCR				(SM_PM_REGS_OFFSET + 0x00c0)
#define SM_PM_BGCR				(SM_PM_REGS_OFFSET + 0x00c4)
#define SM_PM_VREGCR				(SM_PM_REGS_OFFSET + 0x00c8)
#define SM_PM_BOD				(SM_PM_REGS_OFFSET + 0x00d0)
#define SM_PM_RCAUSE				(SM_PM_REGS_OFFSET + 0x0140)
#define SM_RC_RCAUSE				SM_PM_RCAUSE /* TODO: remove */
/* RTC starts at 0xFFFF0D00 */
#define SM_RTC_REGS_OFFSET			0x0d00
#define SM_RTC_CTRL				(SM_RTC_REGS_OFFSET + 0x0000)
#define SM_RTC_VAL				(SM_RTC_REGS_OFFSET + 0x0004)
#define SM_RTC_TOP				(SM_RTC_REGS_OFFSET + 0x0008)
#define SM_RTC_IER				(SM_RTC_REGS_OFFSET + 0x0010)
#define SM_RTC_IDR				(SM_RTC_REGS_OFFSET + 0x0014)
#define SM_RTC_IMR				(SM_RTC_REGS_OFFSET + 0x0018)
#define SM_RTC_ISR				(SM_RTC_REGS_OFFSET + 0x001c)
#define SM_RTC_ICR				(SM_RTC_REGS_OFFSET + 0x0020)
/* WDT starts at 0xFFFF0D30 */
#define SM_WDT_REGS_OFFSET			0x0d30
#define SM_WDT_CTRL				(SM_WDT_REGS_OFFSET + 0x0000)
#define SM_WDT_CLR				(SM_WDT_REGS_OFFSET + 0x0004)
#define SM_WDT_EXT				(SM_WDT_REGS_OFFSET + 0x0008) /* TODO: does not exist ? */
/* EIC starts at offset 0xFFFF0D80 */
/* TODO: change EIM to EIC */
#define SM_EIC_REGS_OFFSET			0x0d80
#define SM_EIM_IER				(SM_EIC_REGS_OFFSET + 0x0000)
#define SM_EIM_IDR				(SM_EIC_REGS_OFFSET + 0x0004)
#define SM_EIM_IMR				(SM_EIC_REGS_OFFSET + 0x0008)
#define SM_EIM_ISR				(SM_EIC_REGS_OFFSET + 0x000c)
#define SM_EIM_ICR				(SM_EIC_REGS_OFFSET + 0x0010)
#define SM_EIM_MODE				(SM_EIC_REGS_OFFSET + 0x0014)
#define SM_EIM_EDGE				(SM_EIC_REGS_OFFSET + 0x0018)
#define SM_EIM_LEVEL				(SM_EIC_REGS_OFFSET + 0x001c)
#define SM_EIM_FILTER				(SM_EIC_REGS_OFFSET + 0x0020)
#define SM_EIM_TEST				(SM_EIC_REGS_OFFSET + 0x0024)
#define SM_EIM_ASYNC				(SM_EIC_REGS_OFFSET + 0x0028)
#define SM_EIM_SCAN				(SM_EIC_REGS_OFFSET + 0x002c)
#define SM_EIM_EN				(SM_EIC_REGS_OFFSET + 0x0030)
#define SM_EIM_DIS				(SM_EIC_REGS_OFFSET + 0x0034)
#define SM_EIM_CTRL				(SM_EIC_REGS_OFFSET + 0x0038)

/* Bitfields used in many registers */
#define SM_EN_OFFSET				0
#define SM_EN_SIZE				1

/* Bitfields in PM_MCCTRL */
#define SM_MCSEL_OFFSET				0
#define SM_MCSEL_SIZE				2
#define SM_OSC0EN_OFFSET			2
#define SM_OSC0EN_SIZE				1
#define SM_OSC1EN_OFFSET			3
#define SM_OSC1EN_SIZE				1

/* Bitfields in PM_CKSEL */
#define SM_CPUSEL_OFFSET			0
#define SM_CPUSEL_SIZE				3
#define SM_CPUDIV_OFFSET			7
#define SM_CPUDIV_SIZE				1
#define SM_HSBSEL_OFFSET			8
#define SM_HSBSEL_SIZE				3
#define SM_HSBDIV_OFFSET			15
#define SM_HSBDIV_SIZE				1
#define SM_PBASEL_OFFSET			16
#define SM_PBASEL_SIZE				3
#define SM_PBADIV_OFFSET			23
#define SM_PBADIV_SIZE				1
#define SM_PBBSEL_OFFSET			24
#define SM_PBBSEL_SIZE				3
#define SM_PBBDIV_OFFSET			31
#define SM_PBBDIV_SIZE				1

/* Bitfields in PM_PLL0 */
#define SM_PLLEN_OFFSET				0
#define SM_PLLEN_SIZE				1
#define SM_PLLOSC_OFFSET			1
#define SM_PLLOSC_SIZE				1
#define SM_PLLOPT_OFFSET			2
#define SM_PLLOPT_SIZE				3
#define SM_ERRATA_OFFSET			7
#define SM_ERRATA_SIZE				1
#define SM_PLLDIV_OFFSET			8
#define SM_PLLDIV_SIZE				4
#define SM_PLLMUL_OFFSET			16
#define SM_PLLMUL_SIZE				4
#define SM_PLLCOUNT_OFFSET			24
#define SM_PLLCOUNT_SIZE			6
#define SM_PLLTEST_OFFSET			31	/* TODO: remove */
#define SM_PLLTEST_SIZE				1	/* TODO: remove */

/* Bitfields in PM_OSCCTRL0,1 */
#define SM_MODE_OFFSET 				0
#define SM_MODE_SIZE				3
#define SM_STARTUP_OFFSET 			8
#define SM_STARTUP_SIZE				3

/* Bitfields in PM_VCTRL */
#define SM_VAUTO_OFFSET				0	/* TODO: remove */
#define SM_VAUTO_SIZE				1	/* TODO: remove */
#define SM_PM_VCTRL_VAL_OFFSET			8	/* TODO: remove */
#define SM_PM_VCTRL_VAL_SIZE			7	/* TODO: remove */

/* Bitfields in PM_VMREF */
#define SM_REFSEL_OFFSET			0	/* TODO: remove */
#define SM_REFSEL_SIZE				4	/* TODO: remove */

/* Bitfields in PM_VMV */
#define SM_PM_VMV_VAL_OFFSET			0	/* TODO: remove */
#define SM_PM_VMV_VAL_SIZE			8	/* TODO: remove */

/* Bitfields in PM_IER/IDR/IMR/ISR/ICR, POSCSR */
#define SM_LOCK0_OFFSET				0
#define SM_LOCK0_SIZE				1
#define SM_LOCK1_OFFSET				1
#define SM_LOCK1_SIZE				1
#define SM_WAKE_OFFSET				2	/* TODO: remove */
#define SM_WAKE_SIZE				1	/* TODO: remove */
#define SM_VOK_OFFSET				3	/* TODO: remove */
#define SM_VOK_SIZE					1	/* TODO: remove */
#define SM_VMRDY_OFFSET				4	/* TODO: remove */
#define SM_VMRDY_SIZE				1	/* TODO: remove */
#define SM_CKRDY_OFFSET				5
#define SM_CKRDY_SIZE				1
#define SM_MSKRDY_OFFSET			6
#define SM_MSKRDY_SIZE				1
#define SM_OSC0RDY_OFFSET			7
#define SM_OSC0RDY_SIZE				1
#define SM_OSC1RDY_OFFSET			8
#define SM_OSC1RDY_SIZE				1
#define SM_OSC32RDY_OFFSET			9
#define SM_OSC32RDY_SIZE			1
#define SM_BODDET_OFFSET			16
#define SM_BODDET_SIZE				1

/* Bitfields in PM_GCCTRL*/
#define SM_OSCSEL_OFFSET			0
#define SM_OSCSEL_SIZE				1
#define SM_PLLSEL_OFFSET			1
#define SM_PLLSEL_SIZE				1
#define SM_CEN_OFFSET				2
#define SM_CEN_SIZE				1
#define SM_DIVEN_OFFSET				4
#define SM_DIVEN_SIZE				1
#define SM_DIV_OFFSET				8
#define SM_DIV_SIZE				8

/* Bitfields in PM_RCAUSE */
#define SM_POR_OFFSET				0
#define SM_POR_SIZE				1
#define SM_BOD_OFFSET				1
#define SM_BOD_SIZE				1
#define SM_EXT_OFFSET				2
#define SM_EXT_SIZE				1
#define SM_WDT_OFFSET				3
#define SM_WDT_SIZE				1
#define SM_JTAG_OFFSET				4
#define SM_JTAG_SIZE				1
#define SM_SERP_OFFSET				5	/* TODO: remove */
#define SM_SERP_SIZE				1	/* TODO: remove */
#define SM_CPUERR_OFFSET			7
#define SM_CPUERR_SIZE				1
#define SM_OCDRST_OFFSET			8
#define SM_OCDRST_SIZE				1
#define SM_JTAGHARD_OFFSET			9
#define SM_JTAGHARD_SIZE			1


/* Bitfields in RTC_CTRL */
#define SM_PCLR_OFFSET				1
#define SM_PCLR_SIZE				1
#define SM_WAKE_EN_OFFSET			2
#define SM_WAKE_EN_SIZE				1
#define SM_CLK32_OFFSET				3
#define SM_CLK32_SIZE				1
#define SM_BUSY_OFFSET				4
#define SM_BUSY_SIZE				1
#define SM_RTC_CTRL_PSEL_OFFSET		8
#define SM_RTC_CTRL_PSEL_SIZE		4
#define SM_CLKEN_OFFSET				16
#define SM_CLKEN_SIZE				1

/* Bitfields in RTC_VAL */
#define SM_RTC_VAL_VAL_OFFSET		0
#define SM_RTC_VAL_VAL_SIZE			32

/* Bitfields in RTC_TOP */
#define SM_RTC_TOP_VAL_OFFSET		0
#define SM_RTC_TOP_VAL_SIZE			32

/* Bitfields in RTC_ICR */
#define SM_TOPI_OFFSET				0
#define SM_TOPI_SIZE				1


/* Bitfields in WDT_CTRL */
#define SM_WDT_CTRL_PSEL_OFFSET	8
#define SM_WDT_CTRL_PSEL_SIZE	5
#define SM_KEY_OFFSET			24
#define SM_KEY_SIZE				8


/* Bitfields in EIC IER/IDR/IMR/ISR/ICR and MODE/EDGE/LEVEL/FILTER/ASYNC */
#define SM_INT0_OFFSET				0
#define SM_INT0_SIZE				1
#define SM_INT1_OFFSET				1
#define SM_INT1_SIZE				1
#define SM_INT2_OFFSET				2
#define SM_INT2_SIZE				1
#define SM_INT3_OFFSET				3
#define SM_INT3_SIZE				1
#define SM_INT4_OFFSET				4
#define SM_INT4_SIZE				1
#define SM_INT5_OFFSET				5
#define SM_INT5_SIZE				1
#define SM_INT6_OFFSET				6
#define SM_INT6_SIZE				1
#define SM_INT7_OFFSET				7
#define SM_INT7_SIZE				1
#define SM_NMI_OFFSET				8
#define SM_NMI_SIZE					1

/* Bitfields in EIM_TEST */
#define SM_TESTEN_OFFSET			31
#define SM_TESTEN_SIZE				1


/* Bit manipulation macros */
#define SM_BIT(name)					\
	(1 << SM_##name##_OFFSET)
#define SM_BF(name,value)				\
	(((value) & ((1 << SM_##name##_SIZE) - 1))	\
	 << SM_##name##_OFFSET)
#define SM_BFEXT(name,value)				\
	(((value) >> SM_##name##_OFFSET)		\
	 & ((1 << SM_##name##_SIZE) - 1))
#define SM_BFINS(name,value,old)			\
	(((old) & ~(((1 << SM_##name##_SIZE) - 1)	\
		    << SM_##name##_OFFSET))		\
	 | SM_BF(name,value))

/* Register access macros */
#define sm_readl(reg)					\
	readl((void *)SM_BASE + SM_##reg)
#define sm_writel(reg,value)				\
	writel((value), (void *)SM_BASE + SM_##reg)

#endif /* __CPU_AT32UC_SM_H__ */
