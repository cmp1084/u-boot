/*
 * Register definitions for flash controller
 */
#ifndef __ASM_AVR32_FLASHC_H__
#define __ASM_AVR32_FLASHC_H__

/* FLASHC register offsets */
#define FLASHC_FCR				0x0000
#define FLASHC_FCMD				0x0004
#define FLASHC_FSR				0x0008
#define FLASHC_FGPFRHI			0x000c
#define FLASHC_FGPFRLO			0x0010

/* Bitfields in FCR and FSR */
#define FLASHC_FRDY_OFFSET		0
#define FLASHC_FRDY_SIZE		1
#define FLASHC_LOCKE_OFFSET		2
#define FLASHC_LOCKE_SIZE		1
#define FLASHC_PROGE_OFFSET		3
#define FLASHC_PROGE_SIZE		1

/* Bitfields in FCR */
#define FLASHC_FWS_OFFSET		6
#define FLASHC_FWS_SIZE			1
#define FLASHC_SASD_OFFSET		8
#define FLASHC_SASD_SIZE		1

/* Bitfields in FCMD */
#define FLASHC_CMD_OFFSET		0
#define FLASHC_CMD_SIZE			6
#define FLASHC_PAGEN_OFFSET		8
#define FLASHC_PAGEN_SIZE		16
#define FLASHC_KEY_OFFSET		24
#define FLASHC_KEY_SIZE			8

/* Bitfields in FSR */
#define FLASHC_SECURITY_OFFSET		4
#define FLASHC_SECURITY_SIZE		1
#define FLASHC_QPRR_OFFSET			5
#define FLASHC_QPRR_SIZE			1
#define FLASHC_FSZ_OFFSET			13
#define FLASHC_FSZ_SIZE				3
#define FLASHC_LOCK_OFFSET			16
#define FLASHC_LOCK_SIZE			16

#define FLASHC_NOP 	0 /*No operation*/
#define FLASHC_WP 	1 /*Write Page*/
#define FLASHC_EP	2 /*Erase Page*/
#define FLASHC_CPB 	3 /*Clear Page Buffer*/
#define FLASHC_LP 	4 /*Lock region containing given Page*/
#define FLASHC_UP 	5 /*Unlock region containing given Page*/
#define FLASHC_EA 	6 /*Erase All*/
#define FLASHC_WGPB	7 /*Write General-Purpose Fuse Bit*/
#define FLASHC_EGPB 	8 /*Erase General-Purpose Fuse Bit*/
#define FLASHC_SSB 	9 /*Set Security Bit*/
#define FLASHC_PGPFB 	10 /*Program GP Fuse Byte*/
#define FLASHC_EAGPF 	11 /*Erase All GPFuses*/
#define FLASHC_QPR 	12 /*Quick Page Read*/
#define FLASHC_WUP	13 /*Write User Page*/
#define FLASHC_EUP	14 /*Erase User Page*/
#define FLASHC_QPRUP 	15 /*Quick Page Read User Page*/


/* Bit manipulation macros */
#define FLASHC_BIT(name)					\
	(1 << FLASHC_##name##_OFFSET)
#define FLASHC_BF(name,value)					\
	(((value) & ((1 << FLASHC_##name##_SIZE) - 1))		\
	 << FLASHC_##name##_OFFSET)
#define FLASHC_BFEXT(name,value)				\
	(((value) >> FLASHC_##name##_OFFSET)			\
	 & ((1 << FLASHC_##name##_SIZE) - 1))
#define FLASHC_BFINS(name,value,old)				\
	(((old) & ~(((1 << FLASHC_##name##_SIZE) - 1)		\
		    << FLASHC_##name##_OFFSET))			\
	 | FLASHC_BF(name,value))

/* Register access macros */
#define flashc_readl(reg)					\
	readl((void *)FLASHC_BASE + FLASHC_##reg)
#define flashc_writel(reg,value)				\
	writel((value), (void *)FLASHC_BASE + FLASHC_##reg)

void flash_set_waitstate(int waitstate);

#endif /* __ASM_AVR32_FLASHC_H__ */
