/* kernel/kernel.c
 *
 * raf-fx kernel main entry point, starts the fun
 
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/kernel.h"
#include "include/vga.h"
#include "include/idt.h"
#include "include/mayday.h"
// #include "include/isr.h"

#define KERNEL_NAME "raf-fx"
#define KERNEL_STAGE "dev"
#define KERNEL_VERSION "0.1"
#define KERNEL_LICENCE "GNU GPL v3"

__attribute__((section(".text.kernel"))) void kernel_main() {
	vga_clear_screen(VGA_COLOR_WHITE | VGA_COLOR_BLACK << 4);
	
	vga_print_ready();
	
	init_idt();

	printk_info();
	
	halt_cpu();
}

void halt_cpu(){
	while(1) {
		__asm__("hlt");
	}
}

// universal function to output kernel messages, uses white character color
void printk(const char *str) {
	// as for now, only use VGA driver functionality
	vga_puts(str, VGA_COLOR_WHITE);
	vga_puts("\n", VGA_COLOR_WHITE);
}

// it's like printk, but let's you choose the color of the text
void printkc(const char *str, uint8_t color) {
	// as for now, only use VGA driver functionality
	vga_puts(str, color);
	vga_puts("\n", color);
}

void printk_info() {
	print_logo();
	vga_puts("\n", VGA_COLOR_WHITE);
	vga_puts(">>> ", VGA_COLOR_WHITE);
	vga_puts(KERNEL_NAME, VGA_COLOR_WHITE);
	vga_puts(" ", VGA_COLOR_WHITE);
	vga_puts(KERNEL_STAGE, VGA_COLOR_WHITE);
	vga_puts(" ", VGA_COLOR_WHITE);
	vga_puts(KERNEL_VERSION, VGA_COLOR_WHITE);
	vga_puts(" ", VGA_COLOR_WHITE);
	vga_puts(KERNEL_LICENCE, VGA_COLOR_WHITE);
	vga_puts(" <<<", VGA_COLOR_WHITE);
	vga_puts("\n", VGA_COLOR_WHITE);
}

void print_logo(){
	vga_puts("\n", VGA_COLOR_WHITE);
	vga_puts("\n", VGA_COLOR_WHITE);
    	vga_puts("               _____           _____        \n", VGA_COLOR_WHITE);
    	vga_puts("____________ _/ ____\\        _/ ____\\__  ___\n", VGA_COLOR_WHITE);
    	vga_puts("\\_  __ \\__  \\\\   __\\  ______ \\   __\\\\  \\/  /\n", VGA_COLOR_WHITE);
    	vga_puts(" |  | \\// __ \\|  |   /_____/  |  |   >    < \n", VGA_COLOR_WHITE);
    	vga_puts(" |__|  (____  /__|            |__|  /__/\\_ \\\n", VGA_COLOR_WHITE);
    	vga_puts("            \\/                            \\/\n", VGA_COLOR_WHITE);
	vga_puts("\n", VGA_COLOR_WHITE);
	vga_puts("\n", VGA_COLOR_WHITE);
}
