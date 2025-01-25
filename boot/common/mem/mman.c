/*********************************************************************************/
/* Module Name:  mman.c                                                          */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024-2025 Jozef Nagy                                            */
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

#include <mem/mman.h>
#include <print.h>
#include <stddef.h>

#ifndef AXBOOT_UEFI

#warning "Memory management is not implemented yet, expect runtime errors."

void *mem_alloc(size_t n)
{
	(void)n;

	return NULL;
}

int mem_allocat(void *addr, size_t npages)
{
	(void)addr;
	(void)npages;

	return 0;
}

void mem_free(void **addr)
{
	(void)addr;
}

#else

#include <efi.h>
#include <efilib.h>

void *mem_alloc(size_t n)
{
	EFI_STATUS status;
	void *alloc = NULL;

	status = gBootServices->AllocatePool(EfiLoaderData, (EFI_UINTN)n, &alloc);
	if (EFI_ERROR(status)) {
		debug("mem_alloc(): Couldn't allocate %u bytes: %s (%lx)\n", n, efi_status_to_str(status), status);
		return NULL;
	}

	return alloc;
}

int mem_allocat(void *addr, size_t npages)
{
	EFI_STATUS status;
	void *alloc;

	status = gBootServices->AllocatePages(AllocateAddress, EfiLoaderData, (EFI_UINTN)npages, addr);
	if (EFI_ERROR(status)) {
		debug("mem_allocat(): Couldn't allocate %u bytes at 0x%lx: %s (%lx)\n", npages, addr, efi_status_to_str(status), status);
		return 0;
	}

	return 1;
}

void mem_free(void **addr)
{
	EFI_STATUS status;

	if (addr == NULL) {
		return;
	}

	status = gBootServices->FreePool(*addr);
	if (EFI_ERROR(status)) {
		debug("mem_free(): Couldn't free 0x%lx: %s (%lx)\n", *addr, efi_status_to_str(status), status);
		return;
	}

	*addr = NULL;
}

#endif