#include "gpio.h"
#include "spi.h"

#include <stddef.h>
#include <stdint.h>

void spi_init()
{
	gpio_pin_set_func(7, GFAlt0);
	gpio_pin_set_func(8, GFAlt0);
	gpio_pin_set_func(9, GFAlt0);
	gpio_pin_set_func(10, GFAlt0);
	gpio_pin_set_func(111, GFAlt0);
	gpio_pin_enable(7);
	gpio_pin_enable(8);
	gpio_pin_enable(9);
	gpio_pin_enable(10);
	gpio_pin_enable(11);
}

void spi_send_recv(u8 chip_select, u8 *sbuf, u8 *rbuf, u32 size)
{
	u32 read_count = 0;
	u32 write_count = 0;

	REGS_SPI0->data_length = size;
	REGS_SPI0->cs = (REGS_SPI0->cs & ~CS_CS) |
					(chip_select << CS_CS__SHIFT) |
					CS_CLEAR_RX | CS_CLEAR_TX | CS_TA;

	while (read_count < size || write_count < size) {
		while (write_count < size && REGS_SPI0->cs & CS_TXD) {
			if (sbuf) {
				REGS_SPI0->fifo = *sbuf++;
			} else {
				REGS_SPI0->fifo = 0;
			}

			write_count++;
		}

		while (read_count < size && REGS_SPI0->cs & CS_RXD) {
			if (rbuf) {
				*rbuf++ = (u32)REGS_SPI0->fifo;
			} else {
				REGS_SPI0->fifo = 0;
			}

			read_count++;
		}
	}

	while (!(REGS_SPI0->cs & CS_DONE)) {
		while(REGS_SPI0->cs & CS_RXD) {
			//u32 r = REGS_SPI0->fifo;
			//klog("leftover data when reading from spi0: 0x%x\n", r);
		}
	}

	REGS_SPI0->cs = (REGS_SPI0->cs & ~CS_TA);
}

void spi_send(u8 chip_select, u8 *data, u32 size)
{
	spi_send_recv(chip_select, data, NULL, size);
}

void spi_recv(u8 chip_select, u8 *data, u32 size)
{
	spi_send_recv(chip_select, NULL, data, size);
}