# Aurix Boot Protocol

This document specifies the Aurix Boot Protocol.

## Machine state

- All general purpose registers are zeroed out
- Framebuffer is set to the best available video mode

## Kernel parameters

The bootloader passes `abp_boot_info` structure as a parameter to the kernel.
This structure contains the bootloader name and version, version of the ABP protocol,
memory map and framebuffer information.

```c
struct abp_boot_info {
    // General
    const char *bootloader_name;
    const char *bootloader_version;
    const char *protocol_version;

    // ACPI
    void *rsdp;
    int acpiver;

    // Memory
    struct memory_map *memmap;
    int memmap_entcnt;

    // Framebuffer
    struct framebuffer_info *framebuffer;
    int framebuffer_cnt;
};
```

## Memory map

```c
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
```

## Framebuffer

```c
struct framebuffer_info {
    void *addr;
    uint32_t width;
    uint32_t height;
    uint16_t bpp;
};
```