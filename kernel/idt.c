/* kernel/idt.c
 *
 * defines and sets up Interrupt Descriptor Table (IDT)
 
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/idt.h"
#include "include/isr.h"
#include "include/kernel.h"
#include "include/io.h"

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
	printk("Setting IDT limit");
	idt_p.limit = sizeof(idt) - 1;
	printk("Setting IDT pointer base");
	idt_p.base = (uint32_t)&idt;
	
	// set reserved ISRs 0-31 for CPU exceptions
	printk("Setting reserved ISRs for CPU exceptions");
	set_idt_entry(0, (uint32_t)isr0);
	set_idt_entry(1, (uint32_t)isr1);
	set_idt_entry(2, (uint32_t)isr2);
	set_idt_entry(3, (uint32_t)isr3);
	set_idt_entry(4, (uint32_t)isr4);
	set_idt_entry(5, (uint32_t)isr5);
	set_idt_entry(6, (uint32_t)isr6);
	set_idt_entry(7, (uint32_t)isr7);
	set_idt_entry(8, (uint32_t)isr8);
	set_idt_entry(9, (uint32_t)isr9);
	set_idt_entry(10, (uint32_t)isr10);
	set_idt_entry(11, (uint32_t)isr11);
	set_idt_entry(12, (uint32_t)isr12);
	set_idt_entry(13, (uint32_t)isr13);
	set_idt_entry(14, (uint32_t)isr14);
	set_idt_entry(15, (uint32_t)isr15);
	set_idt_entry(16, (uint32_t)isr16);
	set_idt_entry(17, (uint32_t)isr17);
	set_idt_entry(18, (uint32_t)isr18);
	set_idt_entry(19, (uint32_t)isr19);
	set_idt_entry(20, (uint32_t)isr20);
	set_idt_entry(21, (uint32_t)isr21);
	set_idt_entry(22, (uint32_t)isr22);
	set_idt_entry(23, (uint32_t)isr23);
	set_idt_entry(24, (uint32_t)isr24);
	set_idt_entry(25, (uint32_t)isr25);
	set_idt_entry(26, (uint32_t)isr26);
	set_idt_entry(27, (uint32_t)isr27);
	set_idt_entry(28, (uint32_t)isr28);
	set_idt_entry(29, (uint32_t)isr29);
	set_idt_entry(30, (uint32_t)isr30);
	set_idt_entry(31, (uint32_t)isr31);
	
	// set timer interrupt handler
	printk("Setting timer interrupt handler");
	set_idt_entry(32, (uint32_t)isr32_handler);

	// set keyboard interrupt handler
	printk("Setting keyboard interrupt handler");
	set_idt_entry(33, (uint32_t)isr33_handler);
	
	// set other IDT entries with default handler, a placeholder
	printk("Setting IDT placeholders");
	for (int i=34; i < IDT_ENTRIES; i++) {
		set_idt_entry(i, (uint32_t)default_handler);
	}

	// remap Programmable Interrupt Controller
	printk("Remapping PIC");
	remap_pic();
	
	// load IDT using external assembly function
	printk("Loading IDT table");
	load_idt((uint32_t)&idt_p);

	// enable interrupts
	printk("Enabling interrupts");
	__asm__ __volatile__("sti");	

	printk("IDT init complete");
}

// default handler, placeholder										
void default_handler() {}								

