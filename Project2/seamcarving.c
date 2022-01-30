#include "c_img.h"
#include "seamcarving.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calc_energy(struct rgb_img *im, struct rgb_img **grad){
    int height = im->height;
    int width = im->width;
    create_img(grad, height, width);
    (*grad)->height = height;
    (*grad)->width = width;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int b_y, g_y, r_y, r_x, g_x, b_x;
            int r_l, g_l, b_l, r_r, g_r, b_r, r_t, b_t, g_t, r_b, b_b, g_b;
            int delta_x, delta_y;
            uint8_t energy;
            r_l = get_pixel(im, y, x==0? width - 1: x - 1, 0);
            g_l = get_pixel(im, y, x==0? width - 1: x - 1, 1);
            b_l = get_pixel(im, y, x==0? width - 1: x - 1, 2);
            r_r = get_pixel(im, y, x==width-1? 0: x + 1, 0);
            g_r = get_pixel(im, y, x==width-1? 0: x + 1, 1);
            b_r = get_pixel(im, y, x==width-1? 0: x + 1, 2);
            r_t = get_pixel(im, y==0? height - 1: y - 1, x, 0);
            g_t = get_pixel(im, y==0? height - 1: y - 1, x, 1);
            b_t = get_pixel(im, y==0? height - 1: y - 1, x, 2);
            r_b = get_pixel(im, y==height-1? 0: y + 1, x, 0);
            g_b = get_pixel(im, y==height-1? 0: y + 1, x, 1);
            b_b = get_pixel(im, y==height-1? 0: y + 1, x, 2);
            r_x = r_r - r_l;
            g_x = g_r - g_l;
            b_x = b_r - b_l;
            r_y = r_b - r_t;
            g_y = g_b - g_t;
            b_y = b_b - b_t;
            delta_x = r_x*r_x + g_x*g_x + b_x*b_x;
            delta_y = r_y*r_y + g_y*g_y + b_y*b_y;
            energy = (uint8_t)((sqrt(delta_x + delta_y))/10);
            set_pixel(*grad, y, x, energy, energy, energy);
        }
    }
}

double min(double d1, double d2, double d3){
    if (d1 <= d2 && d1 <= d3) {
        return d1;
    }
    else if (d2 <= d1 && d2 <= d3) {
        return d2;
    }
    else {
        return d3;
    }
}

void dynamic_seam(struct rgb_img *grad, double **best_arr){
    int height = grad->height;
    int width = grad->width;
    *best_arr = (double*)malloc(sizeof(double)*height*width);
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (i == 0) {
                (*best_arr)[i*width+j] = get_pixel(grad, i, j, 0);
            }
            else{
                if (j == 0) {
                    (*best_arr)[i*width+j] = get_pixel(grad, i, j, 0) + min((*best_arr)[(i-1)*width+j], (*best_arr)[(i-1)*width+j], (*best_arr)[(i-1)*width+j+1]);
                }
                else if (j==width-1) {
                    (*best_arr)[i*width+j] = get_pixel(grad, i, j, 0) + min((*best_arr)[(i-1)*width+j-1], (*best_arr)[(i-1)*width+j], (*best_arr)[(i-1)*width+j]);
                }
                else{
                    (*best_arr)[i*width+j] = get_pixel(grad, i, j, 0) + min((*best_arr)[(i-1)*width+j-1], (*best_arr)[(i-1)*width+j], (*best_arr)[(i-1)*width+j+1]);
                }
            }
        }
    }
}

void recover_path(double *best, int height, int width, int **path){
    *path = (int*)malloc(height*sizeof(int));
	(*path)[height - 1] = 100000000.0;
	double min_num = 100000000.0;
	for (int y = 0; y < width; y++) {
		if (min_num > best[(height - 1) * width + y]) {
			(*path)[height - 1] = y;
			min_num = best[(height - 1) * width + y];
		}
	}

	for (int x = height - 2; x >= 0; x--) {
		int y = (*path)[x + 1];
		double min = 100000000.0;
		for (int index = (y > 0 ? y - 1 : 0); index <= (y < width - 1 ? y + 1 : y); index++) {
			if (min > best[x * width + index]) {
				min = best[x * width + index];
				(*path)[x] = index;
			}
		}
	}
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){
    int height_src = src->height;
    int width_src = src->width;
    create_img(dest, height_src, width_src - 1);
    for (int y = 0; y < height_src; y++) {
        for (int x = 0; x < width_src; x++) {
            if (x == path[y]){
                continue;
            }
            if (x > path[y]) {
                set_pixel(*dest, y, x - 1, get_pixel(src, y, x, 0), get_pixel(src, y, x, 1), get_pixel(src, y, x, 2));
            }
            else {  
                set_pixel(*dest, y, x, get_pixel(src, y, x, 0), get_pixel(src, y, x, 1), get_pixel(src, y, x, 2));
            }  
        }
    }
}