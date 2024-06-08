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

#define KERNEL_NAME "raf-fx"
#define KERNEL_STAGE "dev"
#define KERNEL_VERSION "0.1"
#define KERNEL_LICENCE "GNU General Public Licence v3"

__attribute__((section(".text.kernel"))) void kernel_main() {
	vga_clear_screen(VGA_COLOR_WHITE | VGA_COLOR_BLACK << 4);

	vga_puts("Initializing IDT\n", VGA_COLOR_WHITE);
	init_idt();

	vga_puts("Init complete\n", VGA_COLOR_WHITE);

	print_kernel_info();

	halt_cpu();
}

void halt_cpu(){
	while(1) {
		__asm__("hlt");
	}
}

void print_kernel_info() {
	vga_puts(KERNEL_NAME, VGA_COLOR_WHITE);
	vga_puts(" ", VGA_COLOR_WHITE);
	vga_puts(KERNEL_STAGE, VGA_COLOR_WHITE);
	vga_puts(" ", VGA_COLOR_WHITE);
	vga_puts(KERNEL_VERSION, VGA_COLOR_WHITE);
	vga_puts(" ", VGA_COLOR_WHITE);
	vga_puts(KERNEL_LICENCE, VGA_COLOR_WHITE);
}
