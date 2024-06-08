; kernel/asm/kernel.asm

; raf-fx main kernel entry point and low level initialization

; Licence: GNU General Public License v3
; Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
; Maintainer: Przemyslaw Rafalczuk <prz.raf@gmail.com>

[bits 32]
[extern kernel_main]
section .text.entry
global _start

_start:
	call kernel_main		; main kernel function for kernel.c
	jmp $
