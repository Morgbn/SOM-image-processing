#!/usr/bin/env python
# -*- coding: utf-8 -*-

from random import uniform, random



def genRandomNum(row, col):
    print 'ROWS %i\tCOLS %i' % (row, col)
    test = 2
    if test == 1:
        min = 0
        max = 5
        for i in range(0, row):
            for j in range(0, col):
                print round(uniform(min, max), 2), '\t',
            print
    if test == 2:
        k = 0
        for i in range(0, row):
            for j in range(0, col):
                if k < (row*col - 8):
                    print round(uniform(10, 12), 2), '\t',
                if k == row*col-1:
                    print round(uniform(12, 14), 2), '\t',
                if k == row*col-2:
                    print round(uniform(8, 10), 2), '\t',
                if k == row*col-3:
                    print round(uniform(8, 10), 2), '\t',
                if k == row*col-4:
                    print round(uniform(8, 10), 2), '\t',
                if k == row*col-5:
                    print round(uniform(12, 14), 2), '\t',
                if k == row*col-6:
                    print round(uniform(12, 14), 2), '\t',
                if k == row*col-7:
                    print round(uniform(8, 10), 2), '\t',
                if k == row*col-8:
                    print round(uniform(12, 14), 2), '\t',
                k += 1
            print
    if test == 3:
        min = 0
        max = 5
        for i in range(0, row):
            for j in range(0, col):
                if random() > .8: a = min; b = max
                else : a = (min+max)/2 - 1; b = (min+max)/2 + 1
                print round(uniform(a, b), 2), '\t',
            print

import sys

if len(sys.argv) >= 4:
    min = int(sys.argv[3])
    max = int(sys.argv[4])
if len(sys.argv) > 2:
    genRandomNum(int(sys.argv[1]), int(sys.argv[2]))
else: print "genNum.py [Nombre de points] [Dimension]"
