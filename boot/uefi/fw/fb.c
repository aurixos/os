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

uint8_t is_initialized = 0;

void *fb_address = NULL;
uint32_t fb_width = 0;
uint32_t fb_height = 0;
uint32_t fb_bpp = 0;

int fw_initialize_fb(void)
{
	// TODO: Remove this; this just signalizes no framebuffer has been found for now.
	return 1;

	// get GOP

	// set best available graphics mode

	// all went well :>
	is_initialized = 1;
	return 0;
}

void fw_get_framebuffer(void **address, uint32_t *width, uint32_t *height, uint32_t *bpp)
{
	*address = fb_address;
	*width = fb_width;
	*height = fb_height;
	*bpp = fb_bpp;
}