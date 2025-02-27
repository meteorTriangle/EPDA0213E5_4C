#include "epd_lib.h"

void epd_output_byte(uint8_t data) {
    #ifdef _PICO_H
    spi_write_blocking(spi0, &data, sizeof(uint8_t));
    #endif
}

void epd_write_command(uint8_t command) {
    #ifdef _PICO_H
    gpio_put(EPD_DC, false);
    gpio_put(EPD_SPI_CS, false);
    sleep_us(1);
    epd_output_byte(command);
    gpio_put(EPD_SPI_CS, true);
    #endif
}

void epd_write_data(uint8_t data) {
    #ifdef _PICO_H
    gpio_put(EPD_DC, true);
    gpio_put(EPD_SPI_CS, false);
    sleep_us(1);
    epd_output_byte(data);
    gpio_put(EPD_SPI_CS, true);
    #endif
}

void epd_wait_until_idle(void) {
    #ifdef _PICO_H
    sleep_ms(2);
    while(gpio_get(EPD_BUSY) != 1) {
        tight_loop_contents();
    }
    #endif
}

void epd_hw_reset(void) {
    #ifdef _PICO_H
    sleep_ms(20);
    gpio_put(EPD_RST, false);
    sleep_ms(40);
    gpio_put(EPD_RST, true);
    sleep_ms(50);
    #endif
}

void epd_init(void) {
    #ifdef _PICO_H
    gpio_init(EPD_SPI_CS);
    gpio_init(EPD_DC);
    gpio_init(EPD_RST);
    gpio_init(EPD_BUSY);
    gpio_set_function(EPD_SPI_TX , GPIO_FUNC_SPI);
    gpio_set_function(EPD_SPI_SCK , GPIO_FUNC_SPI);
    spi_init(spi0, 100*1000);
    
    gpio_set_dir(EPD_SPI_CS, GPIO_OUT);
    gpio_set_dir(EPD_DC, GPIO_OUT);
    gpio_set_dir(EPD_RST, GPIO_OUT);
    gpio_set_dir(EPD_BUSY, GPIO_IN);

    gpio_put(EPD_SPI_CS, true);

    epd_hw_reset();
    epd_wait_until_idle();

    epd_write_command(0x4D);
    epd_write_data(0x78);

    epd_write_command(0x00);
    epd_write_data(0b00000111);
    epd_write_data(0b00001001);

    epd_write_command(0x01);
    epd_write_data(0x07);
    epd_write_data(0x00);
    epd_write_data(0x22);
    epd_write_data(0x78);
    epd_write_data(0x0A);
    epd_write_data(0x22);

    epd_write_command(0x03); //POFS
    epd_write_data(0x10);
    epd_write_data(0x54);
    epd_write_data(0x44);
    
    epd_write_command(0x06); //BTST_P
    epd_write_data(0x0F);
    epd_write_data(0x0A);
    epd_write_data(0x2F);
    epd_write_data(0x25);
    epd_write_data(0x22);
    epd_write_data(0x2E);
    epd_write_data(0x21); 
    
    epd_write_command(0x30); //CDI
    epd_write_data(0x02);
    
    epd_write_command(0x41);
    epd_write_data(0x00);
    
    epd_write_command(0x50);
    epd_write_data(0x37);
    epd_write_command(0x60);
    epd_write_data(0x02);
    epd_write_data(0x02);
    
    epd_write_command(0x61); 
    epd_write_data(0x00);   // Source_BITS_H
    epd_write_data(0x80);   // Source_BITS_L
    epd_write_data(0x00);     // Gate_BITS_H
    epd_write_data(0xFA);    


    epd_write_command(0x65);
    epd_write_data(0x00);
    epd_write_data(0x00);
    epd_write_data(0x00);
    epd_write_data(0x00);
    
    epd_write_command(0xE7);
    epd_write_data(0x1C);
    
    epd_write_command(0xE3); 
    epd_write_data(0x22);

    epd_write_command(0xE0); 
    epd_write_data(0x00);
    
    epd_write_command(0xB4);
    epd_write_data(0xD0);
    epd_write_command(0xB5);
    epd_write_data(0x03);
    
    epd_write_command(0xE9);
    epd_write_data(0x01); 
    #endif
}

uint8_t epd_img_fetch_hex_32(int y, int x, uint32_t* img_src) {
    int hsize = GATE_BITS/16 + (GATE_BITS%16==0 ? 0 : 1);
    if(y >= SOURCE_BITS || x >= GATE_BITS) {
        return 0b11;
    }
    else {
        uint32_t target = *(img_src + hsize*y + x/16);
        return (target) >> ((15 - x%16)*2) & 0b11;
    }
}

void epd_write_img(uint32_t* img_src) {
    #ifdef _PICO_H
    epd_write_command(0x10);

    for(uint i = 0; i < GATE_BITS; i++) {
        for(uint j = 0; j < 32; j++) {
            uint8_t ty = (epd_img_fetch_hex_32(j*4+0,i, img_src)<<6) | 
                        (epd_img_fetch_hex_32(j*4+1,i, img_src)<<4) | 
                        (epd_img_fetch_hex_32(j*4+2,i, img_src)<<2) | 
                        (epd_img_fetch_hex_32(j*4+3,i, img_src)<<0);
            epd_write_data(ty);
        }
    }

    epd_write_command(0x17);
    epd_write_data(0xA5);
    sleep_ms(1000);
    epd_wait_until_idle();

    gpio_put(EPD_RST, false);
    gpio_put(EPD_DC, false);
    gpio_put(EPD_SPI_CS, false);
    #endif
}
