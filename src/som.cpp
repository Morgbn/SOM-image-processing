#include "include/som.h"

int editImg(const char * fin, const char * fout, QProgressBar *progressBar, int verbose) {
  srand(time(NULL)); // initialise rand

  int width, height;
  int nx = 0;   // nombres de capteurs
  int nw = 2;   // nombres de neurones
  int lenx = 0; // taille des capteurs

  png_bytep * rowImg = readPngFile(fin, &width, &height);
  if (rowImg == NULL) return 1;
  float ** allx = getPoints(rowImg, &lenx, &nx, width, height);

  #if MY_HSV
    for (int i = 0; i < nx; i++) rgb2hsv(allx[i]);
  #endif
  #if MY_HSL
    for (int i = 0; i < nx; i++) rgb2hsl(allx[i]);
  #endif
  #if MY_HSVRGB
    lenx = 6;
    float ** newx = create2Darray(nx, lenx);
    for (int i = 0; i < nx; i++)
      for (int j = 0; j < 3; j++) newx[i][j] = allx[i][j];

    for (int i = 0; i < nx; i++) rgb2hsv(allx[i]);

    for (int i = 0; i < nx; i++)
      for (int j = 0; j < 3; j++) newx[i][3+j] = allx[i][j];
    free(allx);
    allx = newx;
  #endif
  #if MY_HSVL
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
  #endif

  float ** w = som(allx, lenx, nx, nw, progressBar, verbose);

  #if MY_HSV || MY_HSVL
    for (int i = 0; i < nx; i++) hsv2rgb(allx[i]);
    for (int i = 0; i < nw; i++) hsv2rgb(w[i]);
  #endif
  #if MY_HSL
    for (int i = 0; i < nx; i++) hsl2rgb(allx[i]);
    for (int i = 0; i < nw; i++) hsl2rgb(w[i]);
  #endif

  if (verbose) { printf("W = "); print2Darray("%g", w, lenx, nw); }

  for(int y = 0; y < height; y++) {
    png_bytep row = rowImg[y];
    for(int x = 0; x < width; x++) {
      png_bytep px = &(row[x * 4]); // un pixel = [R,G,B,A]
      float d, min;
      int bestIndex;
      for (int i = 0; i < nw; i++) {
        d = 0; for (int j = 0; j < 3; j++) d += pow(px[i] - w[i][j], 2); // dist eucl
        if (!i || d < min) { // plus petite distance
          min = d;
          bestIndex = i;
        }
      }
      for (int i = 0; i < 3; i++) px[i] = w[bestIndex][i]; // RGB
      px[3] = 255; // Alpha
    }
  }
  if (writePngFile(fout, rowImg, width, height))
    return 1;
  return 0;
}
