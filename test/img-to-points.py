#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
if len(sys.argv) < 2: print "img-to-points.py [filename]"; exit(1)

import Image
import numpy as np

im = Image.open(sys.argv[1])

colorToMatch = [255, 0, 0]
points = []
for y, line in enumerate(np.array(im)):
    for x, color in enumerate(line):
        if set(color) == set(colorToMatch): points.append('%i\t%i' % (x, y))

print "ROWS %i	COLS 2" % len(points)
for coo in points: print coo
