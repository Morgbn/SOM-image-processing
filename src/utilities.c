#include "utilities.h"

float distEucl(float * x, float * y, int len) {
  float dist = 0;
  for (size_t i = 0; i < len; i++) {
    dist += pow(y[i] - x[i], 2);
  }
  // return dist;
  return sqrt(dist);
}

float * vectorAverage(float ** w, int lenx, int lenw) {
  float * av = calloc(lenx, sizeof(float));
  if (av == NULL) usage("vectorAverage : error malloc");

  for (size_t i = 0; i < lenw; i++) {
    for (size_t j = 0; j < lenx; j++) {
      av[j] += w[i][j]; // additionne ts les composantes
    }
  }
  for (size_t j = 0; j < lenx; j++) {
    av[j] /= lenw; // divises le total par le nombre de composantes
  }
  return av;
}

float ** create2Darray(int rows, int cols) {
  float ** cells = (float **) malloc(rows * sizeof(float *));
  if (cells == NULL) usage("getPoints : error malloc");

  for (size_t i = 0; i < rows; i++) {
    cells[i] = (float *) malloc(cols * sizeof(float));
    if (cells[i] == NULL) usage("getPoints : error malloc");
  }

  return cells;
}

void usage(char * error) {
  fprintf(stderr, "%s\n", error); // affiche le message
  exit(1);                        // quitter
}
