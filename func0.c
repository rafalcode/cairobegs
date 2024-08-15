#include <cairo/cairo.h>
#include <math.h>

#define LWID 10

typedef struct /*col_t colour type*/
{
    float r,g,b; // must be 0 to 1
} col_t;

typedef struct /*pos_t position type*/
{
    float x,y;
} pos_t;

void draw0(cairo_t *cr, pos_t *p1, pos_t *p2, col_t *col)
{
    cairo_set_source_rgb(cr, col->r, col->g, col->b);
    cairo_move_to (cr, p1->x, p1->y);
    cairo_line_to (cr, p2->x, p2->y);
    cairo_set_line_width (cr, LWID);
    cairo_close_path(cr);
    cairo_stroke (cr);
    return;
}

int main (int argc, char *argv[])
{
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 640, 480);
    cairo_t *cr = cairo_create (surface);

    pos_t p1= {.x=50, .y=50};
    pos_t p2= {.x=150, .y=50};
    col_t col={.r=.9, .g=.9, .b=.9};

    draw0(cr, &p1, &p2, &col);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "func0.png");
    cairo_surface_destroy (surface);

    return 0;
}
