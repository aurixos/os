#include "gpio.h"
#include <arch/aarch64/utils/utils.h>

#include <stdint.h>

void gpio_pin_set_func(u8 pin_number, GpioFunc func)
{
	u8 bit_start = (pin_number * 3) % 30;
	u8 reg = pin_number / 10;

	u32 selector = REGS_GPIO->func_select[reg];
	selector &= ~(7 << bit_start);
	selector |= (func << bit_start);

	REGS_GPIO->func_select[reg] = selector;
}

void gpio_pin_enable(u8 pin_number)
{
	REGS_GPIO->pupd_enable = 0;
	tdelay(150);
	REGS_GPIO->pupd_enable_clocks[pin_number / 32] = 1 << (pin_number % 32);
	tdelay(150);
	REGS_GPIO->pupd_enable = 0;
	REGS_GPIO->pupd_enable_clocks[pin_number / 32] = 0;
}