#include <cairo/cairo.h>
#include <math.h>

static void draw(cairo_t *cr, int x, int w, int h, cairo_operator_t op)
{

    cairo_t *first_cr, *second_cr;
    cairo_surface_t *first, *second;

    first = cairo_surface_create_similar(cairo_get_target(cr),
            CAIRO_CONTENT_COLOR_ALPHA, w, h);

    second = cairo_surface_create_similar(cairo_get_target(cr),
            CAIRO_CONTENT_COLOR_ALPHA, w, h);

    first_cr = cairo_create(first);
    cairo_set_source_rgb(first_cr, 0, 0, 0.4);
    cairo_rectangle(first_cr, x, 20, 50, 50);
    cairo_fill(first_cr);

    second_cr = cairo_create(second);
    cairo_set_source_rgb(second_cr, 0.5, 0.5, 0);
    cairo_rectangle(second_cr, x+10, 40, 50, 50);
    cairo_fill(second_cr);

    cairo_set_operator(first_cr, op);
    cairo_set_source_surface(first_cr, second, 0, 0);
    cairo_paint(first_cr);

    cairo_set_source_surface(cr, first, 0, 0);
    cairo_paint(cr);

    cairo_surface_destroy(first);
    cairo_surface_destroy(second);

    cairo_destroy(first_cr);
    cairo_destroy(second_cr);
}

int main (int argc, char *argv[])
{
    int w=640, h=480;

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);
    cairo_t *cr = cairo_create (surface);

    int x, y;

    cairo_operator_t oper[] = {
        CAIRO_OPERATOR_DEST_OVER, 
        CAIRO_OPERATOR_DEST_IN, 
        CAIRO_OPERATOR_OUT,
        CAIRO_OPERATOR_ADD, 
        CAIRO_OPERATOR_ATOP,
        CAIRO_OPERATOR_DEST_ATOP,
    };

    int i;

    for(x=20, y=20, i=0; i < 6; x+=80, i++)
        draw(cr, x, w, h, oper[i] );

    cairo_destroy(cr);
    cairo_surface_write_to_png (surface, "cps.png");
    cairo_surface_destroy (surface);

    return 0;
}
