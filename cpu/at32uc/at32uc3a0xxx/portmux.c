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
#include <common.h>

#include <asm/io.h>

#include <asm/arch/chip-features.h>
#include <asm/arch/memory-map.h>
#include <asm/arch/portmux.h>

/*
 * Lots of small functions here. We depend on --gc-sections getting
 * rid of the ones we don't need.
 */
void portmux_enable_ebi(unsigned int bus_width, unsigned int addr_width, unsigned long flags, unsigned long drive_strength)
{
	/* Added 20100624 Mjan
	 * TODO: This is a hack.
	 * This should be done in another way, of course.
	 */
	/*
	 * GPIO pins to be set to enable all EBI pins on Mizar:
	 * PIN 42-46	function C port1 mask 00 00 7c 00
	 *
	 * PIN 70		function A port2 mask 00 00 00 40
	 * PIN 72-81	function A port2 mask 00 03 ff 00
	 * PIN 83-84	function A port2 mask 0? ?? 00 00
	 * PIN 86-87	function A port2 mask 00 c0 00 00
	 *
	 * >PIN 90-95	function A port2 mask fc 00 00 00
	 * 						port2 totaling: fcdbff40
	 * >PIN 96-105	function A port3 mask 00 00 03 ff
	 *
	 * PIN 106		function A port3 mask 00 00 04 00
	 * PIN 109		function A port3 mask 00 00 20 00
	 */
/*
{*
* Clock related bits
* {pin = 42 '*', function = 2 '\002'},
* {pin = 43 '+', function = 2 '\002'}}
*
* Control bits
* {pin = 44 ',', function = 2 '\002'},
* {pin = 45 '-', function = 2 '\002'},
* {pin = 46 '.', function = 2 '\002'},
*
* SDA
* {pin = 48 '0', function = 2 '\002'},
*
* Data mask bits (also pin 109)
* {pin = 70 'F', function = 0 '\0'},
*
* Addr bits
* {pin = 72 'H', function = 0 '\0'},
* {pin = 73 'I', function = 0 '\0'},
* {pin = 74 'J', function = 0 '\0'},
* {pin = 75 'K', function = 0 '\0'},
* {pin = 76 'L', function = 0 '\0'},
* {pin = 77 'M', function = 0 '\0'},
* {pin = 78 'N', function = 0 '\0'},
* {pin = 79 'O', function = 0 '\0'},
* {pin = 80 'P', function = 0 '\0'},
* {pin = 81 'Q', function = 0 '\0'},
* {pin = 83 'S', function = 0 '\0'},
* {pin = 84 'T', function = 0 '\0'},
*
* Bank address bits
* {pin = 86 'V', function = 0 '\0'},
* {pin = 87 'W', function = 0 '\0'},
*
* Data bits
* {pin = 90 'Z', function = 0 '\0'},
* {pin = 91 '[', function = 0 '\0'},
* {pin = 92 '\\', function = 0 '\0'},
* {pin = 93 ']', function = 0 '\0'},
* {pin = 94 '^', function = 0 '\0'},
* {pin = 95 '_', function = 0 '\0'},
* {pin = 96 '`', function = 0 '\0'},
* {pin = 97 'a', function = 0 '\0'},
* {pin = 98 'b', function = 0 '\0'},
* {pin = 99 'c', function = 0 '\0'},
* {pin = 100 'd', function = 0 '\0'},
* {pin = 101 'e', function = 0 '\0'},
* {pin = 102 'f', function = 0 '\0'},
* {pin = 103 'g', function = 0 '\0'},
* {pin = 104 'h', function = 0 '\0'},
* {pin = 105 'i', function = 0 '\0'},
*
* Control bit (together with 44, 45, 46)
* {pin = 106 'j', function = 0 '\0'},
*
* Data mask (also pin 70)
* {pin = 109 'm', function = 0 '\0'},
*/

	portmux_select_peripheral(PORTMUX_PORT_B,
		(1 << (42-32)) |
		(1 << (43-32)) |
		(1 << (44-32)) |
		(1 << (45-32)) |
		(1 << (46-32)) |
		(1 << (48-32)),
		PORTMUX_FUNC_C, 0);

	portmux_select_peripheral(PORTMUX_PORT_C,
		(1 << (70-64)) |
		(1 << (72-64)) |
		(1 << (73-64)) |
		(1 << (74-64)) |
		(1 << (75-64)) |
		(1 << (76-64)) |
		(1 << (77-64)) |
		(1 << (78-64)) |
		(1 << (79-64)) |
		(1 << (80-64)) |
		(1 << (81-64)) |
		(1 << (82-64)) |
		(1 << (83-64)) |
		(1 << (84-64)) |
		(1 << (86-64)) |
		(1 << (87-64)) |
		(1 << (90-64)) |
		(1 << (91-64)) |
		(1 << (92-64)) |
		(1 << (93-64)) |
		(1 << (94-64)) |
		(1 << (95-64)),
		PORTMUX_FUNC_A, 0);

	portmux_select_peripheral(PORTMUX_PORT_X,
		(1 << (96 - 96)) |
		(1 << (97 - 96)) |
		(1 << (98 - 96)) |
		(1 << (99 - 96)) |
		(1 << (100 - 96)) |
		(1 << (101 - 96)) |
		(1 << (102 - 96)) |
		(1 << (103 - 96)) |
		(1 << (104 - 96)) |
		(1 << (105 - 96)) |
		(1 << (106 - 96)) |
		(1 << (109 - 96)),
		PORTMUX_FUNC_A, 0);
}

#ifdef AT32UC3A0xxx_CHIP_HAS_MACB
void portmux_enable_macb(unsigned long flags, unsigned long drive_strength)
{
	unsigned long portb_mask;

	portb_mask = (1 << 2)	/* TXD0	*/
		| (1 << 3)	/* TXD1	*/
		| (1 << 1)	/* TXEN	*/
		| (1 << 0)	/* TXCK */
		| (1 << 5)	/* RXD0	*/
		| (1 << 6)	/* RXD1	*/
		| (1 << 7)	/* RXER	*/
		| (1 << 15)	/* RXDV	*/
		| (1 << 8)	/* MDC	*/
		| (1 << 9);	/* MDIO	*/

	if (flags & PORTMUX_MACB_MII)
		portb_mask |= (1 << 16)	/* COL	*/
			| (1 << 4)	/* CRS	*/
			| (1 << 12)	/* TXER	*/
			| (1 << 10)	/* TXD2	*/
			| (1 << 11)	/* TXD3 */
			| (1 << 13)	/* RXD2	*/
			| (1 << 14)	/* RXD3	*/
			| (1 << 17);	/* RXCK	*/

	if (flags & PORTMUX_MACB_SPEED)
		portb_mask |= (1 << 18);/* SPD	*/

	/* REVISIT: Some pins are probably pure outputs */
	portmux_select_peripheral(PORTMUX_PORT_B, portb_mask,
			PORTMUX_FUNC_A, PORTMUX_BUSKEEPER);
}

#endif


#ifdef AT32UC3A0xxx_CHIP_HAS_SPI
void portmux_enable_spi0(unsigned long cs_mask, unsigned long drive_strength)
{
	unsigned long pin_mask;

	/* MOSI and SCK */
	portmux_select_peripheral(PORTMUX_PORT_A, (1 << 12) | (1 << 13),
			PORTMUX_FUNC_A, 0);
	/* MISO may float */
	portmux_select_peripheral(PORTMUX_PORT_A, 1 << 11,
			PORTMUX_FUNC_A, PORTMUX_BUSKEEPER);

	/* Set up NPCSx as GPIO outputs, initially high */
	pin_mask = 0;
	if (cs_mask & (1 << 0))
		pin_mask |= 1 << 10;
	if (cs_mask & (1 << 1))
		pin_mask |= 1 << 8;
	if (cs_mask & (1 << 2))
		pin_mask |= 1 << 9;
	if (cs_mask & (1 << 3))
		pin_mask |= 1 << 7;

	portmux_select_gpio(PORTMUX_PORT_A, pin_mask,
			PORTMUX_DIR_OUTPUT | PORTMUX_INIT_HIGH);
}

void portmux_enable_spi1(unsigned long cs_mask, unsigned long drive_strength)
{
	unsigned long pin_mask;

	/* MOSI and SCK */
	portmux_select_peripheral(PORTMUX_PORT_B, (1 << 16) | (1 << 15),
			PORTMUX_FUNC_B, 0);
	//~ /* MISO may float */
	portmux_select_peripheral(PORTMUX_PORT_B, 1 << 17,
			PORTMUX_FUNC_B, PORTMUX_BUSKEEPER);

	/* Set up NPCSx as GPIO outputs, initially high */
	pin_mask = 0;
	if (cs_mask & (1 << 0))
		pin_mask |= 1 << 14;
	if (cs_mask & (1 << 1))
		pin_mask |= 1 << 18;
	if (cs_mask & (1 << 2))
		pin_mask |= 1 << 19;
	if (cs_mask & (1 << 3))
		pin_mask |= 1 << 20;

	portmux_select_gpio(PORTMUX_PORT_A, pin_mask,
			PORTMUX_DIR_OUTPUT | PORTMUX_INIT_HIGH);
}
#endif

