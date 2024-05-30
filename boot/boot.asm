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
	
	jmp setup_gdt
	
; keep printing inital message characters
print_msg_init:
	mov ah, 0xe				; BIOS function code to print characters
	mov si, msg_init			; load the address of init message
	call print_info				; print the messgae

; load kernel from the disk. 
load_kernel:
	mov ah, 0x02				; BIOS read sector function
	mov al, 9				; read 9 sectors
	mov ch, 0x00				; cylinder 0
	mov cl, 0x02				; sector 2
	mov dh, 0x00				; head 0
	mov dl, 0x80				; drive 0x80 (first hard drive)
	mov bx, 0x1000				; Address to load the kernel, (0x0000:0x1000)
	int 0x13				; BIOS interrupt to read the hard drive

	jc disk_read_failed			; jump to disk_read_failed if carry flag is set
	jmp disk_read_success			; if all good, let's continue in disk_read_success

; inidcator whether disk read was success (carry flag was not set)
disk_read_success:
	mov ah, 0x0e
	mov si, msg_disk_read_success
	call print_info
	jmp gdt_start

; indicator whether disk read failed (carry flag was set)
disk_read_failed:
	mov ah, 0x0e
	mov si, msg_disk_read_failed
	call print_error


; define GDT (Global Descriptor Table) and GDT descriptor
gdt_start:
	mov ah, 0x0e
	mov si, msg_gdt_start
	call print_info				; inform user that gdt_start has been reached

	gdt_null:				; null descriptor (mandatory)	
		dq 0x0000000000000000
	
	gdt_code:				; code segment descriptor		
		dq 0x00CF9A000000FFFF
		
		mov ah, 0x0e
		mov si, msg_gdt_code
		call print_info

	gdt_data:				; data segment descriptor
		mov ah, 0x0e
		mov si, msg_gdt_data
		call print_info
		
		dq 0x00CF92000000FFFF

gdt_end:
	mov ah, 0x0e
	mov si, msg_gdt_end
	call print_info				; inform user that we reached this point

gdt_descriptor:
	dw gdt_end - gdt_start - 1 		; limit (size of GDT - 1)
	dd gdt_start				; base address of GDT

; load GDT and enable protected mode, then jump to kernel entry point
setup_gdt:
	cli					; clear interrupts
	lgdt [gdt_descriptor]			; load global table descriptor register
	mov eax, cr0				; move CR0 value to EAX (CR0 indicates if protected mode is on)
	or eax, 0x1				; set PE bit (bit 0) 
	mov cr0, eax				; move EAX back to CR0 to enable protected mode
	jmp CODE_SEG:init_pm			; far jump to flush the pipeline and update CS

	CODE_SEG equ gdt_code - gdt_start	; calculate code segment offset
	DATA_SEG equ gdt_data - gdt_start	; calculate data segment offset
	
print_init_pm:
	mov ah, 0x0e				
	mov si, msg_entering_protected_mode
	call print_info
	
init_pm:
	mov ax, DATA_SEG			; load data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, 0x7b00				; set the stack pointer to for protected mode
	
	jmp 0x08:0x1000				; jump to kernel entry point, 0x08 is the code segment selector

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
	
	msg_init 			db 	'Booting raf-fx...', 13, 10, 0
	msg_disk_read_success		db 	'Disk read success!', 13, 10, 0
	msg_disk_read_failed		db	'Disk read failed!', 13, 10, 0
	msg_gdt_start			db	'Preparing GDT...', 13, 10, 0
	msg_gdt_code			db	'Setting code descriptor', 13, 10, 0
	msg_gdt_data			db	'Setting data descriptor', 13, 10, 0
	msg_gdt_end			db	'Preparing GDT done...', 13, 10, 0
	msg_entering_protected_mode 	db 	'Entering protected mode...', 13, 10, 0
	
	times 510-($-$$) db 0 			; pad of the rest of the sector with zeros
	dw 0xaa55				; boot signature
