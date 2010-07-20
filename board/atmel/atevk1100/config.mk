PLATFORM_RELFLAGS	+= -ffunction-sections -fdata-sections
PLATFORM_LDFLAGS	+= --gc-sections
TEXT_BASE		= 0x80000000
LDSCRIPT		= $(obj)board/atmel/atevk1100/u-boot.lds
