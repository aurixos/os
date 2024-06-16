#ifndef _UART_H
#define _UART_H

void uart_init();

char uart_recv();
void uart_send(char c);
void uart_sendstr(char *s);

#endif /* _UART_H */