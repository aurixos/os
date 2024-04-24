#ifndef _BOOT_BOOT_H
#define _BOOT_BOOT_H

#include <boot/limine.h>

extern volatile struct limine_memmap_request memmap_request;
extern volatile struct limine_hhdm_request hhdm_request;
extern volatile struct limine_kernel_address_request kernel_addr_request;

#endif /* _BOOT_BOOT_H */