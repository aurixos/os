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

#include <arch/mm/paging.h>
#include <firmware/firmware.h>
#include <firmware/memmap.h>
#include <firmware/handoff.h>
#include <lib/string.h>
#include <print.h>
#include <efi.h>
#include <efilib.h>

#include <stdint.h>
#include <stddef.h>

void fw_get_memory_map(struct memory_map_info *memmap)
{
	EFI_STATUS status;
	EFI_MEMORY_DESCRIPTOR *map = NULL;
	EFI_UINTN size = 0;
	EFI_UINTN key = 0;
	EFI_UINTN desc_size = 0;
	EFI_UINT32 desc_ver = 0;

	if (memmap == NULL) {
		return;
	}

	status = gSystemTable->BootServices->GetMemoryMap(&size, map, &key, &desc_size, &desc_ver);
	if (EFI_ERROR(status) && status != EFI_BUFFER_TOO_SMALL) {
		debug("ERROR: Failed to acquire memory map (step 1): 0x%lx\r\n", status);
		return;
	}

	size += desc_size * 2;
	map = (EFI_MEMORY_DESCRIPTOR *)malloc(size);

	status = gSystemTable->BootServices->GetMemoryMap(&size, map, &key, &desc_size, &desc_ver);
	if (EFI_ERROR(status)) {
		debug("ERROR: Failed to acquire memory map (step 2): 0x%lx\r\n", status);
		free(map);
		return;
	}

	// allocate memory for AxBoot-format memory map
	memmap->entry_count = size / desc_size - 1;
	memmap->entries = (struct memory_map_entry *)malloc(memmap->entry_count * sizeof(struct memory_map_entry));

	// translate UEFI memory map to AxBoot one
	debug("Processing memory map\r\n");
	for (EFI_UINTN i = 0; i < size / desc_size - 1; i++) {
		EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((uint8_t *)map + (i * desc_size));
		
		if (desc->NumberOfPages == 0) {
			continue;
		}

		memmap->entries[i].base = (uint64_t)desc->PhysicalStart;
		memmap->entries[i].length = (uint64_t)(desc->NumberOfPages * PAGE_SIZE);

		switch (desc->Type) {
			case EfiReservedMemoryType:
			case EfiPalCode:
				memmap->entries[i].type = MemoryMapReserved;
				break;
			case EfiLoaderCode:
			case EfiLoaderData:
			case EfiBootServicesCode:
			case EfiBootServicesData:
			case EfiConventionalMemory:
			case EfiPersistentMemory:
				memmap->entries[i].type = MemoryMapUsable;
				break;
			case EfiUnusableMemory:
				memmap->entries[i].type = MemoryMapUnusable;
				break;
			case EfiACPIReclaimMemory:
				memmap->entries[i].type = MemoryMapAcpiReclaimable;
				break;
			case EfiRuntimeServicesCode:
			case EfiRuntimeServicesData:
			case EfiACPIMemoryNVS:
				memmap->entries[i].type = MemoryMapAcpiNVS;
				break;
			case EfiMemoryMappedIO:
			case EfiMemoryMappedIOPortSpace:
				memmap->entries[i].type = MemoryMapMmio;
				break;
			default:
				debug("Unknown memory type %x; marking as unusable\r\n", desc->Type);
				memmap->entries[i].type = MemoryMapUnusable;
				break;
		}
	}

    // check for overlapping entries and merge them
	for (int i = 0; i < memmap->entry_count; i++) {
		struct memory_map_entry *entry = &memmap->entries[i];
	
		// are we on the last entry?
		if (i == memmap->entry_count - 1) {
			break;
		}
	
		if (entry->length == 0) {
			for (int j = i; j < memmap->entry_count; j++) {
				memmap->entries[j] = memmap->entries[j + 1];
			}
		}
	
		struct memory_map_entry *next_entry = &memmap->entries[i+1];

		uint64_t entry_end = (uint64_t)entry->base + entry->length;
		if (entry_end >= next_entry->base) {
			if (entry->type == next_entry->type) {
				// two consecutive entries are the same, so just merge them
				entry->length += next_entry->length;
	
				for (int j = i + 1; j < memmap->entry_count; j++) {
					memmap->entries[j] = memmap->entries[j + 1];
				}
	
				memmap->entry_count--;
				i--;
				continue;
			}
		}
	}
}

void uefi_exit_boot_services(void)
{
	EFI_STATUS status;
	EFI_MEMORY_DESCRIPTOR *map = NULL;
	EFI_UINTN size = 0;
	EFI_UINTN key = 0;
	EFI_UINTN desc_size = 0;
	EFI_UINT32 desc_ver = 0;
	EFI_UINT32 retries = 0;

	status = gSystemTable->BootServices->GetMemoryMap(&size, map, &key, &desc_size, &desc_ver);
	if (EFI_ERROR(status) && status != EFI_BUFFER_TOO_SMALL) {
		debug("ERROR: Failed to acquire memory map (step 1): 0x%lx\r\n", status);
		return;
	}

	size += desc_size * 2;
	map = (EFI_MEMORY_DESCRIPTOR *)malloc(size);

#define MAX_RETRIES 10

	do {
		debug("Exitting Boot Services: Attempt %u/%u\r\n", retries + 1, MAX_RETRIES);

		status = gSystemTable->BootServices->GetMemoryMap(&size, map, &key, &desc_size, &desc_ver);
		if (EFI_ERROR(status)) {
			debug("Failed to acquire memory map: 0x%lx\r\n", status);
		}

		status = gSystemTable->BootServices->ExitBootServices(gImageHandle, key);
		if (EFI_ERROR(status)) {
			debug("Failed to exit boot services: ExitBootServices() returned 0x%lx\r\n", status);
		}

	} while (retries++ < MAX_RETRIES && EFI_ERROR(status));

	if (retries == MAX_RETRIES) {
		debug("ERROR: Failed to exit boot services!\r\n");
		// TODO: die?
		while (1);
	}
}
