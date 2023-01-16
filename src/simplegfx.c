#include "simplegfx.h"
#include <stdlib.h>
#include <stdio.h>

#define UNUSED __attribute__((unused))
#define MAX_COLOR_VALUE 255

typedef struct pixel Pixel; // forward reference

typedef struct canvas_data {
    int width;
    int height;
    Pixel **data;
} Canvas_data;

struct pixel {
    unsigned char color[4]; // rgba
};

/* local function - traverse through pixels, freeing the rows
 */
static void purge_pixels(Canvas_data *c_data) {
    for (int i = 0; i < c_data->width; ++i) {
        free(c_data->data[i]);
    }
}

static void simplegfx_canvas_destroy(const Simplegfx_canvas *canvas) {
    Canvas_data *c_data = (Canvas_data *)canvas->self;
    
    purge_pixels(c_data);
    free(c_data->data);
    free(c_data);
    free((void *)canvas);
}

static bool simplegfx_write(const Simplegfx_canvas *canvas, char *file_name) {
    Canvas_data *c_data = (Canvas_data *)canvas->self;
    FILE *fp;
    int i, j;

    if ((fp = fopen(file_name, "wb")) ==  NULL) { /* wb : write binary" */
        fprintf(stderr, "Error: failed to open file.\n");
        return false;
    }

    (void)fprintf(fp, "P6\n%d %d\n%d\n", c_data->width, c_data->height, MAX_COLOR_VALUE);
    
    for (i = 0; i < c_data->width; ++i) {
        for (j = 0; j < c_data->height; ++j) {
            (void)fwrite(c_data->data[i][j].color, 1, 3, fp);
        }
    }

    (void) fclose(fp);

    return true;
}

static void simplegfx_fill_canvas(const Simplegfx_canvas *canvas, 
                                  unsigned char r, unsigned char g, 
                                  unsigned char b, unsigned char alpha) {
    Canvas_data *c_data = (Canvas_data *)canvas->self;
    int i, j;

    /* set all pixels in canvas to color */
    for (i = 0; i < c_data->width; ++i) {
        for (j = 0; j < c_data->height; ++j) {
            c_data->data[i][j].color[0] = r;
            c_data->data[i][j].color[1] = g;
            c_data->data[i][j].color[2] = b;
            c_data->data[i][j].color[3] = alpha;
        }
    }
}

static void simplegfx_assign_pixel(const Simplegfx_canvas *canvas, int i, int j,
                                   unsigned char r, unsigned char g, 
                                   unsigned char b, unsigned char alpha) {
    Canvas_data *c_data = (Canvas_data *)canvas->self;

    // check that i and j are within the canvas borders
    if (i >= c_data->height || i < 0 || j >= c_data->width || j < 0) {
        #if DEBUG
            fprintf(stderr, "Error: can not assign pixel out of range.\n");
        #endif
        return;
    }

    c_data->data[i][j].color[0] = r;
    c_data->data[i][j].color[1] = g;
    c_data->data[i][j].color[2] = b;
    c_data->data[i][j].color[3] = alpha;
}

static const Simplegfx_canvas *simplegfx_canvas_create(int width, int height); // forward reference

static Simplegfx_canvas template = {
    NULL, 
    //simplegfx_canvas_create, 
    simplegfx_canvas_destroy,
    simplegfx_write,
    simplegfx_fill_canvas,
    simplegfx_assign_pixel
};

static const Simplegfx_canvas *simplegfx_canvas_create(int width, int height) {
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
            int x_dim, y_dim, i;
            Pixel **data;

            x_dim = (width <= 0) ? DEFAULT_DIM : width;
            y_dim = (height <= 0) ? DEFAULT_DIM : height;

            if ((data = (Pixel **)malloc(sizeof(Pixel *) * x_dim)) != NULL) {
                for (i = 0; i < x_dim; ++i) {
                    if ((data[i] = (Pixel *)malloc(sizeof(Pixel) * y_dim)) == NULL) {
                        // TODO: check for malloc errors
                    }
                }
                
                // now we can set all of our private data
                c_data->width = x_dim;
                c_data->height = y_dim;
                c_data->data = data;

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
