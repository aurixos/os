/*********************************************************************************/
/* Module Name:  config.c                                                        */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024-2025 Jozef Nagy                                            */
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
#include <mm/mman.h>
#include <vfs/vfs.h>
#include <print.h>
#include <axboot.h>

#include <stdint.h>
#include <stddef.h>

char *config_paths[] = {
	"\\axboot.cfg",
	"\\System\\axboot.cfg",
	"\\EFI\\axboot.cfg",
	"\\EFI\\BOOT\\axboot.cfg",
};

void config_init(void)
{
	char *config_buf;
	uint8_t open = 0;
	
	for (size_t i = 0; i < ARRAY_LENGTH(config_paths); i++) {
		vfs_read("\\System\\axkrnl", &config_buf);
		if (config_buf != NULL) {
			open = 1;
			break;
		}
	}

	if (open == 0) {
		debug("Couldn't open a configuration file! Entering console...\n");
		//console();
		while (1);
	}

	// TODO: parse configuration file

	mem_free(config_buf);
}