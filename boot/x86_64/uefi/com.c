/*++
Module Name:  com.c
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

#include <io.h>
#include <com.h>

AXBOOT_STATUS
ComInitializeCom(
	UINT16 ComPort,
	UINT32 BaudRate)
{
	// Calculate the divisor to tell UART
	UINT8 BaudDivisor = BaudRate / 115200;

	//
	// Disable interrupts
	//
	IoOutByte(ComPort + 1, 0x00);
	
	//
	// Set Baud Rate divisor
	//
	IoOutByte(ComPort + 3, 0x80);
	IoOutByte(ComPort + 0, BaudDivisor & 0xFF);
	IoOutByte(ComPort + 1, (BaudDivisor << 2) & 0xFF);

	//
	// Configure, enable loopback mode and
	// send a test byte 0xAB
	//
	IoOutByte(ComPort + 3, 0x03);
	IoOutByte(ComPort + 2, 0xC7);
	IoOutByte(ComPort + 4, 0x0B);
	IoOutByte(ComPort + 4, 0x1E);
	IoOutByte(ComPort + 0, 0xAB);
 
	//
	// Check if UART is faulty
	//
	if(IoInByte(ComPort + 0) != 0xAB) {
		return 1;
	}

	//
	// Set UART to normal operation
	//
	IoOutByte(ComPort + 4, 0x0F);
	return 0;
}