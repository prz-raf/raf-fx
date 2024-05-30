/* kernel/print.c
 *
 * Provides print functionality for the kernel using x86 text mode
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/print.h"

void printk(const char *str){
	// address below is the starting address of the video memory for text mode on x86
	volatile char *v = (volatile char*)0xb800;

	while(*str){
		// assign character byte
		*v++ = *str++;
		
		// assign attribute byte, in this case light grey character on black background
		*v++ = 0x07; 	
	}
}
