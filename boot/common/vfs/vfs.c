/*********************************************************************************/
/* Module Name:  vfs.c                                                           */
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

/* VFS originally written by Levente Kurusa, stripped down for AxBoot */
/* https://github.com/levex/osdev */

#include <mm/mman.h>
#include <vfs/drive.h>
#include <vfs/vfs.h>
#include <lib/string.h>
#include <print.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_MOUNTS 32

struct vfs_mount **mountpoints = NULL;
uint8_t last_mount = 0;

size_t str_backspace(char *str, char c)
{
	size_t i = strlen(str) - 1;

	while (--i) {
		if (str[i] == c) {
			str[i+1] = 0;
			return 1;
		}
	}
	return 0;
}

/* Returns UINT8_MAX incase an error happens */
uint8_t find_mntpoint_from_filename(char *filename, uint32_t *s_off)
{
	char *orig = (char *)mem_alloc(strlen(filename) + 1);
	if (!orig) {
		debug("find_mntpoint_from_filename(): Failed to allocate memory for filename!\n");
		return UINT8_MAX;
	}

	memset(orig, 0, strlen(filename) + 1);
	memcpy(orig, filename, strlen(filename) + 1);

	if (orig[strlen(orig)] == '/')
		str_backspace(orig, '/');

	// TODO: Check if there's a way to stay in this loop forever
	while (1) {
		for (int i = 0; i < MAX_MOUNTS; i++) {
			if (!mountpoints[i])
				break;

			if (strcmp(mountpoints[i]->mnt, orig) == 0) {
				/* Adjust the orig to make it relative to the partition */
				*s_off = (strlen(orig) - 1);
				mem_free(orig);
				return i;
			}
		}

		if (strcmp(orig, "/") == 0)
			break;
		str_backspace(orig, '/');
	}
	return 0;
}

void vfs_init(void)
{
	mountpoints = (struct vfs_mount **)mem_alloc(sizeof(struct vfs_mount) * MAX_MOUNTS);
	if (!mountpoints) {
		debug("vfs_init(): Failed to allocate memory for VFS!\n");
		// TODO: Panic and halt
	}
}

int vfs_read(char *filename, char *buf, size_t len)
{
	uint32_t s_off = 0;
	int i = find_mntpoint_from_filename(filename, &s_off);
	filename += s_off;

	return mountpoints[i]->drive->fs->read(filename, buf, mountpoints[i]->drive, mountpoints[i]->drive->fs->fs_data);
}

int vfs_write(char *filename, char *buf, size_t len)
{
	(void)filename;
	(void)buf;
	(void)len;

	return 0;
}