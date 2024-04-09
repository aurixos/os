#include <arch/x86_64/drivers/pic/pic.h>
#include <arch/x86_64/cpu/cpu_utils.h>

void pic_init()
{
	outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
	outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);
	outb(PIC1_DATA, 0x20);
	outb(PIC2_DATA, 0x20 + 8);
	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);
	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);
}

void pic_disable()
{
	//outb(PIC1_DATA, 0xff);
	//outb(PIC2_DATA, 0xff);
}