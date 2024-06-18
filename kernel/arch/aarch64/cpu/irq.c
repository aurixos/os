#include <arch/aarch64/utils/utils.h>
#include <arch/aarch64/dev/aux.h>
#include <arch/aarch64/dev/timer.h>
#include <dev/uart.h>
#include <machine.h>
#include "entry.h"
#include "irq.h"

#include <stdint.h>

const char *entry_error_messages[16] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",
	"FIQ_INVALID_EL1t",
	"ERROR_INVALID_EL1t",
	"SYNC_INVALID_EL1h",
	"IRQ_INVALID_EL1h",
	"FIQ_INVALID_EL1h",
	"ERROR_INVALID_EL1h",
	"SYNC_INVALID_EL0_32",
	"IRQ_INVALID_EL0_32",
	"FIQ_INVALID_EL0_32",
	"ERROR_INVALID_EL0_32",
	"SYNC_INVALID_EL0_64",
	"IRQ_INVALID_EL0_64",
	"FIQ_INVALID_EL0_64",
	"ERROR_INVALID_EL0_64"
};

void show_invalid_entry_message(u32 type, u64 esr, u64 addr)
{
	(void)type;
	(void)esr;
	(void)addr;

	//klog("EXCEPTION CAUGHT: %s - %d, ESR: %x, Address: 0x%lx\n",
	//	entry_error_messages[type], type, esr, addr);
}

void enable_interrupt_controller()
{
#if MACHINE_VERSION == 3
	REGS_IRQ->irq0_enable_1 = AUX_IRQ | SYS_TIMER_IRQ_1 | SYS_TIMER_IRQ_3;
#elif MACHINE_VERSION == 4
	REGS_IRQ->irq0_enable_0 = AUX_IRQ | SYS_TIMER_IRQ_1 | SYS_TIMER_IRQ_3;
#endif
}

void handle_irq()
{
	u32 irq;

#if MACHINE_VERSION == 3
	irq = REGS_IRQ->irq0_pending_0;
#elif MACHINE_VERSION == 4
	irq = REGS_IRQ->irq0_pending_1;
#endif

	while (irq) {
		if (irq & AUX_IRQ) {
			irq &= ~AUX_IRQ;

			while ((REGS_AUX->mu_iir & 4) == 0) {
				//klog("UART_recv: ");
				uart_send(uart_recv());
				//klog("\n");
			}
		}
		
		if (irq & SYS_TIMER_IRQ_1) {
			irq &= ~SYS_TIMER_IRQ_1;

			handle_timer_1();
		}
		
		if (irq & SYS_TIMER_IRQ_3) {
			irq &= ~SYS_TIMER_IRQ_3;

			handle_timer_3();
		}
	}
}