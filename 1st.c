/* CPROG Filename:  1st.c
 * Description: A first Cairo Test
 *
 * This is taken from cairo's FAQ. It's the simplest program.
 * 
 * Created:  02/25/2010 03:15:11 PM
 * Revision:  none
 * Compiler:  gcc
 *
 * Author:  YOUR NAME (), 
 * Company:   */
#include <cairo/cairo.h>

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 240, 80);

    /*  then a cario_type is created from this surface */
    cairo_t *cr = cairo_create (surface);

    /*  fonts ... unsure how these are selected */
    cairo_select_font_face (cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 32.0);
    cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
    cairo_move_to (cr, 10.0, 50.0);
    /*  the showing of text is the terminology for the  */
    cairo_show_text (cr, "Hello, world");
    /* We're finished this soon cos this is only a simple exercise */
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "hello.png");
    cairo_surface_destroy (surface);
    return 0;
}

/*  Compile normally, adding -lcairo at the end. */
