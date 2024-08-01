/*********************************************************************************/
/* Module Name:  loader.c                                                        */
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

#include <lib/string.h>
#include <loader/loader.h>
#include <firmware/firmware.h>
#include <firmware/file.h>
#include <print.h>

void loader_load(int type, int protocol, const char *filepath)
{
	(void)protocol;
	uint64_t filesize;
	FILE *file;
	void *filebuf;

	file = fw_file_open(NULL, filepath);
	if (file == NULL) {
		// TODO: Error handling
		log("ERROR: Couldn't open file '%s'.\r\n", filepath);
		return;
	}

	// allocate memory for file
	filesize = fw_file_size(file);
	if (filesize == 0) {
		// TODO: Error handling
		log("ERROR: Couldn't read '%s'.\r\n", filepath);
		return;
	}

	filebuf = malloc(filesize);

	if (fw_file_read(file, filesize, filebuf) != 0) {
		// TODO: Error handling
		log("ERROR: Couldn't read '%s'.\r\n", filepath);
		return;
	}

	fw_file_close(file);

	switch (type) {
		case KernelElf:
			break;
		default:
			break;
	}
}