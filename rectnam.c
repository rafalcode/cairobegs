/* a more advanced version of image block example */

#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* now the principle canvas definition settings, which is the image dimensions minus the margins
 * follows vim direction conventions*/
#define IMLMARG 20 /* left margin */
#define IMBMARG 10 /* bottom */
#define IMRMARG 30
#define IMTMARG 40

/* principal image and block settings */
#define IMWIDTH 1920
#define IMHEIGHT 1080
#define CBNUM 4 /* number of column bands */
#define RBNUM CBNUM /* number of row-bands */

/* derived settings */
#define CBSZ IMWIDTH/CBNUM /* size of each column-band */
#define RBSZ IMHEIGHT/RBNUM /* size of each row-band */

/* Margins of each block */
#define BKLMARG 4 /* left margin */
#define BKBMARG 4 /* bottom */
#define BKRMARG 4
#define BKTMARG 4

#define NAMBUF 32 /* string buffer for color names */
#define CS_SZ 18 /* the size (number of colours) that our colorscheme has */

typedef struct {
    char nam[NAMBUF];
    int rgb[3];
} colstru_i;

typedef struct {
    char nam[NAMBUF];
    float rgb[3];
} colstru_f;


colstru_f *norfloatify(colstru_i *schcol)
{
    /*  set up the struct we're going to return .. as a pointer: important to assign memory */
    colstru_f *colsf;
    colsf = malloc(sizeof(colstru_f));
    strncpy( colsf->nam, schcol->nam, NAMBUF);
    colsf->rgb[0] = (float)schcol->rgb[0]/255.0;
    colsf->rgb[1] = (float)schcol->rgb[1]/255.0;
    colsf->rgb[2] = (float)schcol->rgb[2]/255.0;
    return colsf;
}

int main (int argc, char *argv[])
{
    /*  first we intriduce our 18 colr scheme taken from an .Xdefaults file */
    colstru_i scheme[CS_SZ] = { {"foreground", {0xdd, 0xdd, 0xdd} }, {"background", {0x11, 0x11, 0x11} }, {"color0", {0x19, 0x19, 0x19} }, {"color8", {0xa0, 0x52, 0x2d} }, {"color1", {0x80, 0x32, 0x32} }, {"color9", {0x98, 0x2b, 0x2b} }, {"color2", {0x5b, 0x76, 0x2f} }, {"color10", {0x89, 0xb8, 0x3f} }, {"color3", {0xaa, 0x99, 0x43} }, {"color11", {0xef, 0xef, 0x60} }, {"color4", {0x32, 0x4c, 0x80} }, {"color12", {0x2b, 0x4f, 0x98} }, {"color5", {0x70, 0x6c, 0x9a} }, {"color13", {0x82, 0x6a, 0xb1} }, {"color6", {0x92, 0xb1, 0x9e} }, {"color14", {0xa1, 0xcd, 0xcd} }, {"color7", {0xff, 0xff, 0xff} }, {"color15", {0xdd, 0xdd, 0xdd} } };
    colstru_f *colsf;
    /* now main program business */
    cairo_surface_t *surface;
    cairo_t *cr;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMWIDTH, IMHEIGHT);
    cr = cairo_create (surface);
    /* First we set our general background */
    cairo_rectangle (cr, 0, 0, IMWIDTH, IMHEIGHT); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* OK, now, text consideration */
    cairo_select_font_face (cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, 24.0);
    cairo_font_extents_t fe;
    cairo_text_extents_t te;

    int i, j, k;
    for (i=0; i<RBNUM; i++)
        for (j=0; j<CBNUM; j++) { /* i and j serve as our block indices */
            k=CBNUM*i+j+2;
            colsf = norfloatify(scheme+k);

            cairo_set_source_rgb(cr, colsf->rgb[0], colsf->rgb[1], colsf->rgb[2]);
            cairo_rectangle (cr, CBSZ*j+BKLMARG, RBSZ*i+BKTMARG, CBSZ-BKLMARG-BKRMARG, RBSZ-BKTMARG-BKBMARG);
            cairo_fill (cr);
            /*  text section */
            cairo_text_extents (cr, colsf->nam, &te);
            cairo_move_to (cr, (CBSZ*j+CBSZ/2) - te.x_bearing - te.width/2, (RBSZ*i + RBSZ/2) - fe.descent + fe.height/2);
            cairo_set_source_rgb(cr, 0.3, 0.2, .2);
            cairo_show_text (cr, colsf->nam);
            free(colsf);
        }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "rectnam.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}
