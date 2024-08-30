# Aurix Boot Protocol (revision 0.2)

The Aurix Boot Protocol presents a simple and minimal protocol for booting the AurixOS kernel.

## Machine state

- All general purpose registers are zeroed out
- Interrupts are disabled

- Framebuffer is set to the best available video mode (graphics mode if available)

## Kernel parameters

The bootloader passes `abp_boot_info` structure as a parameter to the kernel.
This structure contains the bootloader name and version, version of the ABP protocol, ACPI information,
memory map and framebuffer information.

```c
struct abp_boot_info {
    // General
    char *bootloader_name;
    char *bootloader_version;
    char *protocol_version;

    // ACPI and SMBIOS
    struct acpi_info acpi;
    struct smbios_info smbios;

    // Memory
    struct memory_map *memmap;

    // Framebuffer
    struct framebuffer_info framebuffer;
};
```

## ACPI and SMBIOS

These structures contain pointers to the Root System Description Pointer (ACPI) and System Management BIOS Entry Point (SMBIOS).
If `is_valid` is set to a non-zero value, the pointer is guaranteed to be valid.
Otherwise, the pointer is set to NULL and should not be used.

```c
struct acpi_info {
    uint8_t is_valid;
    void *rsdp;
};
```

```c
struct smbios_info {
    uint8_t is_valid;
    void *entry_point;
};
```

## Memory map

The memory map is a singly linked list containing the physical address of the entry, its length and type, as well as a pointer to the next entry.

Entries are guaranteed to not overlap with each other, and sorted by base address from low to high.

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

    struct memory_map *next;
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