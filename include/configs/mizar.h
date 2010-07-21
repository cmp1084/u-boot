/*
 * Copyright (C) 2005-2006 Atmel Corporation
 *
 * Configuration settings for the ATEVK1100 evaluation kit
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
#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/arch/memory-map.h>

#define CONFIG_AVR32		1
#define CONFIG_AT32UC		1
#define CONFIG_AT32UC3A0xxx	1
#define CONFIG_ATEVK1100	0
#define CONFIG_MIZAR 		1

/* Timer clock frequency. We're using the CPU-internal COUNT register
 * for this, so this is equivalent to the CPU core clock frequency */
#define CFG_HZ 1000

/*
 * Set up the PLL to run at 132 MHz, and the CPU, PBA and PBB to run at PLL/2.
 * fVCO = (CFG_OSC0_HZ * CFG_PLL0_MUL) / CFG_PLL0_DIV
 * fPLL = fVCO / ((CFG_PLL0_OPT & 0x2) ? 2 : 1)
 */
  // Supported frequencies:
   // Fosc0 mul div PLL div2_en cpu_f pba_f   Comment
   //					opt[1]
   //  12   15   1  192     1     12    12
   //  12    9   3   40     1     20    20    PLL out of spec
   //  12   15   1  192     1     24    12
   //  12    9   1  120     1     30    15
   //  12    9   3   40     0     40    20    PLL out of spec
   //  12   15   1  192     1     48    12
   //  12   15   1  192     1     48    24
   //  12    8   1  108     1     54    27
   //  12    9   1  120     1     60    15
   //  12    9   1  120     1     60    30
   //  12   10   1  132     1     66    16.5

#define CONFIG_PLL					1	//20100624 Mjan, was: 1. Can not be set to 0 as #ifdef is used to determine if PLL is going to be used
#undef CONFIG_PLL					//Need to #undef CONFIG_PLL if PLL is not to be used
//~ #define CFG_POWER_MANAGER			1
#define CFG_OSC0_HZ					12000000UL
#define CFG_PLL0_DIV				1 //was 1 20100716 Mjan
#define CFG_PLL0_MUL				11 //10	//was 11 20100716 Mjan
#define CFG_PLL0_SUPPRESS_CYCLES	64

/* The PLLOPT register controls the PLL like this:
 * Select the operating range for the PLL.
 * PLLOPT[0]: Select the VCO frequency range.
 * PLLOPT[1]: Enable the extra output divider.
 * PLLOPT[2]: Disable the Wide-Bandwidth mode (Wide-Bandwidth mode allows a faster startup time and out-of-lock time).
 * We want to run the cpu at 66 MHz, and the fVCO of the PLL at 132 MHz. */
#define CFG_PLL0_OPT 0x07	//80 Mhz <fvco<180 Mhz, fPLL = fvco / 2

/* Set the CPU running at:
 * PLL / (2^CFG_CLKDIV_CPU) = CPU MHz */
#define CFG_CLKDIV_CPU 0	//was 1 20100719 Mjan

/* Set the PBA running at:
 * PLL / (2^CFG_CLKDIV_PBA) = PBA MHz
 * On the atuc3a0512es, the maximum clock rate of PBA is 33 MHz. */
#define CFG_CLKDIV_PBA 1

/* Set the PBB running at:
 * PLL / (2^CFG_CLKDIV_PBB) = PBB MHz */
#define CFG_CLKDIV_PBB 0

#define CONFIG_USART0 1
#undef CONFIG_USART1
#undef CONFIG_USART2
#undef CONFIG_USART3

/* User serviceable stuff */
#define CONFIG_DOS_PARTITION		1
#define CONFIG_CMDLINE_TAG			1
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_INITRD_TAG			1
#define CONFIG_STACKSIZE			(4*2048)
#define CONFIG_BAUDRATE				38400
#define CONFIG_BOOTARGS	\
	"console=ttyS0 ip=dhcp root=/dev/mtdblk0 rootwait=1"
#define CONFIG_BOOTCOMMAND	\
	""	//Was: "dhcp; bootm $(fileaddr)" 20100716 Mjan

/*
 * Only interrupt autoboot if <space> is pressed. Otherwise, garbage
 * data on the serial line may interrupt the boot sequence.
 */
#define CONFIG_BOOTDELAY			1
#define CONFIG_AUTOBOOT				1
#define CONFIG_AUTOBOOT_KEYED		1
#define CONFIG_AUTOBOOT_PROMPT		\
	"Press SPACE to abort autoboot in %d seconds\n", bootdelay
#define CONFIG_AUTOBOOT_DELAY_STR	"d"
#define CONFIG_AUTOBOOT_STOP_STR	" "
#define CONFIG_BOOT_RETRY_TIME -1
//~ #define CONFIG_AUTO_COMPLETE
//#define CFG_MINIMUM_OUPUT	/* Dont output banner and memory info etc. at startup */
#define CFG_CONSOLE_INFO_QUIET
/*
 * After booting the board for the first time, new ethernet addresses
 * should be generated and assigned to the environment variables
 * "ethaddr" and "eth1addr". This is normally done during production.
 */
#define CONFIG_OVERWRITE_ETHADDR_ONCE	1
#define CONFIG_NET_MULTI				1

/*
 * BOOTP/DHCP options
 */
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY

/*****************************
 * Command line configuration.
 *****************************/
#include <config_cmd_default.h>

/* Add these commands */
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MMC		//Added 20100716 Mjan
#define CONFIG_CMD_FAT

/* Remove these 'uneccessary' commands */
#undef CONFIG_CMD_AUTOSCRIPT
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_SETGETDCR
#undef CONFIG_CMD_XIMG

/* Ethernet - RMII mode */
//#define CONFIG_MACB			1
//#define CONFIG_RMII			1

#define CONFIG_ATMEL_USART		1
#define CONFIG_ATMEL_SPI		1
//~ #define CONFIG_GENERIC_MMC	1
#define CONFIG_MMC				1
#define CONFIG_SPI_MMC			1
#define CONFIG_PORTMUX_GPIO		1
//~ #define CFG_NR_PIOS			5	//Removed 20100716 Mjan
#define CFG_SDRAMC				1

//~ #define CFG_SMC				0	//Removed 20100716 Mjan
//~ #undef CFG_SMC

#define CFG_DCACHE_LINESZ		32
#define CFG_ICACHE_LINESZ		32

#define CONFIG_NR_DRAM_BANKS	1

/* Internal flash on the microcontroller (TODO?) (512kB)*/
#define CFG_FLASH_BASE			0x80000000
#define CFG_FLASH_SIZE			0x00080000	//0x00800000	//Really??? 0x00800000 is not 512 kb?
#define CFG_MAX_FLASH_BANKS		1
#define CFG_MAX_FLASH_SECT		1024

#define CFG_MONITOR_BASE		CFG_FLASH_BASE
#define CFG_SRAM_DATA_BASE		0x00000004

#define CFG_INTRAM_BASE			INTERNAL_SRAM_BASE
#define CFG_INTRAM_SIZE			INTERNAL_SRAM_SIZE
/* TODO: Remove comment below, make sure SRAM is not used when SDRAM is supposed to be used. */
/* Not really SDRAM, maybe change to SRAM? */
#define CFG_SDRAM_BASE			EBI_SRAM_CS1_BASE	//Was: EBI_SRAM_CS2_BASE 20100625 Mjan

//TODO: Think about putting env on SD-card, 20100625 Mjan
#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_SIZE			0x400	//65536 woohaa 64 kb for env?! :/ Mjan
#define CONFIG_ENV_ADDR			(CFG_FLASH_BASE + CFG_FLASH_SIZE - CONFIG_ENV_SIZE)

#define CFG_INIT_SP_ADDR		(CFG_INTRAM_BASE + CFG_INTRAM_SIZE)

#define CFG_MALLOC_LEN			(256 * 1024)
#define CFG_DMA_ALLOC_LEN		(16384)

/* Allow 3MB (TODO: update) for the kernel run-time image */
#define CFG_LOAD_ADDR			(CFG_SDRAM_BASE + 0x00270000)
#define CFG_BOOTPARAMS_LEN		(16 * 1024)

/* Other configuration settings that shouldn't have to change all that often */
#define CFG_PROMPT				"U-Boot> "
#define CFG_CBSIZE				256
#define CFG_MAXARGS				16
#define CFG_PBSIZE				(CFG_CBSIZE + sizeof(CFG_PROMPT) + 16)
#define CFG_LONGHELP			1

#define CFG_MEMTEST_START		CFG_SDRAM_BASE
#define CFG_MEMTEST_END			(CFG_MEMTEST_START + EBI_SDRAM_SIZE >> 2) // - 0x00100000) //TODO: Do the - 0x00100000 make sense?	We dont want to overwrite u-boot during RAM-test  >> 2 test only a quarter of RAM//Was: (CFG_MEMTEST_START + 0x700000) 20100625 Mjan
/* TODO: 57600 baud 20100624 Mjan */
#define CFG_BAUDRATE_TABLE { 115200, 57600, 38400, 19200, 9600, 2400 }

#endif /* __CONFIG_H */
