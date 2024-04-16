#include <drivers/gpio/gpio.h>
#include <mm/mmio.h>

#include <stdint.h>

uint32_t gpio_set(uint32_t pin, uint32_t val)
{
	return gpio_call(pin, val, GPSET0, 1, GPIO_MAX_PIN);
}

uint32_t gpio_clear(uint32_t pin, uint32_t val)
{
	return gpio_call(pin, val, GPCLR0, 1, GPIO_MAX_PIN);
}

uint32_t gpio_pull(uint32_t pin, uint32_t val)
{
	return gpio_call(pin, val, GPPUPPDN0, 2, GPIO_MAX_PIN);
}

uint32_t gpio_function(uint32_t pin, uint32_t val)
{
	return gpio_call(pin, val, GPFSEL0, 3, GPIO_MAX_PIN);
}

void gpio_use_as_alt5(uint32_t pin)
{
	gpio_pull(pin, Pull_None);
	gpio_function(pin, GPIO_FUNCTION_ALT5);
}

uint32_t gpio_call(uint32_t pin, uint32_t val, uint32_t base, uint32_t field_size, uint32_t field_max)
{
	uint32_t field_mask = (1 << field_size) - 1;

	if (pin > field_max)
		return 0;

	if (val > field_mask)
		return 0;

	uint32_t field_count = 32 / field_size;
	uint32_t reg = base + ((pin / field_count ) * 4);
	uint32_t shift = (pin % field_count) * field_size;

	uint32_t cval = mmio_read(reg);
	cval &= ~(field_mask << shift);
	cval |= val << shift;
	mmio_write(reg, cval);

	return 1;
}
