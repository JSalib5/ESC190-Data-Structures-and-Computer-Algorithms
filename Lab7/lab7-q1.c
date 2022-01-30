
#include "c_img.h"
#include <stdio.h>
#include <math.h>

void brightness_changer(struct rgb_img ** im, float change){
        int height = (*im)->height;
        int width = (*im)->width;
        for (int i = 0; i<=height; i++){
                for (int j = 0; j<=width; j++){
                        uint8_t r = get_pixel(*im, i, j, 0);
                        uint8_t g = get_pixel(*im, i, j, 1);
                        uint8_t b = get_pixel(*im, i, j, 2);
                        uint8_t n_r = r * change;
                        uint8_t n_g = g * change;
                        uint8_t n_b = b * change; 
                        if (n_r < 255){r = (int)(r * change);}else{r=255;}
                        if (n_g < 255){g = (int)(g * change);}else{g=255;}
                        if (n_b < 255){b = (int)(b * change);}else{b=255;}
                        set_pixel(*im, i, j, r, g, b);
                }
        }
}

int main(void){
        struct rgb_img * im1;
        struct rgb_img * im2;
        struct rgb_img * im3;
        struct rgb_img * im4;
        struct rgb_img * im5;
        struct rgb_img * im[5] = {im1, im2, im3, im4, im5};
        size_t height = 533;
        size_t width = 354;
        float change[5] = {0.1, 0.5, 1.01, 1.05, 1.08};
        char files[5][100] = {"img1.bin",
                         "img2.bin",
                         "img3.bin",
                         "img4.bin",
                         "img5.bin"};
        for (int i = 0; i<5; i++){
                create_img(&(im[i]), height, width);
                read_in_img(&(im[i]), "UofTPresidentMericGertler-smaller.bin");
                brightness_changer(&(im[i]), change[i]);  
                write_img(im[i], *(files+i));
        }
        return 0;
}