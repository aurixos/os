/*********************************************************************************/
/* Module Name:  init.c                                                          */
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

#include <firmware/firmware.h>
#include <print.h>
#include <efi.h>
#include <efilib.h>

#include <stdint.h>
#include <stddef.h>

int firmware_init(void)
{
	EFI_STATUS Status;
	EFI_GUID LoadedImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
	EFI_GUID SimpleFsProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

	Status = gSystemTable->BootServices->OpenProtocol(gImageHandle,
				&LoadedImageProtocolGuid,
				(VOID **)&gLoadedImageProtocol,
				gImageHandle,
				NULL,
				EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
	if (EFI_ERROR(Status)) {
		debug("Couldn't open LoadedImage protocol!\r\n");
		return 1;
	}

	Status = gSystemTable->BootServices->OpenProtocol(gLoadedImageProtocol->DeviceHandle,
				&SimpleFsProtocolGuid,
				(VOID **)&gFileSystem,
				gImageHandle,
				NULL,
				EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
	if (EFI_ERROR(Status)) {
		debug("Couldn't open SimpleFileSystem protocol!\r\n");
		return 1;
	}

	return 0;
}
