/*********************************************************************************/
/* Module Name:  file.c                                                          */
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
#include <firmware/file.h>
#include <lib/string.h>
#include <print.h>
#include <efi.h>
#include <efilib.h>

#include <stdint.h>
#include <stddef.h>

FILE *fw_file_open(FILE *directory, const char *path)
{
	EFI_STATUS Status;
	CHAR16 wpath[4096];
	FILE *file = NULL;

	debug("Opening file '%s'...\r\n", path);

	if (directory == NULL) {
		Status = gFileSystem->OpenVolume(gFileSystem, &directory);
		if (EFI_ERROR(Status)) {
			debug("Error when opening volume: %x\r\n", Status);
			return NULL;
		}
	}

	mbstowcs(wpath, &path, strlen(path));
	wpath[strlen(path)] = '\0';

	Status = directory->Open(directory, &file, wpath, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_SYSTEM);
	if (EFI_ERROR(Status)) {
		debug("Error when opening file '%s': %x\r\n", path, Status);
		return NULL;
	}

	return file;
}

int fw_file_close(FILE *file)
{
	if (file == NULL) {
		return -1;
	}

	return file->Close(file);
}

int fw_file_read(FILE *file, uint64_t size, void *buffer)
{
	if (file == NULL || size < 0 || buffer == NULL) {
		return -1;
	}

	return file->Read(file, &size, buffer);
}

int fw_file_write(FILE *file, uint64_t size, void *buffer)
{
	if (file == NULL || size < 0 || buffer == NULL) {
		return -1;
	}

	return file->Write(file, &size, buffer);
}

int fw_file_size(FILE *file)
{
	EFI_STATUS status;
	EFI_FILE_INFO file_info;
	EFI_GUID fi_guid = EFI_FILE_INFO_GUID;
	EFI_UINTN buffer_size = sizeof(EFI_FILE_INFO);

	status = file->GetInfo(file, &fi_guid, &buffer_size, &file_info);
	if (EFI_ERROR(status)) {
		return 0;
	}

	return file_info.FileSize;
}