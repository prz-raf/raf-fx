/* kernel/lib.c
 *
 * standard library
 
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/lib.h"

// append source string at the end of destination string
void strcat(char *dest, const char *src) {
	while (*dest) dest++;
	while ((*dest++ = *src++));
}
