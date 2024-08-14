/* timestr stands for time stripsfr for frams */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define IW 640 // image/canvas width
#define IH 480 // height
#define LMAR 40
#define RMAR 40
#define TMAR 20
#define BMAR 20

#define RSEED 34 // 34 got "chip off the old block"
#define NTPTS 6

#define LINEWID 2. // can't have .5 of this go over margins, then whole frame will overflow

typedef struct /* dpt_t: drawable point type */
{
    float x1, y1, x2, y2;
} dpt_t; 

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IW, IH);

    /*  then a cairo_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    /* now set background of he canvas */
    cairo_rectangle (cr, 0, 0, IW, IH); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba(cr, .15, .15, .15, 1); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    int i, j;

    /* our drawable are is smaller than canvas as define by the MAR values (i.e. margins) */
    float x1=LMAR;
    float y1=TMAR;
    float xspace=IW-LMAR-RMAR; // drawable space x-wise
    float x2=LMAR+xspace; // right most point in drawable
    float yspace=IH-TMAR-BMAR; // drawable space y-wise
    float y2=TMAR+yspace/2.; // lowest point

    // lets; invents some time point
    int tpta[NTPTS]={12, 145, 1080, 1123, 3050, 3600}; // cumnulative.

    int *xbarsza=calloc(NTPTS-1, sizeof(int));
    for(i=0;i<NTPTS-1;++i) 
        xbarsza[i]=tpta[i+1]-tpta[i];

    int ext=tpta[NTPTS-1] - tpta[0];
    printf("%i\n", ext); 
    printf("%2.2f\n", xspace/ext); 
    float n2d= xspace/ext; 
    // for(i=0;i<NTPTS-1;++i) {
    //     printf("%2.2f\n", xbarsza[i]*xspace/ext); 
    //     xspa[i]=xbarsza[i]*xspace/ext; 
    // }
    float *xspa=calloc(NTPTS, sizeof(float));
    xspa[0]=LMAR;
    xspa[NTPTS-1]=LMAR+xspace;
    for(i=1;i<NTPTS-1;++i)
        xspa[i]=tpta[i]*n2d;

    for(i=0;i<NTPTS;++i)
        printf("%2.2f\n", xspa[i]);

    cairo_set_line_width (cr, LINEWID);
    cairo_move_to(cr, xspa[0], y1);
    cairo_line_to(cr, xspa[0], y2);
    for(i=0;i<NTPTS-1;++i) {
        cairo_move_to(cr, xspa[i], y1);
        cairo_line_to(cr, xspa[i+1], y1);
        cairo_line_to(cr, xspa[i+1], y2);
        cairo_line_to(cr, xspa[i], y2);
        cairo_close_path(cr);
        cairo_set_source_rgb (cr, 0, 0, 0);
        cairo_stroke_preserve(cr);
        if(i%2==0)
            cairo_set_source_rgb (cr, .8, .6, .4);
        else
            cairo_set_source_rgb (cr, .4, .6, .8);
        cairo_fill(cr);
    }


    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "timstr0.png");
    cairo_surface_destroy (surface);
    free(xspa);
    return 0;
}
