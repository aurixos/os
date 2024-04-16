#ifndef _ARCH_DRIVERS_GPIO_H
#define _ARCH_DRIVERS_GPIO_H

#include <arch/mmio.h>

#include <stdint.h>

#define GPFSEL0 (MMIO_BASE + 0x200000)
#define GPSET0 (MMIO_BASE + 0x20001C)
#define GPCLR0 (MMIO_BASE + 0x200028)
#define GPPUPPDN0 (MMIO_BASE + 0x2000E4)

enum {
	GPIO_MAX_PIN = 53,
	GPIO_FUNCTION_ALT5 = 2
};

enum {
	Pull_None = 0,
};

uint32_t gpio_set(uint32_t pin, uint32_t val);
uint32_t gpio_clear(uint32_t pin, uint32_t val);
uint32_t gpio_pull(uint32_t pin, uint32_t val);
uint32_t gpio_function(uint32_t pin, uint32_t val);

void gpio_use_as_alt5(uint32_t pin);

uint32_t gpio_call(uint32_t pin, uint32_t val, uint32_t base, uint32_t field_size, uint32_t field_max);

#endif /* _ARCH_DRIVERS_GPIO_H */
