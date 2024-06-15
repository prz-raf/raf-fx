/* kernel/io.c
 *
 * contains hardware I/O functions
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/io.h"

// sends a byte to requested I/O port
inline void out_byte(uint16_t port, uint8_t value) {
	asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// receives a byte from requested I/O port
inline uint8_t in_byte(uint16_t port) {
	uint8_t ret_val;
	asm volatile ("inb %1, %0" : "=a"(ret_val) : "Nd"(port));

	return ret_val;
}

// remaps the Programmable Interrupt Controller (PIC) to avoid conflicts with CPU
// exceptions and sets new interrupt vector offset
void remap_pic() {
	// start initialization sequence for both master and slave PIC,
	// ICW4(Initialization Command Word 4) will be sent
	out_byte(PIC_MASTER_COMMAND, 0x11);
	out_byte(PIC_SLAVE_COMMAND, 0x11);

	// set the offset of master PIC to 0x20(32) and slave PIC to 0x28(40)
	out_byte(PIC_MASTER_DATA, 0x20);
	out_byte(PIC_SLAVE_DATA, 0x28);

	// tell master PIC that there's slave PIC at IRQ2
	out_byte(PIC_MASTER_DATA, 0x04);

	// tell slave PIC its cascade identity (connected to IRQ2 on the master)
	out_byte(PIC_SLAVE_DATA, 0x02);
	
	// set master and slave PIC to 8086/88 mode
	out_byte(PIC_MASTER_DATA, 0x01);
	out_byte(PIC_SLAVE_DATA, 0x01);

	// clear the registers to remove any leftover data
	out_byte(PIC_MASTER_DATA, 0x00);
	out_byte(PIC_SLAVE_DATA, 0x00);
}

// sends End Of Interrupt (EOI) signal to master PIC
void pic_eoi(){
	out_byte(PIC_MASTER_COMMAND, PIC_MASTER_COMMAND);
}
