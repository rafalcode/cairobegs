# cairbegs
This repository stands for "Cairo Beginnings" alot of the programs dating from 2011 around the time 
I was doing to the Hulsenbeck simulation.

There's a good amount of building block code, taken from the cairo examples page. So some very simple
examples here too.

# hydots aka. slines
Well, what a nice surprise ... very much spirograph in action. Nice pale green with dashed lines and black background!
and what a shock .. I only the executable! No grep of slines anywhere. Tsk!
OK finally discovered this was hypdots. Don't know why I named it to slines ... well I can forget tht now ... it's hypdots.

# circnam and rectnam
Failry related these two, rectnam is better. However the interrect spaces are detectably twice the margins.
They should be independent, right? The side margins acould be massive but the inter rects should be the same.
So it does do to have rectas inside rects really. Actaully I've done this already for the 96 well imitation

# paths are often cleared, watch it!
use the preserve versionsi, i.e.
"A drawing operator that strokes the current path according to the current line width, line join, line cap, and dash settings. After cairo_stroke(), the current path will be cleared from the cairo context."

# cl3.c & fr2.c
cl3 generates a surface from external png, easy enough. Only slightly bigger, OK. But fr2.c actually takes a clip (confirmed) of external png and places it in selected spot. Want a mixture of the two.

# magickcore + cairo?
Well you're going to be looking to transfer pixel info. The attraction of imagemagick is the vast amount of image functions it has. But it's probably also over kill.

# image of bright Mars from:
https://www.popularmechanics.com/space/moon-mars/a22497870/mars-opposition-2018/

# Chip off the old block
this is the fr1.c prog and the pdfr1.c. Note that I seem to have not used cairo outputting to pdf very much at all. It's a bit deceptive
because there's no real writing out, like in png. You destroy the pdf surface (which has a filename associated with it) and thats it.
You use cairo_show_page(cr) to go on to the next page.

# beziers
Limited by cubic beziers, you can combine them and if your are able to make the slop of last and first control pints to be the same, then you will get asmmoth transition
check out
https://www.pythoninformer.com/python-libraries/pycairo/bezier-curves/

# transforms
this affects the whole context cr, so how to selectively use it? Well usee cairo_save(cr) first, then introduce your transform and draw your shape. O foucrsae any shapes you draw
will be affected by the transform, but afetr your desired shape, then go cairo_restore(cr) and it will pul bakc the original from the stack. and you'll be back to normal.

# timstr1.c
this is a timeline for within day activities. Just manages a single horizontal strip with no annotations. You can't really fit so many events into these things.

## timstr2.c
I decided to not put strips and concentrate more on the timepoints themselves by putting a dot for them, then just a thing line between them.
also to stretch them out over several rows. Beware a time point may be not on next row but evern after it.
beware a time 

A temptation would be to just plot the points and put a line through them. No!
