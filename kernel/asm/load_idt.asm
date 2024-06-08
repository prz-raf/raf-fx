; kernel/asm/load_it.asm

; loads Interrupt Descriptor Table (IDT)

; Licence: GNU General Public License v3
; Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
; Maintainer: Przemyslaw Rafalczuk <prz.raf@gmail.com>

global load_idt

load_idt:
	mov eax, [esp+4]		; load the address of idt_ptr argument passed in kernel/include/idt.h (in x86 esp+4 is always 1st argument) into accumulator
	lidt [eax]			; load the address stored in the accumulator into the IDT register
	ret
