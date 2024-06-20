#include <arch/aarch64/dev/i2c/i2c.h>
#include <arch/aarch64/dev/spi/spi.h>
#include <arch/aarch64/mbox/mailbox.h>
#include <machine.h>

void machine_init()
{
	i2c_init();
	spi_init();

	//klog("\nCore clock rate: %d\n", mailbox_clock_rate(CT_CORE));
	//klog("EMMC clock rate: %d\n", mailbox_clock_rate(CT_EMMC));
	//klog("UART clock rate: %d\n", mailbox_clock_rate(CT_UART));
	//klog("ARM clock rate: %d\n", mailbox_clock_rate(CT_ARM));

	//klog("\n");
	//for (int i = 0; i <= 2; i++) {
		//bool on = mailbox_power_check(i);
		//klog("power domain status for I2C%d: %d\n", i, on);
	//}

	u32 cur_temp = 0;
	mailbox_generic_cmd(RPI_FIRMWARE_GET_TEMPERATURE, 0, &cur_temp);
	//klog("Current temperature: %d °C", cur_temp / 1000);
}