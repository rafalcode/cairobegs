/* this will take a round clip of a png file */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int width=640, height=480;
    cairo_surface_t surface = cairo_pdf_surface_create ("teiest.pdf", width, height);
    cairo_t *cr = cairo_create (surface);

    cairo_surface_t *image = cairo_image_surface_create_from_png("gish.png");

    static int pos_x = 128;
    static int pos_y = 128;
    int radius = 40;  

    static int delta[] = { 3, 3 };

    /* make sure there is enough left and right margin for our clipshape */
    if (pos_x < 0 + radius) {
        delta[0] = rand() % 4 + 5;
    } else if (pos_x > width - radius) {
        delta[0] = -(rand() % 4 + 5);
    }
    /* make sure there is enough top and bottom margin for our clipshape */
    if (pos_y < 0 + radius) {
        delta[1] = rand() % 4 + 5;
    } else if (pos_y > height - radius) {
        delta[1] = -(rand() % 4 + 5);
    }
    pos_x += delta[0];
    pos_y += delta[1];

    cairo_set_source_surface(cr, image, 1, 1);
    cairo_arc(cr, pos_x, pos_y, radius, 0, 2*M_PI);
    cairo_clip(cr);
    cairo_paint(cr);

    cairo_destroy(cr);
    cairo_surface_destroy (surface);
    cairo_surface_destroy (image);

    return 0;
}
