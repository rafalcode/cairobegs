#include <cairo/cairo.h>
#include <string.h>
#include <math.h>

int main (int argc, char *argv[])
{
    /* First declare a cairo surface */
    int w=740, h=180;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);

    /*  then a cario_type is created from this surface */
    cairo_t *cr = cairo_create (surface);
    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, w, h); 
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95);
    cairo_fill (cr);

    cairo_select_font_face (cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, 30.0);

    cairo_font_extents_t fe;
    cairo_text_extents_t te;
    char alphabet[] = "AbCdEfGhIjKiliMnOpQrStUv";
    char letter[2];

    cairo_font_extents (cr, &fe);

    int i;

    for (i=0; i < strlen(alphabet); i++) {
        *letter = '\0';
        strncat (letter, alphabet + i, 1);

        cairo_text_extents (cr, letter, &te);
        cairo_move_to (cr, i*20 + 45 - te.x_bearing - te.width / 2, 25 - fe.descent + fe.height / 2);
        cairo_show_text (cr, letter);
    }

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "t2.png");
    cairo_surface_destroy (surface);
    return 0;
}
