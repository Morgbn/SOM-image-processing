#include "som.h"

int main(int argc, char const *argv[]) {
  if (argc < 2) usage("need a filename");
  char * filename = (char *) argv[1];
  srand(time(NULL)); // initialise rand

  int width, height;
  int nx = 0;   // nombres de capteurs
  int nw = 2;   // nombres de neurones
  int lenx = 0; // taille des capteurs

  png_bytep * rowImg = readPngFile(filename, &width, &height);
  float ** allx = getPoints(rowImg, &lenx, &nx, width, height);

  float ** w = som(allx, lenx, nx, nw);

  for(int y = 0; y < height; y++) {
    png_bytep row = rowImg[y];
    for(int x = 0; x < width; x++) {
      png_bytep px = &(row[x * lenx]); // un pixel = [R,G,B,A]
      float d, min;
      int bestIndex;
      for (int i = 0; i < nw; i++) {
        d = 0; for (int j = 0; j < lenx; j++) d += pow(px[i] - w[i][j], 2);
        if (!i || d < min) { // plus petite distance
          min = d;
          bestIndex = i;
        }
      }
      for (int i = 0; i < lenx; i++) px[i] = w[bestIndex][i];
    }
  }
  writePngFile("output.png", rowImg, width, height);
  return 0;
}
