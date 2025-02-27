#ifndef EPD_LIB_H
#define EPD_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _PICO_H
#include "pico/stdlib.h"
#include "hardware/spi.h"

// Pin definitions
#define EPD_SPI_TX 19
#define EPD_SPI_SCK 18
#define EPD_SPI_CS 17
#define EPD_DC 16
#define EPD_RST 20
#define EPD_BUSY 21
#endif

#define SOURCE_BITS 122
#define GATE_BITS 250

// Function declarations
void epd_output_byte(uint8_t data);
void epd_write_command(uint8_t command);
void epd_write_data(uint8_t data);
void epd_wait_until_idle(void);
void epd_hw_reset(void);
void epd_init(void);
void epd_write_img(uint32_t* img_src);
uint8_t epd_img_fetch_hex_32(int y, int x, uint32_t* img_src);

#endif // EPD_LIB_H
