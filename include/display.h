#ifndef DISPLAY_INCLUDED
#define DISPLAY_INCLUDED

#include "include/utilities.h"

/**
 * Ecrire dans une fichier un vecteur de vecteurs
 * @param filename nom du ficher
 * @param a        vecteur de vecteurs
 * @param x        nombre de colonnes
 * @param y        nombre de lignes
 */
void write2Darray(char * filename, float ** a, int x, int y);

/**
 * Affiche un tableau (de float) à 2 dimensions
 * @param format format avec lequel afficher les valeurs
 * @param a      vecteur de vecteurs
 * @param lenx   taille des vecteurs de w
 * @param nx   taille de w
 */
void print2Darray(const char * format, float ** a, int lenx, int nx);

/**
 * Affiche un vecteur de float
 * @param format format avec lequel afficher les valeurs
 * @param a      vecteur de float
 * @param len    taille du vecteur
 * @param ret    aficher ou non un retour à la ligne
 */
void printVect(const char * format, float * a, int len, int ret);

#endif
