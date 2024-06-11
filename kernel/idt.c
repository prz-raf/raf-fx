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

/*
 * 
 * sets an IDT entry
 *
 * int index: an index in IDT table
 * uint32_t handler: the address of an interrupt handler function
 * 
 */
void set_idt_entry(int index, uint32_t handler) {
	
	// extract the lower 16 bits from handler address
	idt[index].offset_low = handler & 0xFFFF;
	
	// code segment selector in the GDT table					
	idt[index].selector = 0x08;
	
						
	idt[index].zero = 0;
	
	// 10001110
	idt[index].type_attr = 0x8E;
	
	// extract the higher 16 bits from handler address, by shifting them right				
	idt[index].offset_high = (handler >> 16) & 0xFFFF;				
}

void init_idt() {
	idt_p.limit = sizeof(idt) - 1;
	idt_p.base = (uint32_t)&idt;
	
	// for now set each IDT entry with default handler, a placeholder
	for (int i=0; i < IDT_ENTRIES; i++) {
		set_idt_entry(i, (uint32_t)default_handler);
	}
	
	// load IDT using external assembly function
	load_idt((uint32_t)&idt_p);							
}

// default handler, placeholder										
void default_handler() {}								

