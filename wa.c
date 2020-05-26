/*  Very, very rough text handling in Cairo */
#include <cairo/cairo.h>
#include <math.h>

int main (int argc, char *argv[])
{
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 640, 480);
    cairo_t *cr = cairo_create (surface);

    cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 

    /*  this Purisa Font is something zetcode has */
    cairo_select_font_face(cr, "Purisa", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_font_size(cr, 13);

    cairo_move_to(cr, 20, 30);
    cairo_show_text(cr, "Most relationships seem so transitory");  
    cairo_move_to(cr, 20, 60);
    cairo_show_text(cr, "They're all good but not the permanent one");

    cairo_move_to(cr, 20, 120);
    cairo_show_text(cr, "Who doesn't long for someone to hold");

    cairo_move_to(cr, 20, 150);
    cairo_show_text(cr, "Who knows how to love you without being told");
    cairo_move_to(cr, 20, 180);
    cairo_show_text(cr, "Somebody tell me why I'm on my own");
    cairo_move_to(cr, 20, 210);
    cairo_show_text(cr, "If there's a soulmate for everyone");

    cairo_destroy(cr);
    cairo_surface_write_to_png (surface, "bed.png");
    cairo_surface_destroy (surface);

    return 0;
}

