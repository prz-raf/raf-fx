; bootloader.asm
; RafOS bootloader
; Licence: GNU General Public License v3
; Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
; Mainainer: Przemyslaw Rafalczuk <prz.raf@gmail.com>

[org 0x7c00] 		; Set the origin to 0x7c00, the start address of the boot sector
mov ah, 0x0e		; BOIS teletype function to print a character

mov al, 'L'
int 0x10
mov al, 'o'
int 0x10
mov al, 'a'
int 0x10
mov al, 'd'
int 0x10
mov al, 'i'
int 0x10
mov al, 'n'
int 0x10
mov al, 'g'
int 0x10
mov al, ' '
int 0x10
mov al, 'R'
int 0x10
mov al, 'a'
int 0x10
mov al, 'f'
int 0x10
mov al, 'O'
int 0x10
mov al, 'S'
int 0x10
mov al, ' '
int 0x10
mov al, 'k'
int 0x10
mov al, 'e'
int 0x10
mov al, 'r'
int 0x10
mov al, 'n'
int 0x10
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
mov al, '.'
int 0x10
mov al, '.'
int 0x10
mov al, '.'
int 0x10

; Load the kernel from disk
xor ax, ax 		; Zero out AX, to make sure we start clean
mov es, ax		; Set ES segment to AX value, which is zero. It now points to the beginning of memory 0x0000
mov bx, 0x1000
mov ah, 0x02
mov al, 0x04
mov ch, 0x00
mov cl, 0x02
mov dh, 0x00
mov dl, 0x80
int 0x13

jc load_error		; Jump to load error if there was an error

jmp 0x1000:0000		; Jump to kernel loaded at 0x1000

; Print error message "Bootloader error" if loading fails
load_error:
	mov ah, 0x0e
	mov al, 'B'
	int 0x10
	mov al, 'o'
        int 0x10
	mov al, 'o'
        int 0x10
	mov al, 't'
        int 0x10
	mov al, 'l'
        int 0x10
	mov al, 'o'
        int 0x10
	mov al, 'a'
        int 0x10
	mov al, 'd'
        int 0x10
	mov al, 'e'
        int 0x10
	mov al, 'r'
        int 0x10
	mov al, ' '
        int 0x10
	mov al, 'e'
        int 0x10
	mov al, 'r'
        int 0x10
	mov al, 'r'
        int 0x10
	mov al, 'o'
        int 0x10
	mov al, 'r'
        int 0x10
	hlt		; Halt the CPU

times 510-($-$$) db 0 	; Pad of the rest of the sector with zeros
dw 0xaa55		; Boot signature
