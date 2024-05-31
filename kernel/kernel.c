/* kernel/kernel.c
 *
 * raf-fx kernel main entry point, starts the fun
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/kernel.h"
#include "include/print.h"

void kernel_main() {
	printk("Kernel loaded!                                                ");
	halt_cpu();
}

void halt_cpu(){
	while(1) {
		__asm__("hlt");
	}
}
