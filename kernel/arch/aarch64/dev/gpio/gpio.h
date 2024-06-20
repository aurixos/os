#ifndef _ARCH_DEV_GPIO_H
#define _ARCH_DEV_GPIO_H

#include <stdint.h>

#include <machine.h>

struct GpioPinData {
	reg32 reserved;
	reg32 data[2];
};

struct GpioRegs {
	reg32 func_select[6];
	struct GpioPinData output_set;
	struct GpioPinData output_clear;
	struct GpioPinData level;
	struct GpioPinData ev_detect_status;
	struct GpioPinData ev_detect_enable;
	struct GpioPinData fe_detect_enable;
	struct GpioPinData hi_detect_enable;
	struct GpioPinData lo_detect_enable;
	struct GpioPinData async_re_detect;
	struct GpioPinData async_fe_detect;
	reg32 reserved;
	reg32 pupd_enable;
	reg32 pupd_enable_clocks[2];
};

#define REGS_GPIO ((struct GpioRegs *)(PERIPHERAL_BASE + 0x00200000))

typedef enum {
	GFInput = 0,
	GFOutput = 1,
	GFAlt0 = 4,
	GFAlt1 = 5,
	GFAlt2 = 6,
	GFAlt3 = 7,
	GFAlt4 = 3,
	GFAlt5 = 2
} GpioFunc;

void gpio_pin_set_func(u8 pin_number, GpioFunc func);
void gpio_pin_enable(u8 pin_number);

#endif /* _ARCH_DEV_GPIO_H */