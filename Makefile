CC=gcc
CFLAGS=-g -Wall
SPECLIBS=-lcairo -lm
CJPGLIBS=-lm -lcairo -lcairo_jpg -ljpeg # cairp +jpg libs
SPECINC=-I/home/nutria/mylocal/include
SPECINC2=-I/usr/include/cairo
EXECUTABLES=sq bez0 arc2 arc3 binodots binodot2 spir spir2 spir2b spir3 spir4 sevshap lines lintx hypdots pa1 strokefills linestar grad ssg ssl lenlines lenlin2 pat lotsofrects rects2 lintx2 rect16 rectnam cl2 rw1 rw2 linev rectcolcat imgen foldr3 strips str0 lin3 lin4 spir4b pdf2 barbr cirs0 cirnam pdf1 pdf2 pdf0 fr0 fr1 fr2 ingot0 cl3 cl4 bez1 rot0 rot1 arro arro2 arro3 arro4 imagkcore0 core core_rfmod cl3a pdfr1 rects00 rects01 rects02 focsqj timstr0 timstr1 timstr2 tu tu2 tu3 gribz0 gribz1 gridrw grill func0 arro3a arro6 rour grill0 grill2 grill3 grill22 grillpa grid2v bez2 sl0 sl1 sl1 arrow3

# wnat ot include imagemagick core libs 
# the following the result of MagickCore-config --cflags --cppflags (cppflags are the exact same so you can leave them out).
# you need to habe MagickCore-config in your $PATH of course
# in Debian its' in here: /usr/lib/x86_64-linux-gnu/ImageMagick-6.9.11/bin-q16
# # unfort. th
IMAGKFLAGS=-I/usr/include/x86_64-linux-gnu/ImageMagick-6 -I/usr/include/ImageMagick-6 -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16
# IMAGKFLAGS2=-I/usr/include/ImageMagick-6
IMAGKLIBS=-lMagickCore-6.Q16

# taken from old core.c
imagkcore0: imagkcore0.c
	gcc ${CFLAGS} ${IMAGKFLAGS} -o $@ $^ ${IMAGKLIBS}
	# gcc ${CFLAGS} ${IMAGKFLAGS} $^
core: core.c
	gcc ${CFLAGS} ${IMAGKFLAGS} -o $@ $^ ${IMAGKLIBS}
core_rfmod: core_rfmod.c
	gcc ${CFLAGS} ${IMAGKFLAGS} -o $@ $^ ${IMAGKLIBS}

# prog: main.c
#     gcc $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

# NOTES:
# 	setsourcegradient.c is gone. You'll need to download it once again, as it showed the way cairo handles gradients
# 	there was a linear gradiant and a radial gradiant, which can/is applied through the whole image, not particularly within 
# 	the objects that appear in it.

# sq: an attempt at something that compiles and runs but gives a blank image
cairar: cairar.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# trying rotations
rot0: rot0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
rot1: rot1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

fr0: fr0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
fr1: fr1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# fr1 but outputting to pdf.
pdfr1: pdfr1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# I use 
# a simplified time line via ingots (equally sized visually)
ingot0: ingot0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
timstr0: timstr0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
timstr2: timstr2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
timstr1: timstr1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# wantot do a grill type drwaing, and decided to build on grid. The following is pretty much just a grid.
grill0: grill0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# this is the prototype for the grill .. should work OK
grill: grill.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# now to add those arrows.
grill2: grill2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
grill22: grill22.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
grillpa: grillpa.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
grill3: grill3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

tu: tu.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS} -lm
tu2: tu2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS} -lm
tu3: tu3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS} -lm
gridrw: gridrw.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS} -lm

# just two vertical bars 
# actually this is pretty good:
grid2v: grid2v.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

gribz0: gribz0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS} -lm
# above was columnwise .. which might make sense sometimes.
gribz1: gribz1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS} -lm
# sat down and came up with some margin and const ideas.
fr2: fr2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
cl3: cl3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# resize please
cl3a: cl3a.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
cl4: cl4.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# How to make an arrow
# actually not so intuitve because at each 
# line_to, current position changes.
arro: arro.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# and now how to deal with slope
arro2: arro2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
arro3: arro3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# this is a cleaner version of arro3.c using slopes and cos and sine:
arrow3: arrow3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
arro3a: arro3a.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# trying to emulate wiki how's arro.
arro4: arro4.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# but what can cairo do with pdf's?
pdf0: pdf0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
pdf1: pdf1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
pdf2: pdf2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# sq: an attempt at something that compiles and runs but gives a blank image
sq: sq.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

bez0: bez0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
bez1: bez1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
bez2: bez2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
sl0: sl0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
sl1: sl1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# arc2: messy three lines and a a circle
arc2: arc2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# arc3: messy three lines and a a circle
arc3: arc3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# circles so I can make random walks all over the pace
rw1: rw1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# circles so I can make random walks all over the pace
rw2: rw2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Simple lines
lines: lines.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Simple lines
lin3: lin3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Simple lines
lin4: lin4.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Simple strips
str0: str0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# rand colour strips
strips: strips.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# A multiple image generator, cretaes its own directory and piles all the files in there.
imgen: imgen.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Vertical lines
linev: linev.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# lines but getting ready for trees
binodots: binodots.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# lines but getting ready for trees
binodot2: binodot2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# converting binodots2 into a binary random walk
binornd: binornd.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Lines and now a little text: this is probaby best to start learning text
lintx: lintx.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Lines and now a little text
lintx2: lintx2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# An attempt to use loops to draw 
sevshap: sevshap.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# spiro inspired?
spir: spir.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# An attempt to use loops to draw 
spir2: spir2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Havig trouble with spir3, so go back to an alternative version of spir2 and mess with it to see what's up
spir2b: spir2b.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# OK, managed to get a decent multishape (not multi-shape type coming up) */
spir3: spir3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Multishape grid with xcolor set
spir4: spir4.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Like spir4, except tighter
spir4b: spir4b.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# where did slines.png come from?
circofcircs: circofcircs.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Multishape grid with xcolor set
cirs2: cirs2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Multishape grid with xcolor set
cirs3: cirs3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# after thinking I had the spirogragh licked in circs2, I realised I hadn't,
# you don't draw a circle at every point. Each point is part of a non-simple curving path!
# so I decided to just draw a point at selected parts of the hypotrochoid. So this methods,
# does enable you to get a false one, because it's not a path but a unassociated points 
# which follow the path!
hypdots: hypdots.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# now tryign to get a path going
linestar: linestar.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# A polygon with some lines left out.
pa1: pa1.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
strokefills: strokefills.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# An useless one which just outputs a blank image.
ssg: ssg.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Colour gradation exercise
grad: grad.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Colour gradation exercise
ssl: ssl.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Lines with colour gradation: useful for visual confirmation of length of line.
lenlin2: lenlin2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Lines with colour gradation: useful for visual confirmation of length of line.
barbr: barbr.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# uses four images as patterns and presents them in four rects. Good enough.
pat: pat.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# as the name says
lotsofrects: lotsofrects.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# as the name says
rects00: rects00.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
rects01: rects01.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
rects02: rects02.c
	${CC} ${CFLAGS} -o $@ $^ ${CJPGLIBS}
# FOCus SQuare Jpg
# # you use cc2.py to clikc on some focus spots of a large JPG and
# this prog will cookie-cut squares from the image onto a PNG
# current it only occupies a row, and does not take into accoutns corners or edges.
focsqj: focsqj.c
	${CC} ${CFLAGS} ${SPECINC2} -o $@ $^ ${CJPGLIBS}


# as the name says
rects0: rects0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# builds upon lotsofrects with a big (256) color array
rects2: rects2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# sixteen rectangles with different colors. This is a preparation to including their names 
# in the boxes to ... ran into trouble with potiners to structs with strings in them.
# this uses two colorstructs one with colors in the typical int 0-255 coding and the other
# for usage with cairo (floats 0-1).
rect16: rect16.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

cirs0: cirs0.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# OK; via rectangles, which may not be the best thing, putting names into rectangles
# note the 16 colors are the .Xdefaults colors.
rectnam: rectnam.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
cirnam: cirnam.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# Takes the colour triangles further, now trying to arrive at nice (cute)
# color categories.
rectcolcat: rectcolcat.c
	${CC} ${CFLAGS} ${SPECINC} -o $@ $^ ${SPECLIBS}

# surprise ... render text in to image files
foldr3: foldr3.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# What can cairo do with PNG images?
cl: cl.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# What can cairo do with PNG images?
cl2: cl2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# just trying to offload drawing to functions.
func0: func0.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^ ${SPECLIBS}
# and also sorting out useefulness of slope
# was using func0.c for this, so at least it's all sent to function.
# clumsy attempt to get arrow. Though it's not actually bad.
arro5: arro5.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^ ${SPECLIBS}
# got too complicated.
arro6: arro6.c
	${CC} ${CFLAGS} -std=c99 -o $@ $^ ${SPECLIBS}
rour: rour.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
