/*
 * Copyright (C) 2008 Atmel Corporation
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
#ifndef __ASM_AVR32_ARCH_HMATRIX_H__
#define __ASM_AVR32_ARCH_HMATRIX_H__

#include <asm/hmatrix-common.h>

/* Bitfields in SFR5 (EBI) */
#define HMATRIX_EBI_SDRAM_ENABLE_OFFSET		1
#define HMATRIX_EBI_SDRAM_ENABLE_SIZE		1

/* HSB masters */
#define HMATRIX_MASTER_CPU_DATA				0
#define HMATRIX_MASTER_CPU_INSTRUCTIONS		1
#define HMATRIX_MASTER_CPU_SAB				2
#define HMATRIX_MASTER_PDCA					3
#define HMATRIX_MASTER_MACB_DMA				4
#define HMATRIX_MASTER_USBB_DMA				5

/* HSB slaves */
#define HMATRIX_SLAVE_INT_FLASH				0
#define HMATRIX_SLAVE_HSB_PB_BR0			1
#define HMATRIX_SLAVE_HSB_PB_BR1			2
#define HMATRIX_SLAVE_INT_SRAM				3
#define HMATRIX_SLAVE_USBB_DPRAM			4
#define HMATRIX_SLAVE_EBI					5

#endif /* __ASM_AVR32_ARCH_HMATRIX_H__ */
