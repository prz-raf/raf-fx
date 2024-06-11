/* kernel/include/kernel.h
 *
 * kernel.c header file
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void kernel_main();
void halt_cpu();
void printk(const char *str);
void printkc(const char *str, uint8_t color);
void printk_info();
void print_logo();

#endif // KERNEL_H
