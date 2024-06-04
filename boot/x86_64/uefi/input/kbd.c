/*++
Module Name:  kbd.c
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

#include <axboot.h>
#include <efi.h>
#include <efilib.h>

#include <input/kbd.h>

EFI_INPUT_KEY
InputGetKey()
{
	EFI_EVENT Event[1];
	EFI_INPUT_KEY Key;
	UINTN Index = 0;

	Key.ScanCode = 0;
	Key.UnicodeChar = u'\0';

	Event[0] = g_SystemTable->ConIn->WaitForKey;
	g_SystemTable->BootServices->WaitForEvent(1, Event, &Index);

	if(Index == 0)
	{
		g_SystemTable->ConIn->ReadKeyStroke(g_SystemTable->ConIn, &Key);
	}

	return Key;
}