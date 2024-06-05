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

// standard integer type definitions, like uint8_t
#include <stdint.h>

void out_byte(uint16_t port, uint8_t value);
uint8_t in_byte(uint16_t port);

#endif // IO_H
