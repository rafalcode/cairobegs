/* boxb, box border */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CW 640 // canvas width
#define CH 480 // canvas height

// there's an outer border ...
#define TMAR 50 // top maring ... usually this will be biggest
#define BMAR 20
#define LMAR 20
#define RMAR 20

// then the box itself has a Topmarg and leftmarg
#define BM 10 // box margin
#define BSZ 80 // essential box size without its borders.

// and an inner one!
#define ITM TMAR+BM+BSZ+BM
#define ILM LMAR+BM+BSZ+BM
#define LINEWID 4

#define HBARNUMS 12

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

    int tx = (CW-LMAR-RMAR-BM) / (BSZ+BM); // times xwise
    int txr = (CW-LMAR-RMAR-BM) % (BSZ+BM); // times xwise remainder
    printf("timesx %i timesremx %i\n", tx, txr); 
    int ty = (CH-TMAR-BMAR-BM) / (BSZ+BM); // times ywise
    int tyr = (CW-TMAR-RMAR-BM) % (BSZ+BM); // times xwise remainder
    printf("timesy %i timesremy %i\n", ty, tyr); 
    printf("So number of full boxes around perimter is actually %i\n", 2*tx+2*ty-4);

    int icw=tx*(BSZ+BM)+BM;
    int ich=ty*(BSZ+BM)+BM;

    // cairo_rectangle (cr, LMAR+txr/2, TMAR+tyr/2, CW-LMAR-RMAR-txr, CH-TMAR-BMAR-tyr-BM-BM);
    // cairo_rectangle (cr, LMAR+txr/2, TMAR+tyr/2, CW-LMAR-RMAR-txr, CH-TMAR-BMAR-tyr);
    cairo_rectangle (cr, LMAR+txr/2, TMAR+tyr/2, icw, ich);
    cairo_set_source_rgb(cr, 0.1, .1, .4);
    cairo_fill (cr);


    // and the inner one which will remain clear.
    cairo_rectangle(cr, ILM+txr/2, ITM+tyr/2, (tx-2)*(BSZ+BM)-BM, (ty-2)*(BSZ+BM)-BM);
    cairo_set_source_rgb(cr, 0.2, .2, .2);
    cairo_fill (cr);

    // now the drawable

    pos_t *st=malloc((2*tx+2*ty-4)*sizeof(pos_t));
    st[0].x=LMAR+txr/2+BM;
    st[0].y=TMAR+tyr/2+BM;
    // from top left to top right
    for(i=1;i<tx;++i) {
        st[i].x=st[i-1].x + BSZ + BM;
        st[i].y=st[0].y;
    }
    // down from top right to bottom right
    for(i=tx;i<tx+ty-1;++i) {
        st[i].x=st[i-1].x;
        st[i].y=st[i-1].y + BSZ + BM;
    }
    // leftwise from bottom right
    for(i=tx+ty-1;i<2*tx+ty-2;++i) {
        st[i].x=st[i-1].x - BSZ - BM;
        st[i].y=st[tx+ty-2].y;
    }
    // from bottom left to top left.
    for(i=2*tx+ty-2;i<2*tx+2*ty-4;++i) {
        st[i].x=st[2*tx+ty-3].x;
        st[i].y=st[i-1].y - BSZ - BM;
    }

    for(i=0;i<2*tx+2*ty-4;++i) 
        cairo_rectangle (cr, st[i].x, st[i].y, BSZ, BSZ);
    cairo_set_source_rgb(cr, .6, .6, 0);
    cairo_fill (cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "boxb.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(st);

    return 0;
}
