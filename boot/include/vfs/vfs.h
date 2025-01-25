/*********************************************************************************/
/* Module Name:  vfs.h                                                           */
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

#ifndef _VFS_VFS_H
#define _VFS_VFS_H

#include <stdint.h>
#include <stddef.h>

struct vfs_drive;

struct vfs_filesystem {
	int (*read_file)(struct vfs_drive *drive, char *filename, char *buf, size_t len);
	int (*write_file)(struct vfs_drive *drive, char *filename, char *buf, size_t len);
};

struct vfs_mount {
	char *mountpoint;
	struct vfs_drive *drive;
};

void vfs_init(void);

int vfs_read(char *filename, char *buf, size_t len);
int vfs_write(char *filename, char *buf, size_t len);

#endif /* _VFS_VFS_H */
