#ifndef __ASM_AVR32_ARCH_GPIO_IMPL_H__
#define __ASM_AVR32_ARCH_GPIO_IMPL_H__

/* Register offsets */
struct gpio_regs {
	u32	GPER;
	u32	GPERS;
	u32	GPERC;
	u32	GPERT;
	u32	PMR0;
	u32	PMR0S;
	u32	PMR0C;
	u32	PMR0T;
	u32	PMR1;
	u32	PMR1S;
	u32	PMR1C;
	u32	PMR1T;
	u32	__reserved0[4];
	u32	ODER;
	u32	ODERS;
	u32	ODERC;
	u32	ODERT;
	u32	OVR;
	u32	OVRS;
	u32	OVRC;
	u32	OVRT;
	u32	PVR;
	u32	__reserved_PVRS;
	u32	__reserved_PVRC;
	u32	__reserved_PVRT;
	u32	PUER;
	u32	PUERS;
	u32	PUERC;
	u32	PUERT;
	u32	ODMER;
	u32	ODMERS;
	u32	ODMERC;
	u32	ODMERT;
	u32	IER;
	u32	IERS;
	u32	IERC;
	u32	IERT;
	u32	IMR0;
	u32	IMR0S;
	u32	IMR0C;
	u32	IMR0T;
	u32	IMR1;
	u32	IMR1S;
	u32	IMR1C;
	u32	IMR1T;
	u32	GFER;
	u32	GFERS;
	u32	GFERC;
	u32	GFERT;
	u32	IFR;
	u32	__reserved_IFRS;
	u32	IFRC;
	u32	__reserved_IFRT;
	u32	__reserved1[8];
};

#endif /* __ASM_AVR32_ARCH_GPIO_IMPL_H__ */
