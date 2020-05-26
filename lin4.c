/* simplest experiment to divide a screen out and draw lines */
#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VBARNUMS 6
#define HBARNUMS 6
#define CNAML 32 /*  colour name length */

typedef struct {
    char nam[CNAML];
    int c[3];
} ctri; /*  our colour triplet together with name */

typedef struct {
    char nam[CNAML];
    float c[3];
} ctrif; /*  our colour triplet together with name */

void c2f(ctri *in, ctrif *out)
{
    int i;
    memcpy(out->nam, in->nam, CNAML);
    for(i=0;i<3;++i) {
        if(in->c[i] == 0)
            out->c[i] = 0.0;
        else
            out->c[i] = in->c[i]/255.0;
    }
}

int main (int argc, char *argv[])
{
    int i, width=480, height=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    ctri cdna[4] = { { "A_blue", {69, 56, 239}}, { "C_green", {0, 121, 7}}, { "G_red", {229, 63, 61}}, { "T_yellow", {254, 242, 0}} };
    ctrif *cdnaf;
    cdnaf=malloc(sizeof(ctrif)*4);
    for(i=0;i<4;++i) {
        c2f(cdna+i, cdnaf+i);
        printf("%s %3.4f %3.4f %3.4f\n",cdnaf[i].nam, cdnaf[i].c[0], cdnaf[i].c[1], cdnaf[i].c[2]); 
    }
    /* vertical divider how ar ewe going to section off the screen vertically */
    int vbar=height/VBARNUMS;
    int vpos[VBARNUMS];
    /* arrange array of positions */
    vpos[0]=vbar/2;
    for(i=1;i<VBARNUMS;i++)
        vpos[i] = vpos[i-1] + vbar;


    /* Drawing code goes here */
    cairo_set_line_width (cr, 4);
    int racol;
    srand(5);
    for(i=0;i<VBARNUMS;i++) {
        racol=rand()%4;
        printf("%i \n",racol); 
        cairo_set_source_rgba(cr, cdnaf[racol].c[0], cdnaf[racol].c[1], cdnaf[racol].c[2], 0.8);
        //    cairo_set_source_rgba(cr, 0.1+(0.2*(float)i), 0.8, 0.25, 0.6);
        cairo_move_to(cr, width/8 +(i*10), 220);
        cairo_line_to(cr, width/8 +((i+1)*10), 220);
        cairo_stroke (cr);
//        cairo_new_path(cr);
    }


    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "lines.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}
