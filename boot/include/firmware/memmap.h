/*********************************************************************************/
/* Module Name:  memmap.h                                                        */
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

#ifndef _FIRMWARE_MEMMAP_H
#define _FIRMWARE_MEMMAP_H

#include <stdint.h>

enum {
	MemoryMapReserved,
	MemoryMapUsable,
	MemoryMapLoader,
	MemoryMapAcpiReclaimable,
	MemoryMapAcpiNVS,
	MemoryMapMmio,
	MemoryMapUnusable,
};

struct memory_map_entry {
	uint64_t base;
	uint64_t length;
	uint16_t type;
};

struct memory_map_info {
	struct memory_map_entry *entries;
	uint64_t entry_count;
};

void fw_get_memory_map(struct memory_map_info *memmap);
void memmap_dump(struct memory_map_info *memmap);
char *memmap_type_to_str(uint16_t type);

#endif /* _FIRMWARE_MEMMAP_H */