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
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (i % 2 && !(j % 2))
                canvas->draw_rectangle(canvas, (100 / 12) * i, (100 / 12) * i + 6, (100 / 12) * j, (100 / 12) * j + 6, 0, 255, 0, 255); 
        }
    }

    canvas->write(canvas, "./tests/test.ppm");
    canvas->destroy(canvas);
    printf("Done.\n");
    return 0;
}
