; kernel/asm/interrupts.asm

; defines ISR stubs

; Licence: GNU General Public License v3
; Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
; Maintainer: Przemyslaw Rafalczuk <prz.raf@gmail.com>

[extern isr32_handler]
[extern isr33_handler]

global isr32
global isr33

section .text

isr32:						; IRQ0 - timer
	cli
	pusha
	call isr32_handler
	popa
	sti
	iret

isr33:						; IRQ1 - keyboard
	cli
	pusha
	call isr33_handler
	popa
	sti
	iret
