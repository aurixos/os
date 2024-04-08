#ifndef _DRIVERS_UART_UART_H
#define _DRIVERS_UART_UART_H

#define COM1 0x3f8

void uart_init();
void uart_write(char *str);

#endif /* _DRIVERS_UART_UART_H */
