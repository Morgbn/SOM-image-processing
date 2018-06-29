#include "utilities.h"

void rgb2hsv(float *rgb) {
  float R = rgb[0], G = rgb[1], B = rgb[2];
  float min, max, delta;

  R /= 255; G /= 255; B/= 255;

  min = fminf(R, fminf(G, B));
  max = fmaxf(R, fmaxf(G, B));

  delta = max - min;
  if (delta < 0.00001) { // noir/gris/blanc
    rgb[0] = 0; rgb[1] = 0; rgb[2] = min;
    return;
  }

  float d = (R==min) ? G-B : ((B==min) ? R-G : B-R);
  float h = (R==min) ? 3 : ((B==min) ? 1 : 5);

  rgb[0] = 60 * (h - d/delta);
  if( rgb[0] < 0.0 ) rgb[0] += 360.0;

  rgb[1] = delta/max;
  rgb[2] = max;
}

void hsv2rgb(float *hsv) {

  if (hsv[1] <= 0) {
    hsv[0] = hsv[1] = hsv[2];
    return;
  }

  float R,G,B, hh, f, v, p, q, t;
  hh = (hsv[0] >= 360.0) ? 0.0: hsv[0];
  hh /= 60.0;
  long i = (long) hh;
  f = hh - i;
  v = hsv[2];
  p = v * (1.0 - hsv[1]);
  q = v * (1.0 - f * hsv[1]);
  t = v * (1.0 - (1.0 - f) * hsv[1]);

  switch (i) {
    case 0: R = v, G = t, B = p; break;
    case 1: R = q, G = v, B = p; break;
    case 2: R = p, G = v, B = t; break;
    case 3: R = p, G = q, B = v; break;
    case 4: R = t, G = p, B = v; break;
    case 5: R = v, G = p, B = q; break;
  }

  hsv[0] = R*255; hsv[1] = G*255; hsv[2] = B*255;
}

float distEucl(float * x, float * y, int len) {
  float dist = 0;
  for (size_t i = 0; i < len; i++) {
    dist += pow(y[i] - x[i], 2);
  }
  // return dist;
  return sqrt(dist);
}

float * vectorAverage(float ** w, int lenx, int nx) {
  float * av = calloc(lenx, sizeof(float));
  if (av == NULL) usage("vectorAverage : error malloc");

  for (size_t i = 0; i < nx; i++) {
    for (size_t j = 0; j < lenx; j++) {
      av[j] += w[i][j]; // additionne ts les composantes
    }
  }
  for (size_t j = 0; j < lenx; j++) {
    av[j] /= nx; // divises le total par le nombre de composantes
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
