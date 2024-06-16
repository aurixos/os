#ifndef _DEV_AUX_H
#define _DEV_AUX_H

#include <stdint.h>

#include <machine.h>

struct AuxRegs {
	reg32 irq_status;
	reg32 enables;
	reg32 reserved[14];
	reg32 mu_io;
	reg32 mu_ier;
	reg32 mu_iir;
	reg32 mu_lcr;
	reg32 mu_mcr;
	reg32 mu_lsr;
	reg32 mu_msr;
	reg32 mu_scratch;
	reg32 mu_control;
	reg32 mu_status;
	reg32 mu_baudrate;
};

#define REGS_AUX ((struct AuxRegs *)(PERIPHERAL_BASE + 0x00215000))

#endif /* _DEV_AUX_H */