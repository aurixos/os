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
#include <efi.h>
#include <efilib.h>

#include <stddef.h>

void *fw_allocmem(size_t size)
{
	void *ptr = NULL;
	EFI_STATUS status;

	status = gSystemTable->BootServices->AllocatePool(EfiLoaderData, (EFI_UINTN)size, &ptr);
	if (EFI_ERROR(status)) {
		return NULL;
	}

	return ptr;
}

void fw_free(void *p)
{
	if (p == NULL)
		return;

	gSystemTable->BootServices->FreePool(p);
}