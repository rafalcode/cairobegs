/* An upper left triangular set of boxes on a png image
 * looks like a preparation for Pair-Wise analyses */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CW 800 // canvas width
#define CH 600 // canvas height

// Subject to the following MARs (margins) we have a "drawable".
#define TMAR 50
#define BMAR 10
#define LMAR 10
#define RMAR 10

// we divide our "drawable" into horizontal bars each of which sets the vertical position of a box, and vertical bars which sets the hoizontal position.
#define HBARNUMS 4
#define VBARNUMS 4

typedef struct /* pos_t */
{
    float x, y;
} pos_t;

int main (int argc, char *argv[])
{
    int i, j;

    // we start with the canvas. Set up surface, set bg etc.
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, CW, CH);
    cairo_t *cr = cairo_create (surface);
    cairo_rectangle (cr, 0, 0, CW, CH);
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    // now the drawable
    pos_t dtl;
    dtl.x=LMAR; // dtl: drawable top left
    dtl.y=TMAR;
    float dw=CW-LMAR-RMAR; // drawable width extent
    float dh=CH-TMAR-BMAR; // drawable height extent
                           //
    /* vertical divider how ar ewe going to section off the screen vertically */
    float vbarsz=dw/VBARNUMS; // size of steps in x direction
    float hbarsz=dh/HBARNUMS; // y direction.
    int totpoints = HBARNUMS*VBARNUMS;
    pos_t *lb=calloc(totpoints, sizeof(pos_t)); /* ori: origin, lb, last bar, */

    // first point, top left
    lb[0].x= dtl.x;
    lb[0].y = dtl.y;
    // first row, only x changes
    for(i=1;i<VBARNUMS;i++) {
        lb[i].x= lb[i-1].x + vbarsz;
        lb[i].y= lb[i-1].y;
    }
    // first column
    for(i=1;i<HBARNUMS;i++) {
        lb[i*VBARNUMS].x= lb[(i-1)*VBARNUMS].x;
        lb[i*VBARNUMS].y= lb[(i-1)*VBARNUMS].y + hbarsz;
    }

    for(i=1;i<HBARNUMS;i++)
        for(j=1;j<VBARNUMS;j++) {
            lb[i*VBARNUMS+j].x= lb[i*VBARNUMS+j-1].x + vbarsz;
            lb[i*VBARNUMS+j].y= lb[i*VBARNUMS+j-1].y;
        }

    int im; // mod i, for changing colours.
    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    for(i=0;i<VBARNUMS;i++) {
        for(j=0;j<HBARNUMS-i;j++) {
            im = (i*VBARNUMS+j)%3;
            switch(im) {
                case 0:
                    cairo_set_source_rgb(cr, 0.65, 0.8, 0.45); break;
                case 1:
                    cairo_set_source_rgb(cr, 0.15, 0.45, 0.6); break;
                case 2:
                    cairo_set_source_rgb(cr, 0.35, 0.2, 0.6);
            }
            printf("%4.4f %4.4f\n", lb[i*VBARNUMS+j].x, lb[i*VBARNUMS+j].y);
            cairo_rectangle(cr, lb[i*VBARNUMS+j].x, lb[i*VBARNUMS+j].y, vbarsz, hbarsz);
            cairo_fill(cr);
        }
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "upleftb.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(lb);

    return 0;
}
