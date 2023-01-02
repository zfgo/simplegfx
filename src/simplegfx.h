#ifndef SIMPLEGFX_H_
#define SIMPLEGFX_H_

#include <stdbool.h>

struct pixel {
    uint32_t color;
};

struct canvas_data {
    int x_dim;
    int y_dim;
    struct pixel **canvas;
};

bool simplegfx_create_img(int x_dim, int y_dim);

#endif /* SIMPLEGFX_H_ */
