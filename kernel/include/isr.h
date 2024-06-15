/* kernel/include/isr.h
 *
 * isr.c header file
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#ifndef ISR_H
#define ISR_H

void isr0(void);     	// divide by zero
void isr1(void);     	// debug exception
void isr2(void);     	// non-maskable interrupt
void isr3(void);     	// breakpoint exception
void isr4(void);     	// into detected overflow exception
void isr5(void);     	// out of bounds
void isr6(void);     	// invalid opcode
void isr7(void);     	// no coprocessor
void isr8(void);     	// double fault
void isr9(void);     	// coprocessor segment overrun
void isr10(void);    	// bad TSS
void isr11(void);    	// segment not present
void isr12(void);	// stack fault    
void isr13(void); 	// general protection fault
void isr14(void); 	// page fault
void isr15(void); 	// reserved
void isr16(void); 	// x87 floating-point exception
void isr17(void); 	// alignment check exception
void isr18(void); 	// machine check exception
void isr19(void); 	// SIMD floating-point exception
void isr20(void); 	// virtualization exception
void isr21(void); 	// control protection exception
void isr22(void); 	// reserved
void isr23(void); 	// reserved
void isr24(void); 	// reserved
void isr25(void); 	// reserved
void isr26(void); 	// reserved
void isr27(void); 	// reserved
void isr28(void); 	// reserved
void isr29(void); 	// reserved
void isr30(void); 	// security exception
void isr31(void); 	// reserved

void isr32_handler(void);	// timer interrupt handler
void isr33_handler(void);	// keyboard interrupt handler

#endif // ISR_H
