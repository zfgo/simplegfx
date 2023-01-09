#include "simplegfx.h"
#include <stdlib.h>

#define UNUSED __attribute__((unused))

typedef struct canvas_data {
    int x_dim;
    int y_dim;
    uint32_t **pixels;
} Canvas_data;


static void simplegfx_canvas_destroy(const Simplegfx_canvas *canvas) {
    // TODO
    return;
}

static const Simplegfx_canvas *simplegfx_canvas_create(const Simplegfx_canvas *canvas);

static Simplegfx_canvas template = {
    NULL, simplegfx_canvas_create, simplegfx_canvas_destroy
};

static const Simplegfx_canvas *simplegfx_new_canvas(int x_dimension, int y_dimension) {
    /*
     * Create an array of memory ("pixels") and fill each pixel with
     * different colors, etc. This library on creates this array of 
     * pixels (a "canvas") and it is up to the user to write that 
     * array to some file, etc.
     */
    Simplegfx_canvas *canvas = (Simplegfx_canvas *)malloc(sizeof(Simplegfx_canvas));

    if (canvas != NULL) {
        Canvas_data *c_data = (Canvas_data *)malloc(sizeof(Canvas_data));

        if (c_data != NULL) {
            int x_dim, y_dim;
            uint32_t **pixels;

            x_dim = (x_dim <= 0) ? DEFAULT_DIM : x_dimension;
            y_dim = (y_dim <= 0) ? DEFAULT_DIM : y_dimension;

            pixels = (uint32_t **)malloc(sizeof(uint32_t *) * x_dim);
            if (pixels != NULL) {
                for (int i = 0; i < x_dim; ++i) {
                    pixels[i] = (uint32_t *)malloc(sizeof(uint32_t) * y_dim);
                    // TODO: check for malloc errors
                }
                
                // now we can set all of our private data
                c_data->x_dim = x_dim;
                c_data->y_dim = y_dim;
                c_data->pixels = pixels;

                *canvas = template;
                canvas->self = c_data;

            } else {
                free(c_data);
                free(canvas);
                canvas = NULL;
            }
        } else {
            free(canvas);
            canvas = NULL;
        }
    }
    return canvas;
} 

static const *Simplegfx_canvas_create( // TODO TODO TODO
