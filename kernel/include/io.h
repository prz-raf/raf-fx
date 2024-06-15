/* kernel/include/io.h
 *
 * io.c header file
 *
 * Licence: GNU General Public Licence v3
 * Author: Przemyslaw Rafalczuk <prz.raf@gmail.com>
 * Maintainer Przemyslaw Rafalczuk <prz.raf@gmail.com>
 *
 */

#ifndef IO_H
#define IO_H

#define PIC_MASTER_COMMAND 	0x20
#define PIC_MASTER_DATA 	0x21
#define PIC_SLAVE_COMMAND	0xA0
#define PIC_SLAVE_DATA		0xA1

// standard integer type definitions, like uint8_t
#include <stdint.h>

void out_byte(uint16_t port, uint8_t value);
uint8_t in_byte(uint16_t port);
void remap_pic();
void pic_eoi();

#endif // IO_H
