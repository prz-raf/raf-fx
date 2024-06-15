/* kernel/isr.c
 *
 * Interrupt Service Routines handler
 
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/isr.h"
#include "include/mayday.h"
#include "include/io.h"

// reserved interrupts for CPU exceptions
void isr0(void) { mayday_halt("ISR0 Divide by Zero", "0"); }
void isr1(void) { mayday_halt("ISR1 Debug Exception", "1"); }
void isr2(void) { mayday_halt("ISR2 Non-maskable Interrupt", "2"); }
void isr3(void) { mayday_halt("ISR3 Breakpoint Exception", "3"); }
void isr4(void) { mayday_halt("ISR4 Into Detected Overflow", "4"); }
void isr5(void) { mayday_halt("ISR5 Out of Bounds Exception", "5"); }
void isr6(void) { mayday_halt("ISR6 Invalid Opcode", "6"); }
void isr7(void) { mayday_halt("ISR7 No Coprocessor", "7"); }
void isr8(void) { mayday_halt("ISR8 Double Fault", "8"); }
void isr9(void) { mayday_halt("ISR9 Coprocessor Segment Overrun", "9"); }
void isr10(void) { mayday_halt("ISR10 Bad TSS", "10"); }
void isr11(void) { mayday_halt("ISR11 Segment Not Present", "11"); }
void isr12(void) { mayday_halt("ISR12 Stack Fault", "12"); }
void isr13(void) { mayday_halt("ISR13 General Protection Fault", "13"); }
void isr14(void) { mayday_halt("ISR14 Page Fault", "14"); }
void isr15(void) { mayday_halt("ISR15 Reserved", "15"); }
void isr16(void) { mayday_halt("ISR16 x87 Floating-Point Exception", "16"); }
void isr17(void) { mayday_halt("ISR17 Alignment Check", "17"); }
void isr18(void) { mayday_halt("ISR18 Machine Check", "18"); }
void isr19(void) { mayday_halt("ISR19 SIMD Floating-Point Exception", "19"); }
void isr20(void) { mayday_halt("ISR20 Virtualization Exception", "20"); }
void isr21(void) { mayday_halt("ISR21 Control Protection Exception", "21"); }
void isr22(void) { mayday_halt("ISR22 Reserved", "22"); }
void isr23(void) { mayday_halt("ISR23 Reserved", "23"); }
void isr24(void) { mayday_halt("ISR24 Reserved", "24"); }
void isr25(void) { mayday_halt("ISR25 Reserved", "25"); }
void isr26(void) { mayday_halt("ISR26 Reserved", "26"); }
void isr27(void) { mayday_halt("ISR27 Reserved", "27"); }
void isr28(void) { mayday_halt("ISR28 Reserved", "28"); }
void isr29(void) { mayday_halt("ISR29 Reserved", "29"); }
void isr30(void) { mayday_halt("ISR30 Security Exception", "30"); }
void isr31(void) { mayday_halt("ISR31 Reserved", "31"); }

// ISR stubs

// timer interrupt handler
void isr32_handler(void) {
	// for now let's just inform PIC that we received interrupt
	pic_eoi();
}

// keyboard interrupt handler
void isr33_handler(void){
	pic_eoi();
}

