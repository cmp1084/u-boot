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
#ifndef __ASM_AVR32_ARCH_GPIO_H__
#define __ASM_AVR32_ARCH_GPIO_H__

#include <asm/arch/chip-features.h>
#include <asm/arch/memory-map.h>

#define NR_GPIO_CONTROLLERS	4

static inline void * pio_pin_to_port(unsigned int pin)
{
	unsigned port_no;

	port_no = pin / 32;
	if (port_no >= (NR_GPIO_CONTROLLERS - 1)) {
		return NULL;
	}

	return GPIO_PORT(port_no);
}

#include <asm/arch-common/portmux-pio.h>

#endif /* __ASM_AVR32_ARCH_GPIO_H__ */
