#ifndef _ARCH_DRIVERS_PIC_PIC_H
#define _ARCH_DRIVERS_PIC_PIC_H

#include <stdint.h>

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xa0
#define PIC2_DATA 0xa1

#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10

#define ICW4_8086 0x01

#define PIC_EOI 0x20

void pic_init(void);
void pic_send_eoi(uint8_t irq);
void pic_disable(void);

#endif /* _ARCH_DRIVERS_PIC_PIC_H */
