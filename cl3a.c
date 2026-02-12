/* FOcus on genertaing a PNG of the right size for an A4 pdf */
#include <cairo/cairo.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    
    int pdfw=842;
    int pdfh=595;
    // unfort, no such thang:1
    // image = cairo_image_surface_create_from_jpg("marspopm.jpg");
    // // so you must convert to png ...
    cairo_surface_t *surf0 = cairo_image_surface_create_from_png("marspopm.png");
    int w = cairo_image_surface_get_width (surf0);
    int h = cairo_image_surface_get_height (surf0);
    printf("w=%i,h=%i\n", w, h); 
    printf("Amount of times true image width exceeds pdfwidth:\n"); 
    float wfac= 2*(float)w/pdfw;
    printf("wfac=%2.2f\n", (float)w/pdfw);
    printf("Amount of times true image height exceeds pdfheight:\n"); 
    printf("hfac=%2.2f\n", (float)h/pdfh); 
    float hfac=2*(float)h/pdfh; 

    cairo_surface_t *surf2 = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 842, 595); // landscape A4 I think
    cairo_t *cr = cairo_create(surf2);
    cairo_scale(cr, 1./wfac, 1./hfac);
    cairo_set_source_surface (cr, surf0, 0, 0);
    cairo_paint(cr);

    cairo_destroy(cr);
    cairo_surface_write_to_png(surf2, "cl3a.png");
    cairo_surface_destroy (surf2);
    cairo_surface_destroy (surf0);

    return 0;
}
