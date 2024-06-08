/* kernel/idt.c
 *
 * defines and sets up Interrupt Descriptor Table (IDT)
 
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/idt.h"

// definte the IDT with specified number of entries (default 256)
struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idt_p;

void set_idt_entry(int index, uint32_t handler) {
	/*
	 * 	sets an IDT entry
	 *
	 * 	int index: an index in IDT table
	 * 	uint32_t handler: the address of an interrupt handler function
	 */
	
	idt[index].offset_low = handler & 0xFFFF;					// extract the lower 16 bits from handler address
	idt[index].selector = 0x08;							// code segment selector in the GDT table
	idt[index].zero = 0;
	idt[index].type_attr = 0x8E;							// 10001110
	idt[index].offset_high = (handler >> 16) & 0xFFFF;				// extract the higher 16 bits from handler address, by shifting them right
}

void init_idt() {
	idt_p.limit = sizeof(idt) - 1;
	idt_p.base = (uint32_t)&idt;

	for (int i=0; i < IDT_ENTRIES; i++) {
		set_idt_entry(i, (uint32_t)default_handler);				// for now set each IDT entry with default handler, a placeholder
	}
	
	load_idt((uint32_t)&idt_p);							// load IDT using external assembly function
}
											
void default_handler() {}								// default handler, placeholder

