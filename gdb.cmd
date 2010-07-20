set output-radix 16
target remote :4711
file u-boot
thb board_init_f
c

define goram
	symbol-file
	add-symbol-file u-boot $r11
	thb board_init_r
	c
end
