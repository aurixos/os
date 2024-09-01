/*********************************************************************************/
/* Module Name:  abp.h                                                           */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024 Jozef Nagy                                                 */
/*                                                                               */
/* This source is subject to the MIT License.                                    */
/* See License.txt in the root of this repository.                               */
/* All other rights reserved.                                                    */
/*                                                                               */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE */
/* SOFTWARE.                                                                     */
/*********************************************************************************/

#ifndef _ABP_H
#define _ABP_H

#include <stdint.h>
#include <stddef.h>

#define AXBOOT_PROTOCOL_VERSION_STR "0.2"

///
// ACPI and SMBIOS
///

struct abp_acpi_info {
    uint8_t is_valid;
    void *rsdp;
};

struct abp_smbios_info {
    uint8_t is_valid;
    void *entry_point;
};

///
// Memory Map
///

#define ABP_MEMORY_RESERVED 0xf0
#define ABP_MEMORY_USABLE 0xf1
#define ABP_MEMORY_BOOTLOADER_RECLAIMABLE 0xf2
#define ABP_MEMORY_MMIO 0xf3
#define ABP_MEMORY_ACPI_NVS 0xf4
#define ABP_MEMORY_ACPI_RECLAIMABLE 0xf5
#define ABP_MEMORY_KERNEL 0xf7
#define ABP_MEMORY_NOT_USABLE 0xff

struct abp_memory_map {
    uint64_t base;
    uint64_t length;
    uint64_t type;

    struct abp_memory_map *next;
};

///
// Framebuffer
///

enum {
    AbpFramebufferRgba,
    AbpFramebufferBgra
};

struct abp_framebuffer_info {
    void *addr;
    uint32_t width;
    uint32_t height;
    uint16_t bpp;
    uint8_t pixel_format;
};

///
// General
///

struct abp_boot_info {
    // General
    char *bootloader_name;
    char *bootloader_version;
    char *protocol_version;

    // ACPI
    struct abp_acpi_info acpi;
    struct abp_smbios_info smbios;

    // Memory
    struct abp_memory_map *memmap;
    uint8_t lvl5_paging;

    // Framebuffer
    struct abp_framebuffer_info framebuffer;
};

///
// AxBoot
///

typedef void (*abp_entryp)(struct abp_boot_info *);

void abp_load(void *kernel, size_t kernel_size);
void abp_handoff(void *entrypoint, struct abp_boot_info *bootinfo, void *stack, uint16_t stack_size);

#endif /* _ABP_H */