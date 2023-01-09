#ifndef SIMPLEGFX_H_
#define SIMPLEGFX_H_

#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#define DEFAULT_DIM 1000


typedef struct simplegfx_canvas Simplegfx_canvas;


struct simplegfx_canvas {
    /* The private data of the canvas 
     */
    void *self;
    
    /* create a new canvas
     */
    const Simplegfx_canvas *(*create)(const Simplegfx_canvas *canvas, int x_dim, int y_dim);

    /* destroy the canvas
     */
    void (*destroy)(const Simplegfx_canvas *canvas);
};


#endif /* SIMPLEGFX_H_ */
