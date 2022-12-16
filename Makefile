CC=gcc
CFLAGS=-g -Wall
SPECLIBS=-lcairo -lm
SPECINC=-I/home/nutria/mylocal/include
EXECUTABLES=sq arc2 arc3 binodots binodot2 spir spir2 spir2b spir3 spir4 sevshap lines lintx hypdots pa1 linestar grad ssg ssl lenlines lenlin2 pat lotsofrects rects2 lintx2 rect16 rectnam cl2 rw1 rw2 linev rectcolcat imgen foldr3 strips str0 lin3 lin4 spir4b pdf2 barbr cirs0 cirnam pdf1 pdf2 pdf0

# NOTES:
# 	setsourcegradient.c is gone. You'll need to download it once again, as it showed the way cairo handles gradients
# 	there was a linear gradiant and a radial gradiant, which can/is applied through the whole image, not particularly within 
# 	the objects that appear in it.

# sq: an attempt at something that compiles and runs but gives a blank image
cairar: cairar.c
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

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
