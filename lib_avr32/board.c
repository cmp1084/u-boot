/*
 * Copyright (C) 2004-2006 Atmel Corporation
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
#include <command.h>
#include <malloc.h>
#include <devices.h>
#include <version.h>
#include <net.h>

#include <asm/arch/clk.h>	//TODO: remove

#include <asm/initcalls.h>
#include <asm/sections.h>

#ifndef CONFIG_IDENT_STRING
#define CONFIG_IDENT_STRING "SimpleMachines"
#endif

DECLARE_GLOBAL_DATA_PTR;

const char version_string[] =
	U_BOOT_VERSION " (" __DATE__ " - " __TIME__ ") " CONFIG_IDENT_STRING;

unsigned long monitor_flash_len = 0;

/*
 * Begin and end of memory area for malloc(), and current "brk"
 */
static unsigned long mem_malloc_start;
static unsigned long mem_malloc_end;
static unsigned long mem_malloc_brk;

/* Weak aliases for optional board functions */
static int __do_nothing(void)
{
	return 0;
}
int board_postclk_init(void) __attribute__((weak, alias("__do_nothing")));
int board_early_init_r(void) __attribute__((weak, alias("__do_nothing")));

/* The malloc area is right below the monitor image in RAM */
static void mem_malloc_init(void)
{
	unsigned long monitor_addr;

	monitor_addr = CFG_MONITOR_BASE + gd->reloc_off;
	mem_malloc_end = monitor_addr;
	mem_malloc_start = mem_malloc_end - CFG_MALLOC_LEN;
	mem_malloc_brk = mem_malloc_start;
#ifndef CFG_MINIMUM_OUPUT
	printf("malloc: Using memory from 0x%08lx to 0x%08lx\n",
	       mem_malloc_start, mem_malloc_end);
#endif
	//~ memset ((void *)mem_malloc_start, 0,	//Removed 20100716 Mjan, malloc() doesnt have to guarantee memory initialized to zero. calloc() on the other hand do. Removing this speed up the startup of u-boot.
		//~ mem_malloc_end - mem_malloc_start);
}

void *sbrk(ptrdiff_t increment)
{
	unsigned long old = mem_malloc_brk;
	unsigned long new = old + increment;

	if ((new < mem_malloc_start) || (new > mem_malloc_end))
		return NULL;

	mem_malloc_brk = new;
	return ((void *)old);
}

#ifdef CFG_DMA_ALLOC_LEN
#include <asm/arch/cacheflush.h>
#include <asm/io.h>

unsigned long dma_alloc_start = 0;
unsigned long dma_alloc_end = 0;
unsigned long dma_alloc_brk = 0;

static void dma_alloc_init(void)
{
	unsigned long monitor_addr;

	monitor_addr = CFG_MONITOR_BASE + gd->reloc_off;
	dma_alloc_end = monitor_addr - CFG_MALLOC_LEN;
	dma_alloc_start = dma_alloc_end - CFG_DMA_ALLOC_LEN;
	dma_alloc_brk = dma_alloc_start;

#ifndef CFG_MINIMUM_OUPUT
	printf("DMA: Using memory from 0x%08lx to 0x%08lx\n",
	       dma_alloc_start, dma_alloc_end);
#endif
	//~ dcache_invalidate_range(cached(dma_alloc_start), //Removed 20100712 Mjan. No cache on UC3A
				//~ dma_alloc_end - dma_alloc_start);
}

void *dma_alloc_coherent(size_t len, unsigned long *handle)
{
	unsigned long paddr = dma_alloc_brk;

	if (dma_alloc_brk + len > dma_alloc_end)
		return NULL;

	dma_alloc_brk = ((paddr + len + CFG_DCACHE_LINESZ - 1)
			 & ~(CFG_DCACHE_LINESZ - 1));

	*handle = paddr;
	return uncached(paddr);
}
#else
static inline void dma_alloc_init(void)
{

}
#endif

static int init_baudrate(void)
{
	char tmp[64];
	int i;

	i = getenv_r("baudrate", tmp, sizeof(tmp));
	if (i > 0) {
		gd->baudrate = simple_strtoul(tmp, NULL, 10);
	} else {
		gd->baudrate = CONFIG_BAUDRATE;
	}
	return 0;
}


static int display_banner (void)
{
#ifndef CFG_MINIMUM_OUPUT
	printf ("\n\n%s\n\n", version_string);
	printf ("U-Boot code: %p -> %p  data: %p -> %p\n",
		_text, _etext, _data, _end);
#endif
	return 0;
}

void hang(void)
{
	for (;;) ;
}

static int display_dram_config (void)
{
	int i;
#ifndef CFG_MINIMUM_OUPUT
	puts ("DRAM Config:\n");
	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		printf ("Bank #%d: %08lx ", i, gd->bd->bi_dram[i].start);
		print_size (gd->bd->bi_dram[i].size, "\n");
	}
#endif
	return 0;
}

static void display_flash_config (void)
{
#ifndef CFG_MINIMUM_OUPUT
	puts ("Flash: ");
	print_size(gd->bd->bi_flashsize, " ");
	printf("at address 0x%08lx\n", gd->bd->bi_flashstart);
#endif
}

void board_init_f(ulong board_type)
{
	gd_t gd_data;
	gd_t * new_gd;
	bd_t * bd;
	unsigned long * new_sp;
	unsigned long monitor_len;
	unsigned long monitor_addr;
	unsigned long addr;
	unsigned long sdram_size;

	unsigned long hsb_hz;
	unsigned long hsb_mhz_dn;
	unsigned long hsb_mhz_up;

	/* Perform initialization sequence */
	/* Initialize the global data pointer */
	memset(&gd_data, 0, sizeof(gd_data));
	gd = &gd_data;


	cpu_init();
	//~ board_postclk_init();
	env_init();
	board_early_init_f();
	init_baudrate();
	serial_init();
	console_init_f();
	display_banner();

	sdram_size = initsdram(board_type);		//Added 20100624 mjan

	//printf("Found 0x%08x bytes of SDRAM\n", sdram_size);

	hsb_hz = get_hsb_clk_rate();
	printf("get_hsb_clk_rate() = %d", hsb_hz);
	hsb_mhz_dn = hsb_hz / 1000000;
	hsb_mhz_up = (hsb_hz + 999999) / 1000000;
	printf("hsb_mhz_dn = %d", hsb_mhz_dn);
	printf("hsb_mhz_up = %d", hsb_mhz_up);

	/* If we have no SDRAM, we can't go on */
	if (sdram_size <= 0)
		panic("No SDRAM");

	/*
	 * Now that we have SDRAM mapped and working, we can
	 * relocate the code and continue running from SDRAM.
	 *
	 * Reserve memory at end of SDRAM for (top down in that order):
	 *  - u-boot image
	 *  - heap for malloc()
	 *  - board info struct
	 *  - global data struct
	 *  - stack
	 */
	addr = CFG_SDRAM_BASE + sdram_size;
	monitor_len = (unsigned long)_end - (unsigned long)_text;

	/* Reserve memory for u-boot code, data and bss.
	 * Round down to next 4 kB limit.
	 */
	addr -= monitor_len;
	addr &= ~(4096UL - 1);
	//Round down to 1 Mb limit, less digits to type during debug
	//~ addr &= ~(1024UL*1024UL - 1);
	monitor_addr = addr;

	/* Reserve memory for malloc() */
	addr -= CFG_MALLOC_LEN;

#ifdef CFG_DMA_ALLOC_LEN
	/* Reserve DMA memory (must be cache aligned) */
	addr &= ~(CFG_DCACHE_LINESZ - 1);
	addr -= CFG_DMA_ALLOC_LEN;
#endif

	/* Allocate a Board Info struct on a word boundary */
	addr -= sizeof(bd_t);
	addr &= ~3UL;
	gd->bd = bd = (bd_t *)addr;

	/* Allocate a new global data copy on a 8-byte boundary. */
	addr -= sizeof(gd_t);
	//~ addr &= ~7UL;
	addr &= ~0x1fUL;
	new_gd = (gd_t *)addr;

	/* And finally, a new, bigger stack. */
	new_sp = (unsigned long *)addr;
	gd->stack_end = addr;
	*(--new_sp) = 0;
	*(--new_sp) = 0;

	/*
	 * Initialize the board information struct with the
	 * information we have.
	 */
	bd->bi_dram[0].start = CFG_SDRAM_BASE;
	bd->bi_dram[0].size = sdram_size;
	bd->bi_baudrate = gd->baudrate;

	memcpy(new_gd, gd, sizeof(gd_t));
	printf("Relocating\n");
	relocate_code((unsigned long)new_sp, new_gd, monitor_addr);
}

void board_init_r(gd_t *new_gd, ulong dest_addr)
{
	extern void malloc_bin_reloc (void);
#ifndef CONFIG_ENV_IS_NOWHERE
	extern char * env_name_spec;
#endif
	char * s;
	cmd_tbl_t * cmdtp;
	bd_t * bd;

	gd = new_gd;
	bd = gd->bd;

	gd->flags |= GD_FLG_RELOC;
	gd->reloc_off = dest_addr - CFG_MONITOR_BASE;
	//~ gd->sram_reloc_off = dest_addr - CFG_SRAM_DATA_BASE; 20100713 Mjan

	board_early_init_r();

	monitor_flash_len = (unsigned long)_edata - (unsigned long)_text;

	/*
	 * We have to relocate the command table manually
	 */
	for (cmdtp = &__u_boot_cmd_start;
	     cmdtp !=  &__u_boot_cmd_end; cmdtp++) {
		unsigned long addr = 0;

		addr = (unsigned long)cmdtp->cmd + gd->reloc_off;
		cmdtp->cmd = (typeof(cmdtp->cmd))addr;

		addr = (unsigned long)cmdtp->name + gd->reloc_off;
		cmdtp->name = (typeof(cmdtp->name))addr;

		if (cmdtp->usage) {
			addr = (unsigned long)cmdtp->usage + gd->reloc_off;
			cmdtp->usage = (typeof(cmdtp->usage))addr;
		}
#ifdef CFG_LONGHELP
		if (cmdtp->help) {
			addr = (unsigned long)cmdtp->help + gd->reloc_off;
			cmdtp->help = (typeof(cmdtp->help))addr;
		}
#endif
	}

	/* there are some other pointer constants we must deal with */
#ifndef CONFIG_ENV_IS_NOWHERE
	env_name_spec += gd->reloc_off;
#endif

	timer_init();
	mem_malloc_init();
	malloc_bin_reloc();

	//TODO: REMOVE MJan
	//~ unsigned long * test;
	//~ unsigned long * test2;
	//~ unsigned long * test3;
	//~ printf("Testing\n");
	//~ test = malloc(700);
	//~ printf("Success. 0x%08x, 0x%x. (0x%08x)\n", (unsigned int)test, (unsigned int)*test, (unsigned int)&test);
	//~ free(test);
	//~ test2 = malloc(64000);
	//~ printf("Success. 0x%08x, 0x%x. (0x%08x)\n", (unsigned int)test2, (unsigned int)*test, (unsigned int)&test);

	//~ test3 = malloc(2*64000);
	//~ printf("Success. 0x%08x, 0x%x. (0x%08x)\n", (unsigned int)test3, (unsigned int)*test, (unsigned int)&test);
	//~ //malloc_stats();
	//~ free(test2);
	//~ free(test3);

	dma_alloc_init();

	enable_interrupts();

	bd->bi_flashstart = 0;
	bd->bi_flashsize = 0;
	bd->bi_flashoffset = 0;

#ifndef CFG_NO_FLASH
	bd->bi_flashstart = CFG_FLASH_BASE;
	bd->bi_flashsize = flash_init();
	bd->bi_flashoffset = (unsigned long)_edata - (unsigned long)_text;

	if (bd->bi_flashsize)
		display_flash_config();
#endif

	if (bd->bi_dram[0].size)
		display_dram_config();

	gd->bd->bi_boot_params = malloc(CFG_BOOTPARAMS_LEN);

#ifndef CFG_MINIMUM_OUPUT
	if (!gd->bd->bi_boot_params)
		puts("WARNING: Cant alloc mem for boot param\n");
#endif

	/* initialize environment */
	env_relocate();

	bd->bi_ip_addr = getenv_IPaddr("ipaddr");

	devices_init();
	jumptable_init();
	console_init_r();

	s = getenv("loadaddr");
	if (s)
		load_addr = simple_strtoul(s, NULL, 16);

#if defined(CONFIG_CMD_NET)
	s = getenv("bootfile");
	if (s)
		copy_filename(BootFile, s, sizeof(BootFile));
#if defined(CONFIG_NET_MULTI)
#ifndef CFG_MINIMUM_OUPUT
	puts("Net:   ");
#endif
#endif
	eth_initialize(gd->bd);
#endif

	for (;;) {
		main_loop();
	}
}
