/*
 * Copyright 2010 Marcus Jansson <cmp1084@gmail.com>
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

int mmc_write(unsigned char * src, unsigned long dst, int size)
{
#ifdef MMC_DEBUG
	printf("mmc_write: src=%p, dst=%lu, size=%u\n", src, dst, size);
#endif
	/* Since mmc2info always returns 0 this function will never be called */
	return 0;
}

int mmc_read(unsigned long src, unsigned char * dst, int size)
{
#ifdef MMC_DEBUG
	printf("mmc_read: src=%lu, dst=%p, size=%u\n", src, dst, size);
#endif
	/* Since mmc2info always returns 0 this function will never be called */
	return 0;
}

int mmc2info(unsigned long addr)
{
	/* This function is used by cmd_cp to determine if source or destination
	 address resides on MMC-card or not. We do not support copy to and from
	 MMC-card so we always return 0. */
	return 0;
}
