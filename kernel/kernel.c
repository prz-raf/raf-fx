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

__attribute__((section(".text.kernel"))) void kernel_main() {
	vga_clear_screen(VGA_COLOR_WHITE | VGA_COLOR_BLACK << 4);
	vga_puts("Welcome to raf-fx!\n", VGA_COLOR_WHITE);
	halt_cpu();
}

void halt_cpu(){
	while(1) {
		__asm__("hlt");
	}
}
