; boot.asm
; raf-fx bootloader
; Licence: GNU General Public License v3
; Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
; Maintainer: Przemyslaw Rafalczuk <prz.raf@gmail.com>

[org 0x7c00] 					; Set the origin to 0x7c00, where BIOS expects bootloader to be

section .text 
global _start

; start with preparing the registers by setting them to default values
_start:
	cli					; clear interrupts
	xor ax, ax				; set AX to 0, beginning of initial cleanup
	mov ss, ax				; set stack segment to 0
	mov sp, 0x7b00				; stack pointer starts with 0x7b00, just below the origin of 0x7c00
	mov ds, ax				; set data segment to 0
	mov es, ax				; set extra segment to 0
	sti					; enable interrupts
	
	mov si, init_msg			; load the address of init message, beginning of message printing
	mov ah, 0x0e				; BIOS function code to print characters

; keep printing inital message characters
print_init_msg:
	lodsb					; helper function that loads byte DS:SI (data segment + source index) into AL and increments SI
	cmp al, 0				; check if AL is 0
	je load_kernel				; jump to print_init_done if the last value in AL was 0
	int 0x10				; BIOS interrupt, print character from AL
	jmp print_init_msg			; repeat this step until AL is not 0
	
; load kernel from the disk. 
load_kernel:
	mov ah, 0x02				; BIOS read sector function
	mov al, 0x01				; read 1 sector
	mov ch, 0x00				; cylinder 0
	mov cl, 0x02				; sector 2
	mov dh, 0x00				; head 0
	mov dl, 0x80				; drive 0x80 (first hard drive)
	mov bx, 0x1000				; Address to load the kernel, (0x0000:0x1000)
	int 0x13				; BIOS interrupt to read the hard drive

	jc load_kernel_error			; jump to load_kernel_error if carry flag is set
	jmp kernel_loaded			; if all good, let's continue in kernel_loaded

; if an error has been encountered (carry flag is set), print an error and halt the CPU
load_kernel_error:
	mov ah, 0x0e				; BIOS function to print characters
	mov si, load_kernel_error_msg		; load the address of error message

; keep printing kernel load error until AL is 0
print_load_kernel_error:
	lodsb					; load the byte from SI into AL and increment SI
	cmp al, 0				; check if loaded byte is 0
	je halt					; if loaded byte is 0, jump to halt
	int 0x10				; BIOS interrupt to print character in AL
	jmp print_load_kernel_error		; repeat until message is printed

; TO BE CONTINUED
kernel_loaded:
	jmp $
	
halt:
	cli					; clear interrupts
	hlt					; halt CPU
	
	init_msg db 'Booting raf-fx...', 13, 10, 0
	load_kernel_error_msg db 'Unable to read kernel from disk!', 0
	
	times 510-($-$$) db 0 			; pad of the rest of the sector with zeros
	dw 0xaa55				; boot signature
