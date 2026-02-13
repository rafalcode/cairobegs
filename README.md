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

# At least with stroke op, and may be more, paths are often cleared, watch it!
Answer is to use the "preserve versions", i.e. cairo_stroke_preserve()
"A drawing operator that strokes the current path according to the current line width, line join, line cap, and dash settings. After cairo_stroke(), the current path will be cleared from the cairo context."
I also find that if you try and change colour, it will have no effect, as the original colour is preserved.

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

# grill2.c
The "winding road" is normalized to 100 total length, a cumulative array is built in terms of total value 100, defining the segments along the path and whether they are line to right (LINE2R)
curves at right (CURVER) etc. There are five of these for the four segment types. Why five? Well the first (0) is nothing, used for the first segment because the segmetns are typed by their endpoints.
i.e. the .p value of type CURVER is the end poit of an arc, not the beginning point. I have to admit, it's all a bit tortuous, but I did get it working to a basic level. However, it is only for 1 point!
One tedious thing is cairo_arc, and cairo_arc_negative, quite confusing. See cairo notes in pc_jottings.

# reading jpg images
Thi is not native to cairo ... but Bernhard Fischer can developed soem functions for doing so. Requires a manual compile.

# rectarrang.c
I've doe this alot of times. But I got into a frazzle once again over hbarnums and vbarnums. vbarnum are vertical bars that span the whole height of the canvas, so they can be
seen as columns, so to move, you move in the x direction. We leave this for j to do. i advances up to hbarnums, but gets multiplied by vbarnums each time.
