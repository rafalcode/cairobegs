/* this will take a round clip of a png file */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    int width=640, height=480;
    /*  s1 our working surface, this is the blank sheet that we start with */
    cairo_surface_t *s1 = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);

    /* But the manipulation will take place on a context, so we need to get a context from the new surface */
    cairo_t *ctx_s1 = cairo_create(s1);

    cairo_rectangle (ctx_s1, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (ctx_s1, 0.5, 0.2, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (ctx_s1);

    cairo_surface_t *s2 = cairo_image_surface_create_from_png("gish.png");
    /*  we load the ctx with all this surface, at pt. ix,iy of the context */
    int ix= 100, iy = 78;
    cairo_set_source_surface(ctx_s1, s2, ix, iy);
    int pngw=cairo_image_surface_get_width(s2);
    int pngh=cairo_image_surface_get_height(s2);
    printf("pngimage is %i wide, %i, high.\n", pngw, pngh); 

    /*  we actually have finished */
    cairo_surface_destroy (s2);

    cairo_format_t caif;
    caif = cairo_image_surface_get_format (s2);
    printf("caif enum is %i\n",caif); 

    int pos_x = 128;
    int pos_y = 128;
    int radius = 50;  

    static int delta[] = { 3, 3 };

    /* make sure there is enough left and right margin for our clipshape */
    if (pos_x < 0 + radius)
        delta[0] = rand() % 4 + 5;
    else if (pos_x > width - radius)
        delta[0] = -(rand() % 4 + 5);

    /* make sure there is enough top and bottom margin for our clipshape */
    if (pos_y < 0 + radius)
        delta[1] = rand() % 4 + 5;
    else if (pos_y > height - radius)
        delta[1] = -(rand() % 4 + 5);

    pos_x += delta[0];
    pos_y += delta[1];

    /* we take our context */
    cairo_arc(ctx_s1, pos_x, pos_y, radius, 0, 2*M_PI);
    cairo_clip(ctx_s1);
    cairo_paint(ctx_s1);



//     /* OK, let's go again */
//     cairo_surface_t *s2 = cairo_image_surface_create_from_png("gish.png");
//     cairo_set_source_surface(ctx_s1, s2, 1, 1);
//     int pos_x = 128;
//     int pos_y = 128;
//     int radius = 40;  
// 


    cairo_destroy(ctx_s1);
    cairo_surface_write_to_png (s1, "cl2.png");
    cairo_surface_destroy (s1);

    return 0;
}
