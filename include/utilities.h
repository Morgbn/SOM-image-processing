#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED
/** @file utilities.h
    Fonctions utiles au reste de l'application
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * rgba vers hsv
 * @param rgb
 */
void rgb2hsv(float *rgb);

/**
 * hsv rgba
 * adapté de https://stackoverflow.com/a/6930407
 * @param hsv
 */
void hsv2rgb(float *hsv);

/**
 * rgba vers hsl
 * adapté de https://gist.github.com/mjackson/5311256
 * @param rgb
 */
void rgb2hsl(float *rgb);

/**
 * hue ver rgb
 * https://www.programmingalgorithms.com/algorithm/hsl-to-rgb?lang=C
 */
float hue2rgb(float v1, float v2, float vH);

/**
 * hsl rgba
 * adapté de https://gist.github.com/mjackson/5311256
 * @param hsl
 */
void hsl2rgb(float *hsl);

/**
 * Calcule la distance euclidienne entre 2 vecteurs
 * @param  x   vecteur
 * @param  y   vecteur
 * @param  len taille des vecteurs
 * @return     distance euclidienne
 */
float distEucl(float * x, float * y, int len);

/**
 * Calcule la moyenne des composantes des vecteurs
 * @param  w      vecteur de vecteurs
 * @param  lenx   taille des vecteurs de w
 * @param  nx     taille de w
 * @return        vecteur moyenne
 */
float * vectorAverage(float ** w, int lenx, int nx);

/**
 * Créer un vecteur de vecteurs de flottants
 * @param  rows nombres de lignes
 * @param  cols nombre de colonnes
 * @return vecteur de vecteurs de flottants
 */
float ** create2Darray(int rows, int cols);

/**
 * Affiche un message d'erreur et quite
 * @param error message
 */
void usage(const char * error);

#endif
