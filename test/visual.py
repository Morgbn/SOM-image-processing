#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import math

def quit_figure(event):
    if event.key == 'q':
        plt.close(event.canvas.figure)

def readPoints(fin):
    f1 = open(fin).read()
    x = []
    y = []
    for i, line in enumerate(f1.split('\n')):
        line = line.split()
        if len(line) > 3: continue # entête
        if len(line):
            x.append(float(line[0]))
            y.append(float(line[1]))
    return x, y

def connectPoints(i, j, allx, ally, style):
    x1, x2 = allx[i], allx[j]
    y1, y2 = ally[i], ally[j]
    plt.plot([x1, x2], [y1, y2], style)

def main(fin, fout):
    cid = plt.gcf().canvas.mpl_connect('key_press_event', quit_figure)

    inx, iny = readPoints(fin)
    outx, outy = readPoints(fout)
    plt.plot(inx, iny, 'ro')

    max = len(outx)
    size = int(math.sqrt(max)) # taille d'une ligne
    for i in range(0, max, 1):
        if ((i+1) % size) and (i+1 < max):
            connectPoints(i, i+1, outx, outy, 'g-')
        if i+size < max:
            connectPoints(i, i+size, outx, outy, 'g-')
    # plt.plot(outx, outy, 'go')
    plt.show()

    return 0;

# main('inPoints.txt', 'outPoints.txt')
main('normalized.txt', 'data.txt')
