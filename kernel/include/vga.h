/* kernel/include/vga.h
 *
 * vga.c header file
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#ifndef VGA_H
#define VGA_H

// standard integer type definitions, like uint8_t
#include <stdint.h>

// VGA text mode buffer start address
#define VGA_BUFFER_ADDR 0xb8000

// VGA control registers
#define VGA_REGISTER_SELECTOR 0x3d4
#define VGA_REGISTER_DATA 0x3d5

// other VGA constants
#define VGA_CURSOR_POS_LOW_BYTE 0x0f
#define VGA_CURSOR_POS_HIGH_BYTE 0x0e

// VGA text mode dimensions
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

void vga_clear_screen(uint8_t color);
void vga_scroll(uint8_t color);
void vga_put_char(char c, uint8_t color, uint8_t x, uint8_t y);
void vga_puts(const char *str, uint8_t color);


#endif // VGA_H
