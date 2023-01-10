#include <stdlib.h>
#include <stdio.h>
#include "simplegfx.h"

int main(void) {
    const Simplegfx_canvas *canvas = NULL;

    if ((canvas = Simplegfx_canvas_create(10,10)) == NULL) {
        printf("unable to make canvas\n");
    }
    canvas->fill_canvas(canvas, 255, 0, 0);
    canvas->write(canvas, "./tests/test.ppm");
    canvas->destroy(canvas);
    printf("Done.\n");
    return 0;
}
