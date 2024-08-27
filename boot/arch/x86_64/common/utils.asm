/*********************************************************************************/
/* Module Name:  utils.asm                                                       */
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

.code64
.section .data

.globl read_cr0
read_cr0:
    mov %cr0, %rax
    ret

.globl write_cr0
write_cr0:
    mov %rdi, %cr0
    ret

.globl read_cr2
read_cr2:
    mov %cr2, %rax
    ret

.globl write_cr2
write_cr2:
    mov %rdi, %cr2
    ret

.globl read_cr3
read_cr3:
    mov %cr3, %rax
    ret

.globl write_cr3
write_cr3:
    mov %rdi, %cr3
    ret

.globl read_cr4
read_cr4:
    mov %cr4, %rax
    ret

.globl write_cr4
write_cr4:
    mov %rdi, %cr4
    ret
