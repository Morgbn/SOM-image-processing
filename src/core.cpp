#include "include/core.h"

int editImg(const char * fin, const char * fout, int nw, QProgressBar *progressBar, int verbose) {
  srand(time(NULL)); // initialise rand

  int width, height;
  int nx = 0;   // nombres de capteurs
  int lenx = 0; // taille des capteurs

  png_bytep * rowImg = readPngFile(fin, &width, &height);
  png_bytep * cpyImg = readPngFile(fin, &width, &height); // copie
  if (rowImg == NULL) return 1;
  float ** allx = getPoints(rowImg, &lenx, &nx, width, height);

  if (MY_HSV)
    for (int i = 0; i < nx; i++) rgb2hsv(allx[i]);
  if (MY_HSL)
    for (int i = 0; i < nx; i++) rgb2hsl(allx[i]);
  if (MY_HSVRGB) {
    lenx = 6;
    float ** newx = create2Darray(nx, lenx);
    for (int i = 0; i < nx; i++)
    for (int j = 0; j < 3; j++) newx[i][j] = allx[i][j];

    for (int i = 0; i < nx; i++) rgb2hsv(allx[i]);

    for (int i = 0; i < nx; i++)
    for (int j = 0; j < 3; j++) newx[i][3+j] = allx[i][j];
    free(allx);
    allx = newx;
  }
  if (MY_HSVL) {
    lenx = 4;
    float ** newx = create2Darray(nx, lenx);
    for (int i = 0; i < nx; i++)
      newx[i][3] = (0.2126*allx[i][0] + 0.7152*allx[i][1] + 0.0722*allx[i][2]);

    for (int i = 0; i < nx; i++) {
      rgb2hsv(allx[i]);
      for (int j = 0; j < 3; j++) newx[i][j] = allx[i][j];
    }
    free(allx);
    allx = newx;
  }

  float ** w = som(allx, lenx, nx, nw, progressBar, verbose);

  if (MY_HSV || MY_HSVL) {
    for (int i = 0; i < nx; i++) hsv2rgb(allx[i]);
    for (int i = 0; i < nw; i++) hsv2rgb(w[i]);
  }
  if (MY_HSL) {
    for (int i = 0; i < nx; i++) hsl2rgb(allx[i]);
    for (int i = 0; i < nw; i++) hsl2rgb(w[i]);
  }

  if (verbose) { printf("W = "); print2Darray("%g", w, lenx, nw); }

  for(int y = 0; y < height; y++) {
    png_bytep row = rowImg[y];
    for(int x = 0; x < width; x++) {
      png_bytep px = &(row[x * 4]); // un pixel = [R,G,B,A]
      float d, min;
      int bestIndex = 0;
      for (int i = 0; i < nw; i++) {
        d = 0; for (int j = 0; j < 3; j++) d += pow(px[j] - w[i][j], 2); // dist eucl
        if (!i || d < min) { // plus petite distance
          min = d;
          bestIndex = i;
        }
      }
      for (int i = 0; i < 3; i++) px[i] = w[bestIndex][i]; // RGB
      px[3] = 255; // Alpha
    }
  }

  if (postProcess) { // enlève les petites zones / bruits
    int i = 0;
    if (progressBar) progressBar->setMaximum(width*height);
    medianFilter(rowImg, width, height, 11, progressBar, &i);
  }

  if (makeTransparent) {
    png_bytep firstPx = &(rowImg[0][width/2 * 4]); // estime que milieu haut = arriére plan
    for (int y = 0; y < height; y++) {
      png_bytep row = rowImg[y];
      png_bytep cpyRow = cpyImg[y];
      for (int x = 0; x < width; x++) {
        png_bytep px = &(row[x * 4]); // un pixel = [R,G,B,A]
        png_bytep pxOr = &(cpyRow[x * 4]); // pixel d'origine
        int d = 0; for (int j = 0; j < 3; j++) d += pow(px[j] - firstPx[j], 2); // dist eucl
        if (d == 0) pxOr[3] = 0; // mettre transparent
      }
    }
    rowImg = cpyImg;
  }

  if (writePngFile(fout, rowImg, width, height))
    return 1;
  return 0;
}
