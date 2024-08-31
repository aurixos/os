/*********************************************************************************/
/* Module Name:  memory.c                                                        */
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

#include <firmware/memory.h>
#include <firmware/firmware.h>
#include <print.h>
#include <efi.h>
#include <efilib.h>

#include <stddef.h>

void *fw_allocmem(size_t size)
{
	void *ptr = NULL;
	EFI_STATUS status;

	status = gSystemTable->BootServices->AllocatePool(EfiLoaderData, (EFI_UINTN)size, &ptr);
	if (EFI_ERROR(status)) {
		debug("ERROR: Failed to allocate memory: 0x%x\r\n", status);
		return NULL;
	}

	return ptr;
}

int fw_allocpage(size_t np, void *base)
{
	EFI_STATUS status;
	
	status = gSystemTable->BootServices->AllocatePages(AllocateAddress, 0x80000000, (EFI_UINTN)np, (EFI_PHYSICAL_ADDRESS *)base);
	if (EFI_ERROR(status)) {
		debug("ERROR: Failed to allocate %u pages at address 0x%x: 0x%x\r\n", np, base, status);
		return 1;
	}

	return 0;
}

void fw_free(void *p)
{
	if (p == NULL)
		return;

	gSystemTable->BootServices->FreePool(p);
}