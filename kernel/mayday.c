/* kernel/mayday.c
 *
 * function to be called when something really goes wrong
 
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/mayday.h"
#include "include/kernel.h"
#include "include/vga.h"
#include "include/lib.h"

void mayday_halt(const char *msg, const char *code) {
	char str_mayday[512] = "Mayday, Mayday, Mayday! Code ";
	strcat(str_mayday, code);
	strcat(str_mayday, " ");
	strcat(str_mayday, msg);
	printkc(str_mayday, VGA_COLOR_RED);
	for(;;);
}
