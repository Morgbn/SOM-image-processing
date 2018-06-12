#ifndef DISPLAY_INCLUDED
#define DISPLAY_INCLUDED

#include "utilities.h"

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
void print2Darray(char * format, float ** a, int lenx, int nx);

/**
 * Affiche un vecteur de float
 * @param format format avec lequel afficher les valeurs
 * @param a      vecteur de float
 * @param len    taille du vecteur
 * @param ret    aficher ou non un retour à la ligne
 */
void printVect(char * format, float * a, int len, int ret);

/**
 * Initialiser l'affichage d'un graphe avec gnuplot
 * @return pipe
 */
FILE * gnuplotInit();

/**
 * Afficher la grille et les points dans gnuplot
 * @param gnuplot pipe vers gnuplot
 * @param w       grille de neurones
 * @param nw      nombre de neurones
 * @param allx    capteurs
 * @param nx      nombre de capteurs
 */
void gnuplotGrid(FILE * gnuplot, float ** w, int nw, float ** allx, int nx);

/**
 * Affiche des variables utiles dans gnuplot
 * @param gnuplot pipe vers gnuplot
 * @param t       nombre d'itérations effectué
 * @param coefA   coef d'apprentissage
 * @param NhdSize taille du rayon de voisinage
 */
void gnuplotShowVars(FILE * gnuplot, int t, float coefA, float NhdSize);

#endif
