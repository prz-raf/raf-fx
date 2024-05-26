; bootloader.asm

[org 0x7c00] 		; Set the origin to 0x7c00, the start address of the boot sector
mov ah, 0x0e		; BOIS teletype function to print a character

mov al, 'B'
int 0x10
mov al, 'o'
int 0x10
mov al, 'o'
int 0x10
mov al, 't'
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
mov al, '.'
int 0x10
mov al, '.'
int 0x10
mov al, '.'
int 0x10

hlt			; Halt the CPU
times 510-($-$$) db 0 	; Pad of the rest of the sector with zeros
dw 0xaa55		; Boot signature
