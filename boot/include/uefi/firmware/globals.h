/*********************************************************************************/
/* Module Name:  globals.h                                                       */
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

#ifndef _UEFI_FIRMWARE_GLOBALS_H
#define _UEFI_FIRMWARE_GLOBALS_H

#include <efi.h>

extern EFI_LOADED_IMAGE_PROTOCOL *gLoadedImageProtocol;
extern EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *gFileSystem;
extern EFI_SYSTEM_TABLE *gSystemTable;
extern EFI_HANDLE gImageHandle;

#endif /* _UEFI_FIRMWARE_GLOBALS_H */