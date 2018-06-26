#include "core.h"

float ** getPoints(char * filename, int * lenx, int *nx, int * width, int * height) {
  png_bytep *rowImg = readPngFile(filename, width, height);
  *nx = (*width) * (*height);
  *lenx = 4; // R,G,B,A

  float ** cells = create2Darray(*nx, *lenx);

  int j = 0;
  for(int y = 0; y < *height; y++) {
    png_bytep row = rowImg[y];
    for(int x = 0; x < *width; x++) {
      png_bytep px = &(row[x * 4]); // un pixel = [R,G,B,A]
      for (int i = 0; i < *lenx; i++) cells[j][i] = px[i];
      j++;
    }
  }
  return cells;
}

void decreaseA(float * a, float a0, int t, int T) {
  *a = a0 * exp( -(double)t / T);
}

void decreaseNhdSize(float * NhdSize, int Nit, int t, int T) {
  *NhdSize = Nit * (1 - (1.0 * t) / T);
}

float h(float dist, float a, int NhdSize) {
  // return (dist < NhdSize) ? 1 : 0; // forme binaire
  // if (!a) return 0;
  return (float) exp((- dist * dist) / (2 * a * a));
}

int findBmuIndex(float ** w, float * x, int lenx, int lenw) {
  int bmuIndex;
  int nbmu = 1;                           // nb de déclenchements
  float jdist = -1;

  for (int i = 0; i < lenw; i++) {
    float dist = distEucl(x, w[i], lenx); // calcul distance

    if (dist <= jdist || jdist < 0) {     // nouveau déclenchement
      if (dist == jdist &&                // déclenchement multiples
         randomInt(0, ++nbmu)) continue;  // -> sélection aléatoire
      if (dist < jdist)                   // nouveau déclenchement
        nbmu = 1;                         // -> remet à 1
      jdist = dist;
      bmuIndex = i;
    }
  }
  return bmuIndex;
}

float ** getNei(float ** w, int n, int r, int N, int lenx, int * l) {
  int width = sqrt(N);
  int x = n % width;                                    // index vers coordonnées
  int y = n / width;

  int maxNei = pow(r*2+1, 2);                           // nb max de voisins (avec le bmu)
  float ** nei = create2Darray(N, maxNei);              // allocation pr voisins

  int len = 0;
  for (int i = -r; i <= r; i++) {
    for (int j = -r; j <= r; j++) {
      if (!j && !i) continue;                           // coordonnées du bmu (l'exclure de la liste)
      int yi = y+i, xj = x+j;
      if (yi< 0 || xj< 0 || yi >= width || xj >= width) // qd le rayon dépasse la 'matrice'
        continue;
      nei[len++] = w[yi*width+xj];
    }
  }
  for (size_t i = len+1; i < lenx; i++) free(nei[i]);   // libére espace non utilisé

  *l = len; // nombre de voisins
  return nei;
}

void normalizeAll(float **w, int lenw, int lenx) {
  for (size_t i = 0; i < lenw; i++)
    for (size_t j = 0; j < lenx; j++)
      w[i][j] /= 255; // et le diviser par le maximum
}
