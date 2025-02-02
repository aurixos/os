/*********************************************************************************/
/* Module Name:  init.c                                                          */
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

#include <vfs/vfs.h>
#include <mm/mman.h>
#include <mm/vmm.h>
#include <loader/elf.h>
#include <print.h>

void axboot_init()
{
	if (!vfs_init("\\")) {
		debug("axboot_init(): Failed to mount boot drive! Halting...\n");
		// TODO: Halt
		while (1);
	}

	// read kernel -> test read
	char *kbuf = NULL;
	vfs_read("\\System\\axkrnl", &kbuf);

	// TODO: Do something with the kernel :p
	uintptr_t *pm = create_pagemap();
	if (!pm) {
		debug("axboot_init(): Failed to create kernel pagemap! Halting...\n");
		// TODO: Halt
		while (1);
	}

	void *kernel_entry = (void *)elf_load(kbuf, pm);
	(void)kernel_entry;

	mem_free(kbuf);

	while (1);
}