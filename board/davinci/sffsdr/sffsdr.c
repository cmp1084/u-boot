/*
 * Copyright (C) 2007 Sergey Kubushyn <ksi@koi8.net>
 *
 * Copyright (C) 2008 Lyrtech <www.lyrtech.com>
 * Copyright (C) 2008 Philip Balister, OpenSDR <philip@opensdr.com>
 *
 * Parts are shamelessly stolen from various TI sources, original copyright
 * follows:
 *
 * Copyright (C) 2004 Texas Instruments.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <common.h>
#include <i2c.h>
#include <asm/arch/hardware.h>
#include <asm/arch/emac_defs.h>
#include "../common/psc.h"
#include "../common/misc.h"

#define DAVINCI_A3CR     (0x01E00014)	/* EMIF-A CS3 config register. */
#define DAVINCI_A3CR_VAL (0x3FFFFFFD)	/* EMIF-A CS3 value for FPGA. */

#define INTEGRITY_SYSCFG_OFFSET    0x7E8
#define INTEGRITY_CHECKWORD_OFFSET 0x7F8
#define INTEGRITY_CHECKWORD_VALUE  0x10ADBEEF

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	/* arch number of the board */
	gd->bd->bi_arch_number = MACH_TYPE_SFFSDR;

	/* address of boot parameters */
	gd->bd->bi_boot_params = LINUX_BOOT_PARAM_ADDR;

	/* Workaround for TMS320DM6446 errata 1.3.22 */
	REG(PSC_SILVER_BULLET) = 0;

	/* Power on required peripherals */
	lpsc_on(DAVINCI_LPSC_EMAC);
	lpsc_on(DAVINCI_LPSC_EMAC_WRAPPER);
	lpsc_on(DAVINCI_LPSC_MDIO);
	lpsc_on(DAVINCI_LPSC_I2C);
	lpsc_on(DAVINCI_LPSC_UART0);
	lpsc_on(DAVINCI_LPSC_TIMER1);
	lpsc_on(DAVINCI_LPSC_GPIO);

#if !defined(CFG_USE_DSPLINK)
	/* Powerup the DSP */
	dsp_on();
#endif /* CFG_USE_DSPLINK */

	/* Bringup UART0 out of reset */
	REG(UART0_PWREMU_MGMT) = 0x0000e003;

	/* Enable GIO3.3V cells used for EMAC */
	REG(VDD3P3V_PWDN) = 0;

	/* Enable UART0 MUX lines */
	REG(PINMUX1) |= 1;

	/* Enable EMAC and AEMIF pins */
	REG(PINMUX0) = 0x80000c1f;

	/* Enable I2C pin Mux */
	REG(PINMUX1) |= (1 << 7);

	/* Set the Bus Priority Register to appropriate value */
	REG(VBPR) = 0x20;

	timer_init();

	return(0);
}

/* Read ethernet MAC address from Integrity data structure inside EEPROM.
 * Returns 1 if found, 0 otherwise.
 */
static int sffsdr_read_mac_address(uint8_t *buf)
{
	u_int32_t value, mac[2], address;

	/* Read Integrity data structure checkword. */
	if (i2c_read(CFG_I2C_EEPROM_ADDR, INTEGRITY_CHECKWORD_OFFSET,
		     CFG_I2C_EEPROM_ADDR_LEN, (uint8_t *) &value, 4))
		goto err;
	if (value != INTEGRITY_CHECKWORD_VALUE)
		return 0;

	/* Read SYSCFG structure offset. */
	if (i2c_read(CFG_I2C_EEPROM_ADDR, INTEGRITY_SYSCFG_OFFSET,
		     CFG_I2C_EEPROM_ADDR_LEN, (uint8_t *) &value, 4))
		goto err;
	address = 0x800 + (int) value; /* Address of SYSCFG structure. */

	/* Read NET CONFIG structure offset. */
	if (i2c_read(CFG_I2C_EEPROM_ADDR, address,
		     CFG_I2C_EEPROM_ADDR_LEN, (uint8_t *) &value, 4))
		goto err;
	address = 0x800 + (int) value; /* Address of NET CONFIG structure. */
	address += 12; /* Address of NET INTERFACE CONFIG structure. */

	/* Read NET INTERFACE CONFIG 2 structure offset. */
	if (i2c_read(CFG_I2C_EEPROM_ADDR, address,
		     CFG_I2C_EEPROM_ADDR_LEN, (uint8_t *) &value, 4))
		goto err;
	address = 0x800 + 16 + (int) value;	/* Address of NET INTERFACE
						 * CONFIG 2 structure. */

	/* Read MAC address. */
	if (i2c_read(CFG_I2C_EEPROM_ADDR, address,
		     CFG_I2C_EEPROM_ADDR_LEN, (uint8_t *) &mac[0], 8))
		goto err;

	buf[0] = mac[0] >> 24;
	buf[1] = mac[0] >> 16;
	buf[2] = mac[0] >> 8;
	buf[3] = mac[0];
	buf[4] = mac[1] >> 24;
	buf[5] = mac[1] >> 16;

	return 1; /* Found */

err:
	printf("Read from EEPROM @ 0x%02x failed\n", CFG_I2C_EEPROM_ADDR);
	return 0;
}

/* Platform dependent initialisation. */
int misc_init_r(void)
{
	uint8_t i2cbuf;
	uint8_t eeprom_enetaddr[6];

	/* EMIF-A CS3 configuration for FPGA. */
	REG(DAVINCI_A3CR) = DAVINCI_A3CR_VAL;

	dv_display_clk_infos();

	/* Configure I2C switch (PCA9543) to enable channel 0. */
	i2cbuf = CFG_I2C_PCA9543_ENABLE_CH0;
	if (i2c_write(CFG_I2C_PCA9543_ADDR, 0,
		      CFG_I2C_PCA9543_ADDR_LEN, &i2cbuf, 1)) {
		printf("Write to MUX @ 0x%02x failed\n", CFG_I2C_PCA9543_ADDR);
		return 1;
	}

	/* Read Ethernet MAC address from EEPROM if available. */
	if (sffsdr_read_mac_address(eeprom_enetaddr))
		dv_configure_mac_address(eeprom_enetaddr);

	if (!eth_hw_init())
		printf("Ethernet init failed\n");

	return(0);
}
