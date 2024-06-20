#include <arch/aarch64/dev/i2c/i2c.h>
#include <arch/aarch64/dev/spi/spi.h>
#include <machine.h>

void machine_init()
{
	i2c_init();
	spi_init();
}