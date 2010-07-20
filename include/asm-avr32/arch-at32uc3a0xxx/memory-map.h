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
#ifndef __AT32UC3A0512_MEMORY_MAP_H__
#define __AT32UC3A0512_MEMORY_MAP_H__

/* Internal and external memories */
#define EBI_SRAM_CS0_BASE		0xc0000000
#define EBI_SRAM_CS0_SIZE		0x01000000
#define EBI_SRAM_CS2_BASE		0xc8000000
#define EBI_SRAM_CS2_SIZE		0x01000000
#define EBI_SRAM_CS3_BASE		0xcc000000
#define EBI_SRAM_CS3_SIZE		0x01000000
#define EBI_SRAM_CS1_BASE		0xd0000000
#define EBI_SRAM_CS1_SIZE		0x02000000	//was: 0x08000000 20100629 Mjan

#define EBI_SDRAM_BASE			EBI_SRAM_CS1_BASE //This is correct, 20100625 Mjan
#define EBI_SDRAM_SIZE			(EBI_SRAM_CS1_SIZE >> 2)	//32Mb, word. Was: EBI_SRAM_CS1_SIZE 20100624 Mjan

#define INTERNAL_SRAM_BASE		0x00000000
#define INTERNAL_SRAM_SIZE		0x00010000

/* Devices on HSB bus */
#define USBB_SLAVE_BASE			0xE0000000

/* Devices on Peripheral Bus B (PBB) */
#define USBB_CONFIG_BASE		0xFFFE0000
#define HMATRIX_BASE			0xFFFE1000
#define FLASHC_BASE				0xFFFE1400
#define MACB_BASE				0xFFFE1800
#define SMC_BASE				0xFFFE1C00
#define SDRAMC_BASE				0xFFFE2000

/* Devices on Peripheral Bus A (PBA) */
#define SM_BASE					0xFFFF0000	/* This base addr is used to reach PM, RTC, WDT et al. with an offset, e.g. 0x0c00 for PM. Quite unnecessary 20100716 Mjan */
#define PCDA_BASE				0xFFFF0000
#define INTC_BASE				0xFFFF0800
#define PM_BASE					0xFFFF0C00
#define RTC_BASE				0xFFFF0D00
#define WDT_BASE				0xFFFF0D30
#define EIC_BASE				0xFFFF0D80
#define GPIO_BASE				0xFFFF1000
#define USART0_BASE				0xFFFF1400
#define USART1_BASE				0xFFFF1800
#define USART2_BASE				0xFFFF1C00
#define USART3_BASE				0xFFFF2000
#define SPI0_BASE				0xFFFF2400
#define SPI1_BASE				0xFFFF2800
#define TWI_BASE				0xFFFF2C00
#define PWM_BASE				0xFFFF3000
#define SSC_BASE				0xFFFF3400
#define TC_BASE					0xFFFF3800
#define ADC_BASE				0xFFFF3C00

#define GPIO_PORT(x) ( (void *) (GPIO_BASE + (x) * 0x0100) )

#endif /* __AT32UC3A0512_MEMORY_MAP_H__ */
