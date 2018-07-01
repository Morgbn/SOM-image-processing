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

  #if HSV
    for (int i = 0; i < nx; i++) rgb2hsv(allx[i]);
  #endif
  #if HSL
    for (int i = 0; i < nx; i++) rgb2hsl(allx[i]);
  #endif
  #if HSVRGB
    lenx = 6;
    float ** new = create2Darray(nx, lenx);
    for (int i = 0; i < nx; i++)
      for (int j = 0; j < 3; j++) new[i][j] = allx[i][j];

    for (int i = 0; i < nx; i++) rgb2hsv(allx[i]);

    for (int i = 0; i < nx; i++)
      for (int j = 0; j < 3; j++) new[i][3+j] = allx[i][j];
    free(allx);
    allx = new;
  #endif
  #if HSVL
    lenx = 4;
    float ** new = create2Darray(nx, lenx);
    for (int i = 0; i < nx; i++)
      new[i][3] = (0.2126*allx[i][0] + 0.7152*allx[i][1] + 0.0722*allx[i][2]);

    for (int i = 0; i < nx; i++) {
      rgb2hsv(allx[i]);
      for (int j = 0; j < 3; j++) new[i][j] = allx[i][j];
    }
    free(allx);
    allx = new;
  #endif

  float ** w = som(allx, lenx, nx, nw);

  #if HSV || HSVL
    for (int i = 0; i < nx; i++) hsv2rgb(allx[i]);
    for (int i = 0; i < nw; i++) hsv2rgb(w[i]);
  #endif
  #if HSL
    for (int i = 0; i < nx; i++) hsl2rgb(allx[i]);
    for (int i = 0; i < nw; i++) hsl2rgb(w[i]);
  #endif

  printf("W = "); print2Darray("%g", w, lenx, nw);

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
  char * newName = "output.png";
  // char newName[255];
  // filename[strlen(filename)-4] = 0;
  // sprintf(newName, "%s_edited%s.png", filename, HSV ? "HSV" : (HSL ? "HSL" : HSVRGB ? "H&R" : (HSVL ? "HSVL": "RGB")));
  writePngFile(newName, rowImg, width, height);
  return 0;
}
