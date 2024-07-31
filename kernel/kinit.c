void _start(void)
{
	for (;;) {
		__asm__ volatile("cli;hlt");
	}
}