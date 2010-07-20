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
#include <common.h>

#include <asm/io.h>
#include <asm/arch/memory-map.h>
#include "flashc.h"

DECLARE_GLOBAL_DATA_PTR;

/* Flash sizes in KB as returned by FSZ bitfield in FSR */
const unsigned long flash_sizes[8] = {
	32,
	64,
	128,
	256,
	384,
	512,
	768,
	1024
};

flash_info_t flash_info[1];

unsigned long flash_init(void)
{
	unsigned long fsz;
	unsigned long size;
	unsigned int i;

	fsz = FLASHC_BFEXT(FSZ, flashc_readl(FSR));

	size = flash_sizes[fsz] * 1024;

	flash_info[0].size = size;

	/* Currently, all interflash have pages which are 128 words. */
	flash_info[0].sector_count = size / (128*4);

	for(i=0; i<flash_info[0].sector_count; i++){
		flash_info[0].start[i] = i*128*4 + CFG_FLASH_BASE;
	}

	return size;
}

void flash_print_info(flash_info_t *info)
{
	printf("Flash: Vendor ID: 0x%02lx, Product ID: 0x%02lx\n",
	       info->flash_id >> 16, info->flash_id & 0xffff);
	printf("Size: %ld kB in %d sectors\n",
	       info->size >> 10, info->sector_count);
}

static void flash_wait_ready(void)
{
	while(! flashc_readl(FSR) & FLASHC_BIT(FRDY) );
}

int flash_erase(flash_info_t *info, int s_first, int s_last)
{
	int page;

	for(page=s_first;page<s_last; page++){
		flash_wait_ready();
		flashc_writel(
			FCMD,FLASHC_BF(CMD, FLASHC_EP)
			|FLASHC_BF(PAGEN, page)
			|FLASHC_BF(KEY, 0xa5));
	}
	return ERR_OK;
}

static void write_flash_page(unsigned int pagen, const u32 *data)
{
	unsigned int i;
	u32 *dst;

	dst = (u32 *) CFG_FLASH_BASE;

	/* clear page buffer */
	flash_wait_ready();
	flashc_writel(FCMD,
		FLASHC_BF(CMD, FLASHC_CPB) |
		FLASHC_BF(KEY, 0xa5));

	/* fill page buffer*/
	flash_wait_ready();
	for(i=0; i<128; i++){
		dst[i]=data[i];
	}

	/* issue write command */
	flashc_writel(FCMD,
		FLASHC_BF(CMD, FLASHC_WP)|
		FLASHC_BF(PAGEN, pagen)|
		FLASHC_BF(KEY, 0xa5));
}

int write_buff(flash_info_t *info, uchar *src, ulong addr, ulong count)
{
	unsigned int i;

	if (addr % (4*128)) {
		printf("flash: write_buff(): ERROR, addr(0x%08lx) not "
			"on page boundary", addr);
		return ERR_ALIGN;
	}
	if (count % (4*128)) {
		printf("flash: write_buff(): ERROR, count(0x%lu) not "
			"a multiple of pagesize", count);
		return ERR_ALIGN;
	}

	for (i = 0; i < count; i += 128*4) {
		unsigned int pagen;
		pagen = (addr-CFG_FLASH_BASE+i) / (128*4);
		write_flash_page(pagen, (u32*) (src+i));
	}


	return ERR_OK;
}

void flash_set_waitstate(int waitstate)
{
	flashc_writel(FCR, waitstate << FLASHC_FWS_OFFSET);
}
