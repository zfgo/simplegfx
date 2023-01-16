#include <stdlib.h>
#include <stdio.h>
#include "simplegfx.h"

int main(void) {
    const Simplegfx_canvas *canvas = NULL;

    if ((canvas = Simplegfx_canvas_create(100,100)) == NULL) {
        printf("unable to make canvas\n");
    }
    canvas->fill_canvas(canvas, 255, 0, 0, 125);
    canvas->assign_pixel(canvas, 1, 1, 0, 0, 0, 255);
    canvas->write(canvas, "./tests/test.ppm");
    canvas->destroy(canvas);
    printf("Done.\n");
    return 0;
}
