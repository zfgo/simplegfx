#include <stdlib.h>
#include <stdio.h>
#include "simplegfx.h"

int main(void) {
    const Simplegfx_canvas *canvas;

    canvas->create(10,10);

    printf("Done.\n");
    return 0;
}
