void _start(void)
{
	__asm__ volatile("int $0x01");
	for (;;) {
		__asm__ volatile("cli;hlt");
	}
}