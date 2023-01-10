#include "simplegfx.h"
#include <stdlib.h>
#include <stdio.h>

#define UNUSED __attribute__((unused))

typedef struct canvas_data {
    int x_dim;
    int y_dim;
    uint32_t **pixels;
} Canvas_data;

/* local function - traverse through pixels, freeing the rows
 */
static void purge_pixels(Canvas_data *c_data) {
    for (int i = 0; i < c_data->x_dim; ++i) {
        free(c_data->pixels[i]);
    }
}


static void simplegfx_canvas_destroy(const Simplegfx_canvas *canvas) {
    Canvas_data *c_data = (Canvas_data *)canvas->self;
    
    purge_pixels(c_data);
    free(c_data->pixels);
    free(c_data);
    free((void *)canvas);
}

static bool simplegfx_write(const Simplegfx_canvas *canvas, char *file_name) {
    Canvas_data *c_data = (Canvas_data *)canvas->self;
    int i, j;

    FILE *fp = fopen(file_name, "wb"); /* wb - write binary mode */
    if (fp == NULL) {
        return false;
    }
    (void )fprintf(fp, "P6\n%d %d\n255\n", c_data->x_dim, c_data->y_dim);

    for (i = 0; i < c_data->x_dim; ++i) {
        for (j = 0; j < c_data->y_dim; ++j) {
            (void) fwrite(&c_data->pixels[i][j], 4, 1, fp);
        }
    }

    (void) fclose(fp);

    return true;
}

static const Simplegfx_canvas *simplegfx_canvas_create(int x_dimension, int y_dimension);

static Simplegfx_canvas template = {
    NULL, 
    //simplegfx_canvas_create, 
    simplegfx_canvas_destroy,
    simplegfx_write
};

static const Simplegfx_canvas *simplegfx_canvas_create(int x_dimension, int y_dimension) {
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

            x_dim = (x_dimension <= 0) ? DEFAULT_DIM : x_dimension;
            y_dim = (y_dimension <= 0) ? DEFAULT_DIM : y_dimension;

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


const Simplegfx_canvas *Simplegfx_canvas_create(int x_dim, int y_dim) {
    return simplegfx_canvas_create(x_dim, y_dim);
}
