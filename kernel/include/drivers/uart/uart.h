#ifndef _DRIVERS_UART_UART_H
#define _DRIVERS_UART_UART_H

#include <aurix.h>

#include ARCH_INCLUDE(drivers/uart/uart.h)

void uart_init(int baud);
void uart_write(char *str);

#endif /* _DRIVERS_UART_UART_H */
