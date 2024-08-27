#ifndef __ABP_H
#define __ABP_H

#include <stdint.h>

#define ABP_MEMORY_RESERVED 0xf0
#define ABP_MEMORY_USABLE 0xf1
#define ABP_MEMORY_BOOTLOADER_RECLAIMABLE 0xf2
#define ABP_MEMORY_MMIO 0xf3
#define ABP_MEMORY_ACPI_NVS 0xf4
#define ABP_MEMORY_ACPI_RECLAIMABLE 0xf5
#define ABP_MEMORY_KERNEL 0xf7
#define ABP_MEMORY_NOT_USABLE 0xff

struct memory_map {
    uint64_t base;
    uint64_t length;
    uint64_t type;
};

struct framebuffer_info {
    void *addr;
    uint32_t width;
    uint32_t height;
    uint16_t bpp;
};

struct abp_boot_info {
    // General
    const char *bootloader_name;
    const char *bootloader_version;
    const char *protocol_version;

    // Memory
    struct memory_map *memmap;
    int memmap_entcnt;

    // Framebuffer
    struct framebuffer_info *framebuffer;
    int framebuffer_cnt;
};

#endif /* __ABP_H */