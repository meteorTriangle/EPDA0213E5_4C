#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "epd_lib.h"
#include "png2bitmap/my_img__.c"
#include "string.h"


uint32_t* getimgbyname(const char* img_name) {
    int img_n = sizeof(img_) / sizeof(img_[0]);
    for (int i = 0; i < img_n; i++) {
        int img_nameLen = *img_[i] & 0xFF;
        char* img_name_f = (char*)malloc(img_nameLen + 1);
        for(int j = 0; j < img_nameLen; j++) {
            img_name_f[j] = *(img_[i]+1+j/4) >> (8 * (3-j%4)) & 0xFF;
        }
        printf("%s\n", img_name_f);
        img_name_f[img_nameLen] = '\0';
        if (strcmp(img_name, img_name_f) == 0) {
            return &((img_[i])[1+(img_nameLen/4 + (img_nameLen%4==0? 0:1))]);
        }
    }
    return NULL;
}


int main()
{
    stdio_init_all();
    // SPI initialisation. This example will use SPI at 1MHz.
    epd_init();
    epd_write_img(getimgbyname("test012.png"));
    
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
