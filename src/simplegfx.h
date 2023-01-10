#ifndef SIMPLEGFX_H_
#define SIMPLEGFX_H_

/* interface definition for the simplegfx graphics library
 *
 * patterned roughly after Joseph Sventek's data structures as seen in
 * "C and Data Structures"
 */
#include <stdbool.h>
#include <stdint.h>                         /* needed for uint32_t */

#define DEFAULT_DIM 1000                    /* set default dimensions */


typedef struct simplegfx_canvas Simplegfx_canvas;   /* forward reference */

/* Create canvas function
 */
const Simplegfx_canvas *Simplegfx_canvas_create(int x_dimension, int y_dimension);

struct simplegfx_canvas {
    /* The private data of the canvas 
     */
    void *self;
    
    /* create a new canvas
     */
    //const Simplegfx_canvas *(*create)(int x_dimension, int y_dimension);

    /* destroy the canvas
     */
    void (*destroy)(const Simplegfx_canvas *canvas);

    /* write the canvas to a .ppm file
     */
    bool (*write)(const Simplegfx_canvas *canvas, char *file_name);
};

#endif /* SIMPLEGFX_H_ */
