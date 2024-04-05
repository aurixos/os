#include <aurix.h>
#include <arch/cpu.h>
#include <cpu/gdt.h>
#include "cpu_utils.h"

aurix_status cpu_init(void)
{
	gdt_init();
	return 0;
}