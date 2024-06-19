#include <arch/aarch64/dev/i2c.h>
#include <machine.h>

void machine_init()
{
	i2c_init();
}