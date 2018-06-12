#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
 * @param  lenw   taille de w
 * @return        vecteur moyenne
 */
float * vectorAverage(float ** w, int lenx, int lenw);

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
void usage(char * error);

#endif
