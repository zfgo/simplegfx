#ifndef SIMPLEGFX_H_
#define SIMPLEGFX_H_

#include <stdbool.h>
#include <stdint.h>


typedef struct simplegfx_canvas {
    int x_dim;
    int y_dim;
    uint32_t *pixels;
} Simplegfx_canvas;

const Simplegfx_canvas simplegfx_create_canvas(int x_dim, int y_dim);

#endif /* SIMPLEGFX_H_ */
