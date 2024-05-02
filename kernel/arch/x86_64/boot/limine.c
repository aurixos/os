#include <boot/limine.h>
#include <boot/boot.h>

#include <stdint.h>

static volatile LIMINE_BASE_REVISION(1)

volatile struct limine_memmap_request memmap_request = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 0
};

volatile struct limine_hhdm_request hhdm_request = {
	.id = LIMINE_HHDM_REQUEST,
	.revision = 0
};

volatile struct limine_kernel_address_request kernel_addr_request = {
	.id = LIMINE_KERNEL_ADDRESS_REQUEST,
	.revision = 0,
};

volatile struct limine_rsdp_request rsdp_request = {
	.id = LIMINE_RSDP_REQUEST,
	.revision = 0
};

volatile struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};
