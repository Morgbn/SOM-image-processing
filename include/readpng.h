#ifndef READPNG_INCLUDED
#define READPNG_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include "include/utilities.h"
#include "include/mainwindow.h"

/*
* readPngFile, writePngFile, processPngFile
* quite highly inspired from http://zarb.org/~gc/html/libpng.html
*
* ajouter -lpng à la compilation
*/

/**
 * Lire une image au format png
 * @param  filename nom du fichier
 * @param  width    largeur
 * @param  height   hauteur
 * @return          tableau de pixels RGBA
 */
png_bytep * readPngFile(const char *filename, int *width, int *height);

/**
 * Ecrire une image au format png
 * @param filename     nom du fichier
 * @param row_pointers tableau de pixels RGBA
 * @param width        largeur
 * @param height       hauteur
 * @return             0->pas d'erreur,1->erreur
 */
int writePngFile(const char *filename, png_bytep *row_pointers, int width, int height);

/**
 * Regarde si 2 pixels sont identiques
 * @param  px1
 * @param  px2
 * @return     1 = identique, 0 sinon
 */
int samePx(png_bytep px1, png_bytep px2);

/**
 * Cherche les 8 voisins d'un pixel
 * @param  img image dans laquel chercher
 * @param  x
 * @param  y
 * @param  w   largeur de l'image
 * @param  h   hauteur de l'image
 * @param  n   nombre de voisin trouvé
 * @return     tableau de voisins
 */
png_bytep * neiPx(png_bytep * img, int x, int y, int w, int h, int * n);

/**
 * Filtre médian
 * @param img         image
 * @param w           largeur de l'image
 * @param h           hauteur de l'image
 * @param size        taille du filtre
 * @param progressBar barre de progres
 * @param progress    indicateur de progression
 */
void medianFilter(png_bytep * img, int w, int h, int size, QProgressBar *progressBar, int *progress);

#endif
