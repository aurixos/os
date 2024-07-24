/*********************************************************************************/
/* Module Name:  config.c                                                        */
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

#include <config/config.h>
#include <firmware/file.h>
//#include <lib/string.h>
//#include <print.h>
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
	FILE *config_file = NULL;
	char config_buffer[4096];
	
	for (size_t i = 0; i < ARRAY_LENGTH(config_paths); i++) {
		config_file = firmware_file_open(NULL, config_paths[i]);
		if (config_file != NULL) {
			break;
		}
	}

	if (config_file == NULL) {
		//print("No configuration file found! Please refer to the AxBoot documentation.\n");
		//print("Entering console...\n\n");
		//console();
	}

	firmware_file_read(config_file, 4096, config_buffer);

	// TODO: parse configuration file

	/*
	if (config_errors != 0 || config_get_menu_root() == NULL) {
		//print("\nConfiguration invalid!\n");
		//print("Please correct your config file.\n");
		//print("Entering console...\n\n");
		//console();
	}
	*/

	firmware_file_close(config_file);
}