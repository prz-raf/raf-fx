; boot/boot.asm
; raf-fx bootloader
; Licence: GNU General Public License v3
; Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
; Maintainer: Przemyslaw Rafalczuk <prz.raf@gmail.com>

[bits 16]
[org 0x7c00] 					; Set the origin to 0x7c00, where BIOS expects bootloader to be

section .text 
global _start

; start with preparing the registers by setting them to default values
_start:
	mov bp, 0x9000
	mov sp, bp				; stack pointer starts with 0x7b00, just below the origin of 0x7c00

; keep printing inital message characters
print_msg_init:
	mov ah, 0xe				; BIOS function code to print characters
	mov si, msg_init			; load the address of init message
	call print_info				; print the message

; load kernel from the disk. 
load_kernel:
	mov bx, KERNEL_OFFSET			; Address to load the kernel
	mov dh, 12				; number of sectors
	mov dl, 0x00				; set the boot drive
	
	pusha					; save all general purpose registers
	push dx					; save DX register which has original number of sectors to read in DH
	
	mov ah, 0x02				; BIOS read sector function
	mov al, dh				; read specified number of sectors
	mov ch, 0x00				; cylinder 0
	mov cl, 0x02				; start from sector 2
	mov dh, 0x00				; head 0
	int 0x13				; BIOS interrupt to read the hard drive

	jc disk_read_failed			; jump to disk_read_failed if carry flag is set
	
	pop dx					; get back original number of sectors to read
	cmp al, dh				; compare original number of sectors to read with current one
	jne sectors_error			; print the error if numbers above don't match
	
	popa					; restore registers
	jmp disk_read_success			; if all good, let's continue in disk_read_success

; inidcator whether disk read was success (carry flag was not set)
disk_read_success:
	mov ah, 0x0e
	mov si, msg_disk_read_success
	call print_info
	jmp setup_gdt

; indicator whether disk read failed (carry flag was set)
disk_read_failed:
	mov ah, 0x0e
	mov si, msg_disk_read_failed
	call print_error

; indicator that original number of sectors to read is not equal to actual number
sectors_error:
	mov ah, 0x0e
	mov si, msg_sectors_error
	call print_error

; load GDT and enable protected mode, then jump to kernel entry point
setup_gdt:
	cli					; clear interrupts
	lgdt [gdt_descriptor]			; load global table descriptor register
	mov eax, cr0				; move CR0 value to EAX (CR0 indicates if protected mode is on)
	or eax, 0x1				; set PE bit (bit 0) 
	mov cr0, eax				; move EAX back to CR0 to enable protected mode
	
	jmp CODE_SEG:init_pm			; far jump to flush the pipeline and update CS
	
[bits 32]
init_pm:
	mov ax, DATA_SEG			; load data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, 0x90000			; set the stack pointer to for protected mode

	;jmp $					; reminds me of hours spent trying to makes this work. this is a memorial. do not remove 
	
	jmp 0x08:KERNEL_OFFSET			; jump to kernel entry point, 0x08 is the code segment selector

; function to print info and debug messages
print_info:
	lodsb					; load the byte from SI into AL and increment SI
	cmp al, 0				; check if loaded byte is 0
	je return				; if loaded byte is 0, return from function
	int 0x10				; BIOS interrupt to print character in AL
	jmp print_info				; repeat until message is printed

; function to print error messages and halt the cpu
print_error:
	lodsb
	cmp al, 0
	je halt
	int 0x10
	jmp print_error


; helper function, return from function call
return:
	ret
	
halt:
	cli					; clear interrupts
	hlt					; halt CPU
	
; define GDT (Global Descriptor Table) and GDT descriptor
gdt_start:
    dq 0x0

; code segment descriptor
gdt_code:
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10011010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

; data segment descriptor
gdt_data:
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10010010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16 bit)
    dd gdt_start ; address (32 bit)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

	KERNEL_OFFSET			equ	0x1000

	msg_init 			db 	'Booting raf-fx...', 13, 10, 0
	msg_disk_read_success		db 	'Disk read success!', 13, 10, 0
	msg_disk_read_failed		db	'Disk read failed!', 13, 10, 0
	msg_sectors_error		db	'Sectors error!', 13, 10, 0
	
	times 510-($-$$) db 0 			; pad of the rest of the sector with zeros
	dw 0xaa55				; boot signature
