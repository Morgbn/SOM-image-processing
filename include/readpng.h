#ifndef READPNG_INCLUDED
#define READPNG_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <png.h>

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

#if TEST
/**
 * Traitement de l'image
 * @param row_pointers tableau de pixel RGBA
 * @param width        largeur
 * @param height       hauteur
 */
void processPngFile(png_bytep * row_pointers, int width, int height);
#endif

#endif
