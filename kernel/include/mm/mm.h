#ifndef _MM_MM_H
#define _MM_MM_H

#include <boot/boot.h>
#include <arch/mm.h>

#define KB_TO_PAGES(kb) (((kb) * 1024) / PAGE_SIZE)
#define ALIGN_DOWN(addr, align) ((addr) & ~((align)-1))
#define ALIGN_UP(addr, align) (((addr) + (align)-1) & ~((align)-1))

#define BIT_TO_PAGE(bit) ((size_t)bit * PAGE_SIZE)
#define PAGE_TO_BIT(page) ((size_t)page / PAGE_SIZE)

#define PHYS_TO_VIRT(addr) ((addr) + hhdm_request.response->offset)
#define VIRT_TO_PHYS(addr) ((addr) - hhdm_request.response->offset)

#endif /* _MM_MM_H */