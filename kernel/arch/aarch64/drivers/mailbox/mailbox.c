#include <drivers/mailbox/mailbox.h>
#include <mm/mmio.h>
#include <aurix.h>

#include <stdint.h>

__attribute__((aligned(0x10)))
volatile uint32_t mailbox[36];

uint32_t mailbox_call(uint8_t c)
{
	// 28-bit address and 4-bit value
	uint32_t r = ((uint32_t)((long)&mailbox) &~ 0xF) | (c & 0xF);

	// wait until we can write
	while (mmio_read(MAILBOX_STATUS) & MAILBOX_FULL);

	// WRITE!!!!!
	mmio_write(MAILBOX_WRITE, r);

	for (;;) {
		// did we get a reply yet?
		while (mmio_read(MAILBOX_STATUS) & MAILBOX_EMPTY);

		// IS IT A REPLY TO OUR MESSAGE????
		if (r == mmio_read(MAILBOX_READ)) {
			// yayy we've got a response :3
			return mailbox[1] == MAILBOX_RESPONSE;
		}
	}

	return 0;
}