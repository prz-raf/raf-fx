/* kernel/vga.c
 *
 * VGA (Video Graphics Array) driver, contains methods to print text using VGA buffer
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#include "include/vga.h"
#include "include/io.h"

// pointer to VGA buffer
static volatile uint16_t *vga_buffer = (uint16_t *)VGA_BUFFER_ADDR;

// initial cursor position
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

// create a VGA entry from character and color
static inline uint16_t vga_entry(char c, uint8_t color){
	/*  Combines character and its color into a single VGA entry
 	 *  - Character is stored in the first byte (lower 8 bits)
	 *  - Color is stored in the second byte (higher 8 bits)
	 */

	return (uint16_t)c | (uint16_t)color << 8;
}

static void vga_set_cursor_position(uint8_t x, uint8_t y){
	uint16_t pos = y * VGA_WIDTH + x;
	
	// tell VGA register selector that the next data value will be the cursor position low byte
	out_byte(VGA_REGISTER_SELECTOR, VGA_CURSOR_POS_LOW_BYTE);

	/*  send the low byte of cursor position to the VGA data register - convert to uint8_t and 
	 *  do bitwise AND 0xFF (11111111)
	 */
	out_byte(VGA_REGISTER_DATA, (uint8_t)(pos & 0xff));
	
	// tell VGA register selector that the next data value will be the cursor position high byte
	out_byte(VGA_REGISTER_SELECTOR, VGA_CURSOR_POS_HIGH_BYTE);

	/*  send the high byte of cursor position to the VGA data register - convert to uint8_t
	 *  shifting the bytes to the right at the same time and then do bitwise AND 0xff (11111111)
	 */
      	out_byte(VGA_REGISTER_DATA, (uint8_t)((pos >> 8) & 0xff));	
	
	// aaaand finally update our internal cursor position variables
	cursor_x = x;
	cursor_y = y;
}

void vga_clear_screen(uint8_t color) {
	/*  Clears VGA screen in text mode and sets cursor in the beginning of VGA buffer
	 *  - Color constants can be found in vga.h
	 */
	
	/*  iterate through the whole VGA buffer flat array and set every byte to space with
	 *  chosen color
	 */  
	for (uint16_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		vga_buffer[i] = vga_entry(' ', color);
	}

	// and set the cursor position to the very beginning of the VGA buffer
	vga_set_cursor_position(0, 0);
}

