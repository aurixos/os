/*********************************************************************************/
/* Module Name:  memmap.c                                                        */
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

#include <firmware/memmap.h>
#include <lib/string.h>
#include <print.h>

#include <stdint.h>
#include <stddef.h>

void memmap_dump(struct memory_map_info *memmap)
{
	debug("Dumping memory map:\r\n");
	for (size_t i = 0; i < memmap->entry_count; i++) {
		debug("Entry %u: base=0x%llx length=%llu type=%s\r\n", i, memmap->entries[i].base, memmap->entries[i].length, memmap_type_to_str(memmap->entries[i].type));
	}
}

char *memmap_type_to_str(uint16_t type)
{
	switch (type) {
		case MemoryMapReserved:
			return "Reserved";
        case MemoryMapUsable:
			return "Usable";
        case MemoryMapLoader:
			return "Bootloader Reclaimable";
        case MemoryMapAcpiReclaimable:
			return "ACPI Reclaimable";
        case MemoryMapAcpiNVS:
			return "Acpi NVS";
        case MemoryMapMmio:
			return "MMIO";
		case MemoryMapUnusable:
			return "Unusable";
        default:
			return "Unknown";
	}
}