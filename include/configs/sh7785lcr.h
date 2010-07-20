/*
 * Configuation settings for the Renesas Technology R0P7785LC0011RL board
 *
 * Copyright (C) 2008 Yoshihiro Shimoda <shimoda.yoshihiro@renesas.com>
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

#ifndef __SH7785LCR_H
#define __SH7785LCR_H

#undef DEBUG
#define CONFIG_SH		1
#define CONFIG_SH4A		1
#define CONFIG_CPU_SH7785	1
#define CONFIG_SH7785LCR	1

#define CONFIG_CMD_FLASH
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_PCI
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_NFS
#define CONFIG_CMD_DFL
#define CONFIG_CMD_SDRAM
#define CONFIG_CMD_RUN
#define CONFIG_CMD_ENV

#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION
#define CONFIG_MAC_PARTITION

#define CONFIG_BAUDRATE		115200
#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTARGS		"console=ttySC1,115200 root=/dev/nfs ip=dhcp"

#define CONFIG_EXTRA_ENV_SETTINGS					\
	"bootdevice=0:1\0"						\
	"usbload=usb reset;usbboot;usb stop;bootm\0"

#define CONFIG_VERSION_VARIABLE
#undef	CONFIG_SHOW_BOOT_PROGRESS

/* MEMORY */
#define SH7785LCR_SDRAM_BASE		(0x08000000)
#define SH7785LCR_SDRAM_SIZE		(128 * 1024 * 1024)
#define SH7785LCR_FLASH_BASE_1		(0xa0000000)
#define SH7785LCR_FLASH_BANK_SIZE	(64 * 1024 * 1024)
#define SH7785LCR_USB_BASE		(0xb4000000)

#define CFG_LONGHELP
#define CFG_PROMPT		"=> "
#define CFG_CBSIZE		256
#define CFG_PBSIZE		256
#define CFG_MAXARGS		16
#define CFG_BARGSIZE		512
#define CFG_BAUDRATE_TABLE	{ 115200 }

/* SCIF */
#define CONFIG_SCIF_CONSOLE	1
#define CONFIG_CONS_SCIF1	1
#define CONFIG_SCIF_EXT_CLOCK	1
#undef	CFG_CONSOLE_INFO_QUIET
#undef	CFG_CONSOLE_OVERWRITE_ROUTINE
#undef	CFG_CONSOLE_ENV_OVERWRITE


#define CFG_MEMTEST_START	(SH7785LCR_SDRAM_BASE)
#define CFG_MEMTEST_END		(CFG_MEMTEST_START + \
					(SH7785LCR_SDRAM_SIZE) - \
					 4 * 1024 * 1024)
#undef	CFG_ALT_MEMTEST
#undef	CFG_MEMTEST_SCRATCH
#undef	CFG_LOADS_BAUD_CHANGE

#define CFG_SDRAM_BASE	(SH7785LCR_SDRAM_BASE)
#define CFG_SDRAM_SIZE	(SH7785LCR_SDRAM_SIZE)
#define CFG_LOAD_ADDR	(CFG_SDRAM_BASE + 16 * 1024 * 1024)

#define CFG_MONITOR_BASE	(SH7785LCR_FLASH_BASE_1)
#define CFG_MONITOR_LEN		(512 * 1024)
#define CFG_MALLOC_LEN		(512 * 1024)
#define CFG_GBL_DATA_SIZE	(256)
#define CFG_BOOTMAPSZ		(8 * 1024 * 1024)

/* FLASH */
#define CONFIG_FLASH_CFI_DRIVER
#define CFG_FLASH_CFI
#undef	CFG_FLASH_QUIET_TEST
#define CFG_FLASH_EMPTY_INFO
#define CFG_FLASH_BASE		(SH7785LCR_FLASH_BASE_1)
#define CFG_MAX_FLASH_SECT	512

#define CFG_MAX_FLASH_BANKS	1
#define CFG_FLASH_BANKS_LIST	{ CFG_FLASH_BASE + \
				 (0 * SH7785LCR_FLASH_BANK_SIZE) }

#define CFG_FLASH_ERASE_TOUT	(3 * 1000)
#define CFG_FLASH_WRITE_TOUT	(3 * 1000)
#define CFG_FLASH_LOCK_TOUT	(3 * 1000)
#define CFG_FLASH_UNLOCK_TOUT	(3 * 1000)

#undef	CFG_FLASH_PROTECTION
#undef	CFG_DIRECT_FLASH_TFTP

/* R8A66597 */
#define LITTLEENDIAN			/* for include/usb.h */
#define CONFIG_USB_R8A66597_HCD
#define CONFIG_R8A66597_BASE_ADDR	SH7785LCR_USB_BASE
#define CONFIG_R8A66597_XTAL		0x0000	/* 12MHz */
#define CONFIG_R8A66597_LDRV		0x8000	/* 3.3V */
#define CONFIG_R8A66597_ENDIAN		0x0000	/* little */

/* PCI Controller */
#define CONFIG_PCI
#define CONFIG_SH4_PCI
#define CONFIG_SH7780_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW	1

#define CONFIG_PCI_MEM_BUS	0xFD000000	/* Memory space base addr */
#define CONFIG_PCI_MEM_PHYS	CONFIG_PCI_MEM_BUS
#define CONFIG_PCI_MEM_SIZE	0x01000000	/* Size of Memory window */

#define CONFIG_PCI_IO_BUS	0xFE200000	/* IO space base address */
#define CONFIG_PCI_IO_PHYS	CONFIG_PCI_IO_BUS
#define CONFIG_PCI_IO_SIZE	0x00200000	/* Size of IO window */

/* Network device (RTL8169) support */
#define CONFIG_NET_MULTI
#define CONFIG_RTL8169

/* ENV setting */
#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_OVERWRITE	1
#define CONFIG_ENV_SECT_SIZE	(256 * 1024)
#define CONFIG_ENV_SIZE		(CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_ADDR		(CFG_FLASH_BASE + CFG_MONITOR_LEN)
#define CONFIG_ENV_OFFSET		(CONFIG_ENV_ADDR - CFG_FLASH_BASE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SECT_SIZE)

/* Board Clock */
/* The SCIF used external clock. system clock only used timer. */
#define CONFIG_SYS_CLK_FREQ	50000000
#define TMU_CLK_DIVIDER		4
#define CFG_HZ			(CONFIG_SYS_CLK_FREQ / TMU_CLK_DIVIDER)

#endif	/* __SH7785LCR_H */
