libcairo, wonderful but frustrating too.
the tricky parts relate to the affine transforming ... which is a discipline by the way
you need to work on it

a way to avoid it is just by using the splmple directives, like move_to and line_to and rectangle
you can do a fair bit with these.

OK how to start explaining? Well cairo needs two entities to get going: surface and context, in that order.

The surface entity needs to know the dimensions: which means a width and a length of course.

Then, and only then, can a cairo context be created. Thsi order is nto entirely intuitive. Here it is:
    cairo_surface_t *surface;
    cairo_t *cr;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMWIDTH, IMHEIGHT);
    cr = cairo_create (surface);

OK, so what about destroyers? It's clear the context "Must go" first.

    cairo_surface_write_to_png (surface, "rw1.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
