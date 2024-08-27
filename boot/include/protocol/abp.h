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

#define AXBOOT_PROTOCOL_VERSION_STR "0.2"

struct acpi_info {
    void *rsdp;
    int is_xsdp;
};

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

    // ACPI
    struct acpi_info acpi;

    // Memory
    struct memory_map *memmap;
    int memmap_entcnt;

    // Framebuffer
    struct framebuffer_info *framebuffer;
    int framebuffer_cnt;
};

void abp_load(void *kernel);

#endif /* _ABP_H */