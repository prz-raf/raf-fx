/* kernel/include/idt.h
 *
 * idt.c header file
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256

struct idt_entry {
	uint16_t offset_low; 				// lower 16 bits of the interrupt handler function address (the address is 32 bits)
	uint16_t selector;				// code segment selector in GDT, so we know what to execute when handling the interrupt
	uint8_t zero;					// always set to 0 to ensure proper alignment
	uint8_t type_attr;				// type and attributes of the interrupt gate, is it interrupt, trap or task and it privilege level
	uint8_t offset_high;				// upper 16 bits of the interrupt handler function address
} __attribute__ ((packed));				// make sure that the compiler does not add any padding, we need this structure exactly as defined

struct idt_ptr {
	uint16_t limit;					// the size of IDT in bytes minus one
	uint32_t base;					// base address of the IDT
};

void init_idt();
void set_idt_entry(int n, uint32_t handler);
void default_handler();
extern void load_idt(uint32_t idt_ptr);

#endif // IDT_H
