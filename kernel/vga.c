/* kernel/drivers/vga.c
 *
 * VGA (Video Graphics Array) driver, contains methods to print text using VGA buffer
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/vga.h"

// pointer to VGA buffer
static volatile uint16_t *vga_buffer = (uint16_t *)VGA_BUFFER_ADDR;

// initial cursor position
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

// create a VGA entry from character and color
static inline uint16_t vga_entry(char c, uint8_t color){
	// cast the character to uint16_t, shift left color by 8 bits and OR both to create a VGA entry
	return (uint16_t)c | (uint16_t)color << 8;
}

// clear VGA screen with chosen color
void vga_clear_screen(uint8_t color) {
	for (uint16_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		vga_buffer[i] = vga_entry(' ', color);
	}
}
