#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/*  Somme 16 element colors schemes I pulled off the web */
int cs1[16][3] = { {0x33, 0x66, 0xFF}, {0x66, 0x33, 0xFF}, {0xCC, 0x33, 0xFF}, {0xFF, 0x33, 0xCC}, {0xFF, 0x33, 0x66}, {0xFF, 0x66, 0x33}, {0xFF, 0xCC, 0x33}, {0xCC, 0xFF, 0x33}, {0x66, 0xFF, 0x33}, {0x33, 0xFF, 0x66}, {0x33, 0xFF, 0xCC}, {0x33, 0xCC, 0xFF}, {0x00, 0x3D, 0xF5}, {0x00, 0x2E, 0xB8}, {0xF5, 0xB8, 0x00}, {0xB8, 0x8A, 0x00} };

int main (int argc, char *argv[])
{
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 640, 480);
    cairo_t *cr = cairo_create (surface);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 5);

    /*  first draw two rectangle shapes in explicitly defined places */
    cairo_rectangle(cr, 20, 20, 120, 80);
    cairo_rectangle(cr, 180, 20, 80, 80);
    /* before we go on to the fill of these two rectangles we've created, we might, or might not, like to include 
     But we want to more than apply a stroke with "cairo_stroke()" we want to preserve our path path too. Therefore: */ 
    cairo_stroke_preserve(cr);
    /*  so we still have two shapes we can fill because we used "preserve" */
    cairo_set_source_rgb(cr, (float)cs1[3][0]/255.0, (float)cs1[3][1]/255.0, (float)cs1[3][2]/255.0);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, (float)cs1[5][0]/255.0, (float)cs1[5][1]/255.0, (float)cs1[5][2]/255.0);
    cairo_arc(cr, 330, 60, 40, 0, 2*M_PI);
    /*  our rectangles are gone now you can be sure ... but we want to fill our circle, be careful to apply the preservce version of stroke */
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, (float)cs1[6][0]/255.0, (float)cs1[6][1]/255.0, (float)cs1[6][2]/255.0);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, (float)cs1[10][0]/255.0, (float)cs1[10][1]/255.0, (float)cs1[10][2]/255.0);
    cairo_arc(cr, 90, 160, 40, M_PI/4, M_PI);
    cairo_close_path(cr);
    cairo_stroke_preserve(cr);
    /*  fill considerations */
    cairo_set_source_rgb(cr, (float)cs1[9][0]/255.0, (float)cs1[9][1]/255.0, (float)cs1[9][2]/255.0);
    cairo_fill(cr);

    /*  OK, now we're going to creatan ellipse ... by first compressing our concept space and then applying a circle! */
    cairo_set_source_rgb(cr, (float)cs1[7][0]/255.0, (float)cs1[7][1]/255.0, (float)cs1[7][2]/255.0);
    /* the translate will send the center of our activities to a new placei .. and it will stay there! */
    cairo_translate(cr, 220, 180);
    cairo_scale(cr, 1, 0.7);
    cairo_arc(cr, 0, 0, 50, 0, 2*M_PI);
    cairo_stroke_preserve(cr);
    /*  Get ready for the fill: set color and then fill */
    cairo_set_source_rgb(cr, (float)cs1[8][0]/255.0, (float)cs1[8][1]/255.0, (float)cs1[8][2]/255.0);
    cairo_fill(cr);

    /* Let's do another of those, to see what the context retains */ 
    cairo_set_source_rgb(cr, (float)cs1[11][0]/255.0, (float)cs1[11][1]/255.0, (float)cs1[11][2]/255.0);
    /* the transalte will send the center of our activities to a new place */
//    cairo_restore(cr); // nope this doesn't really do it.
     cairo_matrix_t *mat;
     mat = malloc(sizeof(cairo_matrix_t));
     cairo_get_matrix(cr, mat);
    double xcur, ycur;
    cairo_get_current_point(cr, &xcur, &ycur);
    printf("Curpts: %3.4f %3.4f\n", xcur, ycur);  /* this just says zero */
    cairo_translate(cr, 20, 20); /*  beware,t his is relative to previous translate point */
    cairo_scale(cr, 1, 0.7);
    cairo_arc(cr, 0, 0, 50, 0, 2*M_PI);

    cairo_fill(cr);
    cairo_destroy(cr);
    free(mat);
    cairo_surface_write_to_png (surface, "sha.png");
    cairo_surface_destroy (surface);

    return 0;
}
