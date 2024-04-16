#ifndef _ARCH_DRIVERS_UART_H
#define _ARCH_DRIVERS_UART_H

#include <drivers/gpio/gpio.h>
#include <arch/mmio.h>

#define AUX_BASE (MMIO_BASE + 0x215000)
#define AUX_ENABLES (AUX_BASE + 4)
#define AUX_MU_IO_REG (AUX_BASE + 64)
#define AUX_MU_IER_REG (AUX_BASE + 68)
#define AUX_MU_IIR_REG (AUX_BASE + 72)
#define AUX_MU_LCR_REG (AUX_BASE + 76)
#define AUX_MU_MCR_REG (AUX_BASE + 80)
#define AUX_MU_LSR_REG (AUX_BASE + 84)
#define AUX_MU_CNTL_REG (AUX_BASE + 96)
#define AUX_MU_BAUD_REG (AUX_BASE + 104)

#define AUX_UART_CLOCK (500000000)
#define UART_MAX_QUEUE (16 * 1024)

#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK / ((baud) * 8)) - 1)

#endif /* _ARCH_DRIVERS_UART_H */
