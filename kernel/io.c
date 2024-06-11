/* kernel/io.c
 *
 * contains hardware I/O functions
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/io.h"

// Sends a byte to requested I/O port
inline void out_byte(uint16_t port, uint8_t value) {
	asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Receives a byte from requested I/O port
inline uint8_t in_byte(uint16_t port) {
	uint8_t ret_val;
	asm volatile ("inb %1, %0" : "=a"(ret_val) : "Nd"(port));

	return ret_val;
}
