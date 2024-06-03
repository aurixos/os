;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Module Name:  stage1-cd.asm                                                       ;;
;; Project:      AurixOS                                                         ;;
;;                                                                               ;;
;; Copyright (c) 2024 Jozef Nagy                                                 ;;
;;                                                                               ;;
;; This source is subject to the MIT License.                                    ;;
;; See License.txt in the root of this repository.                               ;;
;; All other rights reserved.                                                    ;;
;;                                                                               ;;
;; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    ;;
;; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      ;;
;; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   ;;
;; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        ;;
;; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, ;;
;; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE ;;
;; SOFTWARE.                                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[bits 16]
[org 0x7c00]

jmp 0x0000:AxBootEntry

;;
;; BIOS bootloader on x86_64 is just a placeholder
;; incase it ever becomes a thing... for now it just
;; notifies the user that you can't boot AurixOS
;; without UEFI on x86_64.
;;

sErrorUnbootable: db "Error: AurixOS can only be booted via UEFI on x86_64!", 0x0d, 0x0a, 0
sPressToReboot: db ""

AxBootEntry:
	mov si, sErrorUnbootable
	call PrintString
	jmp AxBootHalt

PrintString:
	lodsb
	or al, al
	jz .done
	mov ah, 0x0e
	mov bx, 0x0007
	int 0x10
	jmp PrintString
	.done:
		ret

AxBootHalt:
	cli
	hlt
	jmp AxBootHalt

times 510-($-$$) db 0
dw 0xaa55