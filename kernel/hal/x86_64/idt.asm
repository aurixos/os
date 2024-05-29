;;;++
; Module Name:  idt.asm
; Project:      AurixOS
;
; Copyright (c) 2024 Jozef Nagy
;
; This source is subject to the MIT License.
; See License.txt in the root of this repository.
; All other rights reserved.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
; SOFTWARE.
;;;--

%include "hal/x86_64/utils.asm"

global pHalLoadIdt
global pgHalIsrHandlers

extern HalHandleIsr

pHalLoadIdt:
	lidt [rdi]
	ret

pHalIsrStub:
	cld
	pushaq
	call HalHandleIsr
	popaq
	add rsp, 16
	iretq

%macro pHalIsrError 1
pHalIsrHandler%+%1:
	push %1
	jmp pHalIsrStub
%endmacro

%macro pHalIsrNoError 1
pHalIsrHandler%+%1:
	push 0
	push %1
	jmp pHalIsrStub
%endmacro

pHalIsrNoError 0
pHalIsrNoError 1
pHalIsrNoError 2
pHalIsrNoError 3
pHalIsrNoError 4
pHalIsrNoError 5
pHalIsrNoError 6
pHalIsrNoError 7
pHalIsrError 8
pHalIsrNoError 9
pHalIsrError 10
pHalIsrError 11
pHalIsrError 12
pHalIsrError 13
pHalIsrError 14
pHalIsrNoError 15
pHalIsrNoError 16
pHalIsrError 17
pHalIsrNoError 18
pHalIsrNoError 19
pHalIsrNoError 20
pHalIsrNoError 21
pHalIsrNoError 22
pHalIsrNoError 23
pHalIsrNoError 24
pHalIsrNoError 25
pHalIsrNoError 26
pHalIsrNoError 27
pHalIsrNoError 28
pHalIsrNoError 29
pHalIsrError 30
pHalIsrNoError 31

%assign Index 32
%rep 224
pHalIsrNoError Index
%assign Index Index+1
%endrep

section .data

pgHalIsrHandlers:
%assign Index 0
%rep 256
	dq pHalIsrHandler%+Index
%assign Index Index+1
%endrep
