/* simplest experiment to divide a screen out and draw lines */
#include <string.h>
#include <cairo/cairo.h>

#define VBARNUMS 6
#define HBARNUMS 6

void creatx(cairo_t *cr, char *alphabet, int im_w, int im_h)
{
    cairo_select_font_face (cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, 14.0);

    cairo_font_extents_t fe;
    cairo_text_extents_t te;
    char letter[2]; /* this will be where we put our individual characters, with the null char to mark them out */

    cairo_font_extents (cr, &fe);

    int i;

    for (i=0; i < strlen(alphabet); i++) {
        *letter = '\0';
        strncat (letter, alphabet + i, 1);

        cairo_text_extents (cr, letter, &te);
        cairo_move_to (cr, i*15 + im_w/2-90 - te.x_bearing - te.width / 2, im_h/2 - fe.descent + fe.height / 2);
        cairo_show_text (cr, letter);
    }
}

int main (int argc, char *argv[])
{
    int i, im_w=480, im_h=480;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, im_w, im_h);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, im_w, im_h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* use the scale command to normalise all subsequent dimensions */
    // cairo_scale (cr, 240, 240);
    /* vertical divider how ar ewe going to section off the screen vertically */
    int vbar=im_h/VBARNUMS;
    int vpos[VBARNUMS];
    /* arrange array of positions */
    vpos[0]=vbar/2;
    for(i=1;i<VBARNUMS;i++)
        vpos[i] = vpos[i-1] + vbar;


    /* Drawing code goes here */
    cairo_set_line_width (cr, 4);
    cairo_set_source_rgba(cr, 0.25, 0.8, 0.25, 0.6);
    for(i=0;i<VBARNUMS;i++) {
        cairo_move_to(cr, im_w/2 -50, vpos[i]);
        cairo_line_to(cr, im_w/2 +50, vpos[i]);
        cairo_stroke (cr);
    }
    /*  we want some text now. We have a function, but actually to set color
     *  we need to set color for the whole "cr"  */
    cairo_set_source_rgba (cr, 0.7, 0.6, 0.75, 0.8);
    // creatx(cr, "¡Tómatelo con calma, Iñigo!", im_w, im_h); // gave no text ... it was unable to deal with the encoding
    creatx(cr, "Too lame for a dame", im_w, im_h);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "lines.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}
