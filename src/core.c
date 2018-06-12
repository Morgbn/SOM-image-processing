#include "core.h"

float ** getPoints(char * filename, int * nx, int * lenx) {
  FILE * fp;
  char * l = NULL;
  size_t len = 0;

  if ((fp = fopen(filename, "r")) == NULL)
    usage("getPoints : error reading the file");

  if ((getline(&l, &len, fp)) == -1) // lire la 1er ligne
    usage("getPoints : bad file");   // erreur

  int rows = 0, cols = 0;
  sscanf(l, "ROWS %d\tCOLS %d", &rows, &cols); // récupére les tailles
  *nx = rows;
  *lenx = cols;

  float ** cells = create2Darray(rows, cols);

  // lire les données
  int i = 0, j;
  while ((getline(&l, &len, fp)) != -1) {
    char * token; j = 0;
    for (token = strtok(l, "\t"); token != NULL; token = strtok(NULL, "\t"))
      cells[i][j++] = atof(token);
    i++;
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
  // trouver le min et le max des vecteurs
  float max, min;
  for (size_t i = 0; i < lenw; i++) {
    for (size_t j = 0; j < lenx; j++) {
      if (w[i][j] > max || (!i && !j)) max = w[i][j];
      if (w[i][j] < min || (!i && !j)) min = w[i][j];
    }
  }

  for (size_t i = 0; i < lenw; i++) {
    for (size_t j = 0; j < lenx; j++) {
      w[i][j] -= min; // enlever à chaque le min
      w[i][j] /= max; // et le diviser par le maxNei
    }
  }
}
