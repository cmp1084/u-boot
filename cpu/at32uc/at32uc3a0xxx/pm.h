#ifndef __CPU_AT32UC_PM_H__
#define __CPU_AT32UC_PM_H__

/* PM registers */
#define PM_MCCTRL	0x0000
#define PM_CKSEL 	0x0004
#define PM_CPUMASK	0x0008
#define PM_HSBMASK	0x000c
#define PM_PBAMASK	0x0010
#define PM_PBBMASK	0x0014
#define PM_PLL0		0x0020
#define PM_PLL1		0x0024
#define PM_OSCCTRL0	0x0028
#define PM_OSCCTRL1	0x002c
#define PM_OSCCTRL32 0x0030
#define PM_IER		0x0040
#define PM_IDR		0x0044
#define PM_IMR		0x0048
#define PM_ISR		0x004c
#define PM_ICR		0x0050
#define PM_POSCSR	0x0054
#define PM_GCCTRL	0x0060
#define PM_RCCR		0x00c0
#define PM_BGCR		0x00c4
#define PM_VREGCR	0x00c8
#define PM_BOD		0x00d0
#define PM_RCAUSE	0x0140
#define PM_GPLP0	0x0200
#define PM_GPLP1	0x0204


/* PM register access macros */
#define pm_write(reg, value) writel((value), (void *) PM_BASE + PM_##reg)
#define pm_read(reg) readl((void *) PM_BASE + PM_##reg)

#endif /* __CPU_AT32UC_PM_H__ */
