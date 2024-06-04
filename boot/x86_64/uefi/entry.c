/*++
Module Name:  entry.c
Project:      AurixOS

Copyright (c) 2024 Jozef Nagy

This source is subject to the MIT License.
See License.txt in the root of this repository.
All other rights reserved.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
--*/

#include <efi.h>
#include <axboot.h>

#include <com.h>
#include <print.h>

EFI_HANDLE gImageHandle;
EFI_SYSTEM_TABLE *gSystemTable;

EFI_STATUS
AxBootEntry(EFI_HANDLE ImageHandle,
			EFI_SYSTEM_TABLE *SystemTable)
{
	gImageHandle = ImageHandle;
	gSystemTable = SystemTable;

	gSystemTable->ConOut->ClearScreen(gSystemTable->ConOut);

	//
	// TODO: Initialize a port if debug mode is enabled
	// based on configuration file.
	//
	ComInitializeCom(COM1, 115200);
	EfiPrint(L"AxBoot v1.0 (c) 2024 Jozef Nagy\r\n");

	while (1);
	return EFI_SUCCESS;
}