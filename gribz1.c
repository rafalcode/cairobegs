/* uses gri0.c from cairims to repupose grid code trndot.c ibut to do to do a simple grid */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define HBARNUMS 3
#define VBARNUMS 9

typedef struct
{
    float x, y;
} pos_t;

int main (int argc, char *argv[])
{
    int i, j, width=640, height=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* vertical divider how ar ewe going to section off the screen vertically */
    float vbarsz=(float)width/VBARNUMS; // size of steps in x direction
    float hbarsz=(float)height/HBARNUMS; // y direction.
    int totpoints = HBARNUMS*VBARNUMS;
    pos_t *lb=calloc(totpoints, sizeof(pos_t)); /* ori: origin, lb, last bar, */

    // first point, top left
    lb[0].x= vbarsz/2.;
    lb[0].y = hbarsz/2.;
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

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    for(i=0;i<totpoints;i++){
        // printf("%4.4f %4.4f\n", lb[i].x, lb[i].y);
        cairo_arc(cr, lb[i].x, lb[i].y, 2, 0, 2 * M_PI);
        cairo_fill(cr);

        // cairo_move_to(cr,ori.h,ori.v);
        // cairo_line_to(cr,lb[i].h, lb[i].v);
        cairo_stroke(cr);
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "gribz1.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(lb);

    return 0;
}
