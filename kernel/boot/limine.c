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