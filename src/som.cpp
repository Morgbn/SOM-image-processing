#include "include/som.h"

int editImg(const char * fin, const char * fout, int nw, QProgressBar *progressBar, int verbose) {
  srand(time(NULL)); // initialise rand

  int width, height;
  int nx = 0;   // nombres de capteurs
  int lenx = 0; // taille des capteurs

  png_bytep * rowImg = readPngFile(fin, &width, &height);
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

  if (postProcess) {
    for(int y = 0; y < height; y++) {
      png_bytep row = rowImg[y];
      for(int x = 0; x < width; x++) {
        png_bytep px = &(row[x * 4]); // un pixel = [R,G,B,A]
        int n;
        png_bytep * nei = neiPx(rowImg, x, y, width, height, &n);

        int ncolors[9] = {0}; // jusqu'a 9 couleurs différentes
        ncolors[0] = 1;
        for (int i = 0; i < n; i++) { // parcourir les voisins
          if (samePx(nei[i], px)) ncolors[0]++; // même couleurs
          else {
            for (int j = 0; j < i+1; j++)
            if (samePx(nei[i], nei[j])) {
              ncolors[j+1]++; break;
            }
          }
        }
        int iMax = 0;
        for (int i = 0; i < 9; i++)
          if (ncolors[iMax] < ncolors[i]) iMax = i;
        if (iMax != 0) {
          px[0] = nei[iMax-1][0];
          px[1] = nei[iMax-1][1];
          px[2] = nei[iMax-1][2];
          px[3] = nei[iMax-1][3];
        }
      }
    }
  }

  if (makeTransparent) {
    png_bytep firstPx = &(rowImg[0][width/2]); // estime que milieu haut = arriére plan
    for(int y = 0; y < height; y++) {
      png_bytep row = rowImg[y];
      for(int x = 0; x < width; x++) {
        png_bytep px = &(row[x * 4]); // un pixel = [R,G,B,A]
        int d = 0; for (int j = 0; j < 3; j++) d += pow(px[j] - firstPx[j], 2); // dist eucl
        if (d == 0) px[3] = 0; // mettre transparent
      }
    }
  }

  if (writePngFile(fout, rowImg, width, height))
    return 1;
  return 0;
}
