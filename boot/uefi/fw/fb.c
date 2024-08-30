/*********************************************************************************/
/* Module Name:  fb.c                                                            */
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
#include <firmware/fb.h>
#include <lib/string.h>
#include <print.h>
#include <efi.h>
#include <efilib.h>

#include <stdint.h>
#include <stddef.h>

EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = NULL;

uint8_t is_initialized = 0;

int fw_initialize_fb(void)
{
	EFI_STATUS status;
	EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

	// get GOP
	status = gSystemTable->BootServices->LocateProtocol(&gop_guid,
														NULL,
														(VOID **)&gop);
	if (EFI_ERROR(status)) {
		debug("ERROR: LocateProtocol() returned 0x%lx\r\n", status);
		return 1;
	}

	// UEFI should already set the framebuffer to the best available
	// mode
	// all went well :>
	is_initialized = 1;
	return 0;
}

void fw_get_framebuffer(void **address, uint32_t *width, uint32_t *height, uint16_t *bpp, uint8_t *pixelformat)
{
	EFI_STATUS status;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeinfo = NULL;
	EFI_UINTN modeinfo_size = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);

	if (!is_initialized) {
		debug("Called fw_get_framebuffer() when is_initialized = 0!\r\n");
		return;
	}

	status = gop->QueryMode(gop, gop->Mode->Mode, &modeinfo_size, &modeinfo);
	if (EFI_ERROR(status)) {
		debug("ERROR: Failed to query GOP mode %u\r\n", gop->Mode->Mode);
		return;
	}


	if (modeinfo->PixelFormat == PixelRedGreenBlueReserved8BitPerColor) {
		*pixelformat = 1; // rgba
		*bpp = 32;
	} else if (modeinfo->PixelFormat == PixelBlueGreenRedReserved8BitPerColor) {
		*pixelformat = 2; // bgra
		*bpp = 32;
	}

	*address = (void *)gop->Mode->FrameBufferBase;
	*width = modeinfo->HorizontalResolution;
	*height = modeinfo->VerticalResolution;
}