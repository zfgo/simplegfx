#include "simplegfx.h"

#define UNUSED __attribute__((unused))

const Simplegfx_canvas *simplegfx_create_canvas(int x_dim, int y_dim) {
    /*
     * Create an array of memory ("pixels") and fill each pixel with
     * different colors, etc. This library on creates this array of 
     * pixels (a "canvas") and it is up to the user to write that 
     * array to some file, etc.
     */
    Simplegfx_canvas canvas;
    uint32_t pixels[x_dim * y_dim];
    canvas.pixels = pixels;
    canvas.x_dim = x_dim;
    canvas.y_dim = y_dim;

    return &canvas;
} 
