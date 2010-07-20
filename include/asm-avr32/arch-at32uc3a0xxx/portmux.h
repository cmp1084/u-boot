/*
 * Copyright (C) 2006, 2008 Atmel Corporation
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
#ifndef __ASM_AVR32_ARCH_PORTMUX_H__
#define __ASM_AVR32_ARCH_PORTMUX_H__

#include <asm/arch-common/portmux-gpio.h>
#include <asm/arch/memory-map.h>

#define PORTMUX_PORT(x) ( (void *) (GPIO_BASE + (x) * 0x0100) )
#define PORTMUX_PORT_A	PORTMUX_PORT(0)
#define PORTMUX_PORT_B	PORTMUX_PORT(1)
#define PORTMUX_PORT_C	PORTMUX_PORT(2)
//Added PORTMUX_PORT_X 20100706 Mjan
#define PORTMUX_PORT_X	PORTMUX_PORT(3)

void portmux_enable_ebi(unsigned int bus_width, unsigned int addr_width, unsigned long flags, unsigned long drive_strength);

#define PORTMUX_EBI_CS(x)	(1 << (x))
#define PORTMUX_EBI_NAND	(1 << 6)
#define PORTMUX_EBI_CF(x)	(1 << ((x) + 7))
#define PORTMUX_EBI_NWAIT	(1 << 9)

#ifdef AT32UC3A0xxx_CHIP_HAS_USART
static inline void portmux_enable_usart0(unsigned long drive_strength)
{
#warning "Fix these constants, something like USART0_RX, USART0_TX"
	portmux_select_peripheral(PORTMUX_PORT_A, (1 << 0) | (1 << 1),	//TODO: Fix constants 20100630 Mjan
			PORTMUX_FUNC_A, 0);
}

static inline void portmux_enable_usart1(unsigned long drive_strength)
{
	portmux_select_peripheral(PORTMUX_PORT_A, (1 << 5) | (1 << 6),
			PORTMUX_FUNC_A, 0);
}

static inline void portmux_enable_usart2(unsigned long drive_strength)
{
	portmux_select_peripheral(PORTMUX_PORT_B, (1 << 29) | (1 << 30),
			PORTMUX_FUNC_A, 0);
}

static inline void portmux_enable_usart3(unsigned long drive_strength)
{
	portmux_select_peripheral(PORTMUX_PORT_B, (1 << 10) | (1 << 11),
			PORTMUX_FUNC_B, 0);
}
#endif
#ifdef AT32UC3A0xxx_CHIP_HAS_MACB
void portmux_enable_macb(unsigned long flags, unsigned long drive_strength);

#define PORTMUX_MACB_RMII	(0)
#define PORTMUX_MACB_MII	(1 << 0)
#define PORTMUX_MACB_SPEED	(1 << 1)

#endif
#ifdef AT32UC3A0xxx_CHIP_HAS_SPI
void portmux_enable_spi0(unsigned long cs_mask, unsigned long drive_strength);
void portmux_enable_spi1(unsigned long cs_mask, unsigned long drive_strength);
#endif

#endif /* __ASM_AVR32_ARCH_PORTMUX_H__ */

