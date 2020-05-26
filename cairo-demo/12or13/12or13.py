#!/usr/bin/python

# Written by Behdad Esfahbod, 2006
# http://mces.blogspot.com/2006/09/puzzle-12-or-13.html
# http://mces.blogspot.com/2006/09/solution-12.html
# http://mces.blogspot.com/2007/06/12-or-13-cairo-demo.html
# Not copyrighted, use as you wish

import sys
import math
import cairo
import pygtk
pygtk.require('2.0')
import gtk
import gtk.gdk
import pango
import gobject

def clamp(x, lo=0., hi=1.):
	return max (lo, min (x, hi))

def interpolate(x, x0, x1):
	return x0 * (1. - x) + x1 * (0. + x)

class Puzzle(gtk.Widget):
    def __init__(self, file, num = 12, width_mult = -1, div_mult = -1, top_mult = 0.5, start_mult = 0.0):
        gtk.Widget.__init__ (self)

	self.surface = cairo.ImageSurface.create_from_png (file)
	self.num = num
	self.set_multipliers (width_mult, div_mult, top_mult, start_mult)

    def set_multipliers(self, width_mult = None, div_mult = None, top_mult = None, start_mult = None):
	if (width_mult is not None):
	    if (width_mult < 0):
		width_mult = float (self.num + 1) / self.num
	    self.width_mult = width_mult
	if (div_mult is not None):
	    if (div_mult < 0):
		div_mult = float (self.num - 1) / self.num
	    self.div_mult = clamp (div_mult)
	if (top_mult is not None):
	    self.top_mult = clamp (top_mult)
	if (start_mult is not None):
	    self.start_mult = start_mult % 1

	self.surface_width  = self.surface.get_width  ()
	self.surface_height = self.surface.get_height ()

	self.man_width = int (math.ceil (float (self.surface_width) / self.num))
	self.man_half_width = int (round (float (self.surface_width) / (self.num * 2)))

	self.man_height = self.surface_height
	self.man_top_height = int (round (self.surface_height * self.top_mult))
	self.man_bottom_height = self.man_height - self.man_top_height

	self.effective_width  = (self.surface_width - self.man_width) * self.width_mult
	self.effective_width  = max (1, int (round (self.effective_width)))

	self.width  = self.effective_width + self.man_width
	self.height = self.man_top_height + self.man_height

	self.x_offset = self.man_half_width
	self.y_offset = 2 * self.man_top_height

	self.div_width = (self.effective_width * self.div_mult)
	self.backward_advance = - self.div_width
	self.forward_advance  = self.effective_width + self.backward_advance

	self.__cache_bodies()

    def do_size_request(self, requisition):
	requisition.width  = self.width
	requisition.height = self.height

    def do_size_allocate(self, allocation):
	gtk.Widget.do_size_allocate (self, allocation)

	top_mult= div_mult = start_mult = width_mult = None

	width_mult = float (allocation.width   - self.man_width) / (self.surface_width - self.man_width)
	width_mult = max (0, width_mult)

	top_mult = float (allocation.height - self.surface_height) / self.surface_height

	self.set_multipliers(width_mult = width_mult, top_mult = top_mult, div_mult = div_mult, start_mult = start_mult)

    def __cache_bodies(self):
	self.men = []
	xf = self.effective_width * self.start_mult
	xi = int (round (xf))
	for i in range (self.num):

		surface = self.surface.create_similar (cairo.CONTENT_COLOR_ALPHA, self.man_width, self.man_top_height)
		cr = cairo.Context (surface)
		cr.set_source_surface (self.surface, - i * self.man_width, 0)
		cr.paint ()
		surface.set_device_offset (self.man_half_width, self.man_top_height)
		top = surface

		surface = self.surface.create_similar (cairo.CONTENT_COLOR_ALPHA, self.man_width, self.man_bottom_height)
		cr = cairo.Context (surface)
		cr.set_source_surface (self.surface, - i * self.man_width, - self.man_top_height)
		cr.paint ()
		surface.set_device_offset (self.man_half_width, 0)
		bottom = surface

		x0 = xi
		xf = (xf + self.forward_advance) % self.effective_width
		xi = int (round (xf))
		x1 = xi

		class Man:
		    def __init__(self, top, bottom, x0, x1):
			self.top = top
			self.bottom = bottom
			self.x = [x0, x1]

		self.men.append (Man (top, bottom, x0, x1))
	self.men.reverse ()

    def do_realize(self):
        self.set_flags(self.flags() | gtk.REALIZED)

        self.window = gtk.gdk.Window(
            self.get_parent_window(),
            width=self.allocation.width,
            height=self.allocation.height,
            window_type=gtk.gdk.WINDOW_CHILD,
            wclass=gtk.gdk.INPUT_OUTPUT,
            event_mask=self.get_events() | gtk.gdk.EXPOSURE_MASK)

        self.window.set_user_data(self)

        self.style.attach(self.window)

        self.style.set_background(self.window, gtk.STATE_NORMAL)
        self.window.move_resize(*self.allocation)

    def do_unrealize(self):
        self.window.destroy()

    def do_expose_event(self, event):
        cr = self.window.cairo_create()
        cr.rectangle(event.area.x, event.area.y, event.area.width, event.area.height)
        cr.clip()

        self.draw(cr)

        return False

    def draw(self, cr):

    	cr.set_source_rgb (1, 1, 1)
	cr.paint ()

	cr.translate (self.x_offset, self.y_offset)

	if self.decorate:
	    cr.set_line_width (1)
	    cr.set_line_cap (cairo.LINE_CAP_BUTT)

	    cr.set_source_rgba (1., 0., 0., .8)

	    # horiz top line
	    cr.move_to (-self.x_offset, -self.man_top_height + .5)
	    cr.rel_line_to (self.width, 0)
	    cr.move_to (-self.x_offset, +self.man_bottom_height - .5)
	    cr.rel_line_to (self.width, 0)
	    # vert left line
	    cr.move_to (.5, -self.y_offset)
	    cr.rel_line_to (0, self.height)
	    # vert right line
	    cr.move_to (self.effective_width - .5, -self.y_offset)
	    cr.rel_line_to (0, self.height)

	    cr.stroke ()

	    cr.set_source_rgba (0., 0., 1., .8)
	    # horiz baseline
	    cr.move_to (-self.x_offset, .5)
	    cr.rel_line_to (self.width, 0)
	    cr.stroke ()

	    # vert div line
	    cr.set_source_rgba (0., 0., 1., interpolate (0+self.x_cycle, .9, .2))
	    cr.move_to (self.div_width, -self.y_offset)
	    cr.rel_line_to (0, self.height)
	    cr.stroke ()

	    # vert 'after' div line
	    cr.set_source_rgba (0., 0., 1., interpolate (1-self.x_cycle, .9, .2))
	    cr.move_to (self.forward_advance, -self.y_offset)
	    cr.rel_line_to (0, self.height)
	    cr.stroke ()

	    cr.set_font_size (self.man_top_height)
	    font_extents = cr.font_extents ()
	    font_height = font_extents[0] + font_extents[1]
	    y = -self.man_top_height - font_extents[1] - (self.man_top_height - font_height) / 2.
	    # num
	    cr.set_source_rgba (1., .6, 0., interpolate (0+self.cycle, .5, 0))
	    text = str (self.num)
	    extents = cr.text_extents (text)
	    cr.move_to ((self.effective_width - extents[2]) / 2. - extents[0], y)
	    cr.show_text (text)
	    # num+1
	    cr.set_source_rgba (1., .6, 0., interpolate (1-self.cycle, .5, 0))
	    text = str (self.num+1)
	    extents = cr.text_extents (text)
	    cr.move_to ((self.effective_width - extents[2]) / 2. - extents[0], y)
	    cr.show_text (text)

	for man in self.men:
	    cr.set_source_surface (man.bottom, man.x[0], 0)
	    cr.paint ()
	    cr.set_source_surface (man.top, * self.animate_pos (man))
	    cr.paint ()

	if self.decorate > 1:
	    cr.set_line_width (1)
	    cr.set_line_cap (cairo.LINE_CAP_ROUND)
	    cr.set_source_rgba (0., 1., 0., .8)
	    dy = float (self.man_height) / self.num

	    y = -self.man_top_height + dy * .5
	    cr.new_path ()
	    for man in self.men:
		cr.line_to (man.x[0], y)
		y += dy
	    cr.stroke ()

	    cr.set_line_width (5)
	    y = -self.man_top_height + dy * .5
	    cr.set_source_rgba (0., 1., 0., .8)
	    for man in self.men:
		cr.move_to (man.x[0], y)
		cr.rel_line_to (0, 0)
		cr.stroke ()
		y += dy

    def animate_pos (self, man):
	x = interpolate (self.x_cycle, man.x[0], man.x[1])
	if man.x[0] < man.x[1]:
	    y = 0
	else:
	    y = self.y_cycle * -self.man_top_height
	return (x,y)

    def tick (self):
	self.busy = True

	prev_phase = self.phase
	self.phase += 2*math.pi * self.speed / self.frame_rate

	if (self.phase - prev_phase) * (self.phase%(math.pi) - prev_phase%(math.pi)) < 0:
	    self.phase -= self.phase%(math.pi)
	    self.delay_tick ()
	
	self.phase %= 2*math.pi

	self.cycle = 1. - abs ((self.phase % (2*math.pi) - math.pi) / math.pi)
	c = math.cos (self.phase)
	self.x_cycle = clamp(-math.cos (self.phase), -.5, +.5) + .5
	self.y_cycle = abs (math.sin (self.phase)) ** 2

	self.window.invalidate_rect (gtk.gdk.Rectangle (0, 0, self.width, self.height), True)

	return True

    def delay_tick (self, d = -1):

	if d < 0:
	    d = 1. / self.speed

	if self.timeout_handler_id:
	    gobject.source_remove (self.timeout_handler_id)
	
	self.busy = False
	
	def delay (f):
	    self.timeout_handler_id = gobject.timeout_add (1000 / self.frame_rate, f)
	    return False

	if self.next_delay < 0:
	    self.next_delay = d

	self.timeout_handler_id = gobject.timeout_add (int (self.next_delay * 1000), delay, self.tick)
	self.next_delay = -1
	self.__animate = True

	return False

    def set_animation (self, animate):
	if self.__animate == animate:
	    return

	if self.__animate:
	    gobject.source_remove (self.timeout_handler_id)
	    self.timeout_handler_id = None
	    self.__animate = False
	if animate:
	    self.delay_tick (0)

    def __key_press_event(self, widget, event):
        if event.string == 'q':
            gtk.main_quit()
        elif event.string == ' ':
	    if not self.busy:
		self.delay_tick (0)
	    else:
		self.next_delay = 0

        elif event.string == 'b':
	    self.decorate = (self.decorate + 1) % 3

        elif event.string == 'a':
	    self.speed = min (1.0, self.speed * (2**+.25))
        elif event.string == 'z':
	    self.speed = max (0.1, self.speed * (2**-.25))

        elif event.string == 'l':
	    self.set_multipliers (start_mult = self.start_mult + .01)
        elif event.string == 'j':
	    self.set_multipliers (start_mult = self.start_mult - .01)

        elif event.string == 'i':
	    self.set_multipliers (div_mult = self.div_mult + .03 / self.num)
        elif event.string == 'k':
	    self.set_multipliers (div_mult = self.div_mult - .03 / self.num)

	else:
	    if event.string:
		print "Unhandled key", `event.string`
	    return
	self.window.invalidate_rect (gtk.gdk.Rectangle (0, 0, self.width, self.height), True)

    def run(self):
	self.decorate = 0
	self.cycle = 0.
	self.x_cycle = 0.
	self.y_cycle = 0.
	self.phase = 0.
	self.speed = .3
	self.frame_rate = 25

	self.next_delay = -1
 	self.__animate = False
	self.timeout_handler_id = 0

	self.delay_tick ()

        window = gtk.Window()
	window.props.allow_shrink = True
        window.add(self)
        window.connect("destroy", gtk.main_quit)
        window.connect("key-press-event", self.__key_press_event)
        window.show_all()

        gtk.main()

gobject.type_register(Puzzle)

def main():
    file = '12.png'
    count = 12

    print """How many?

 Press 'b' for annotations,
 space for transition (or just wait),
       'a' and 'z' to change speed,
       'j' and 'l' to change start offset,
       'k' and 'i' to change advance (aka move division line),
resize the window to change width and/or waist line,
   and 'q' to quit"""

    puzzle = Puzzle (file, count, width_mult = 0.688, div_mult = 0.388)
    puzzle.run()

if __name__ == "__main__":
    main()
