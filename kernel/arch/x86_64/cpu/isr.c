#include <arch/x86_64/cpu/isr.h>
#include <arch/x86_64/cpu/cpu_utils.h>
#include <arch/x86_64/drivers/pic/pic.h>
#include <aurix.h>

#include <stddef.h>

static const char *exception_strings[32] = {
	"division by zero",
	"debug",
	"nonmaskable interrupt",
	"breakpoint",
	"overflow",
	"bound range exceeded",
	"invalid opcode",
	"device not available",
	"double fault",
	"coprocessor segment overrun",
	"invalid tss",
	"segment not present",
	"stack segment fault",
	"general protection fault",
	"page fault",
	"reserved",
	"x87 fpu error"
	"alignment check",
	"machine check",
	"simd exception",
	"virtualization exception",
	"control protection exception",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"hypervisor injection exception",
	"vmm communication exception",
	"security exception",
	"reserved"
};

interrupt_handler irq_handlers[16] = {0};

void cpu_exception_handler(struct interrupt_frame frame)
{
	if (frame.vector < 0x20) {
		// @todo: force stop scheduler and make other CPUs spin
		//        when scheduler is implemented
		// @todo: get cpu id when smp is implemented
		int cpu_id = 1;

		_klog("\npanic(cpu %d, 0x%.16llx): type %i (%s), register dump:\n", cpu_id, frame.rip, frame.vector, exception_strings[frame.vector]);
		
		_klog("cr0: 0x%.16llx, cr2: 0x%.16llx, cr3: 0x%.16llx, cr4: 0x%.16llx\n",
		  read_cr0(), read_cr2(), read_cr3(), read_cr4());
		_klog("rax: 0x%.16llx, rbx: 0x%.16llx, rcx: 0x%.16llx, rdx: 0x%.16llx\n",
			  frame.rax, frame.rbx, frame.rcx, frame.rdx);
		_klog("rsp: 0x%.16llx, rbp: 0x%.16llx, rsi: 0x%.16llx, rdi: 0x%.16llx\n",
			  frame.rsp, frame.rbp, frame.rsi, frame.rdi);
		_klog("r8:  0x%.16llx, r9:  0x%.16llx, r10: 0x%.16llx, r11: 0x%.16llx\n",
			  frame.r8, frame.r9, frame.r10, frame.r11);
		_klog("r12: 0x%.16llx, r13: 0x%.16llx, r14: 0x%.16llx, r15: 0x%.16llx\n",
			  frame.r12, frame.r13, frame.r14, frame.r15);
		_klog("rfl: 0x%.16llx, rip: 0x%.16llx, cs:  0x%.16llx, ss:  0x%.16llx\n",
			  frame.rflags, frame.rip, frame.cs, frame.ss);

		_klog("\nAurixOS version:\n");
		aurix_print_version();

		for (;;) {
			__asm__ volatile("cli;hlt");
		}
	} else if (frame.vector >= 0x20 && frame.vector <= 0x2f) {
		uint8_t irq = frame.vector - 0x20;
		if (irq_handlers[irq] != NULL) {
			irq_handlers[irq]();
		}

		pic_send_eoi(irq);
	} else {
		klog("caught unknown interrupt %d; ignoring", frame.vector);
	}
}