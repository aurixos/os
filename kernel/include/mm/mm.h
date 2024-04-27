#ifndef _MM_MM_H
#define _MM_MM_H

#include <boot/boot.h>
#include <arch/mm.h>

#define ALIGN_DOWN(addr, align) ((addr) & ~((align)-1))
#define ALIGN_UP(addr, align) (((addr) + (align)-1) & ~((align)-1))

#define PHYS_TO_VIRT(addr) ((addr) + hhdm_request.response->offset)
#define VIRT_TO_PHYS(addr) ((addr) - hhdm_request.response->offset)

#endif /* _MM_MM_H */
