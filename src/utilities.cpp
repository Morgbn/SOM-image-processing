#include "include/utilities.h"

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

void rgb2hsl(float *rgb) {
  float r = rgb[0]/255, g = rgb[1]/255, b = rgb[2]/255;

  float min = fminf(r, fminf(g, b));
  float max = fmaxf(r, fmaxf(g, b));
  float h, s, l = (max + min) / 2;

  float d = max - min;
  if (d < 0.00001) { // noir/gris/blanc
    h = s = 0;
  } else {
    s = l > 0.5 ? d / (2 - max - min) : d / (max + min);

    if (max == r) h = (g - b) / d + (g < b ? 6 : 0);
    else if (max == g) h = (b - r) / d + 2;
    else if (max == b) h = (r - g) / d + 4;
    h /= 6;
  }

   rgb[0] = h*360; rgb[1] = s; rgb[2] = l;
}

float hue2rgb(float v1, float v2, float vH) {
	if (vH < 0) vH += 1;
	if (vH > 1) vH -= 1;
	if ((6 * vH) < 1) return (v1 + (v2 - v1) * 6 * vH);
	if ((2 * vH) < 1) return v2;
	if ((3 * vH) < 2) return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);
	return v1;
}

void hsl2rgb(float *hsl) {
  float h = hsl[0], s = hsl[1], l = hsl[2];
  float r, g, b;

  if (s == 0) {
    r = g = b = l * 255; // achromatic
  } else {
    float v1, v2;
		float hue = h / 360;

		v2 = (l < 0.5) ? (l * (1 + s)) : ((l + s) - (l * s));
		v1 = 2 * l - v2;

		r = hue2rgb(v1, v2, hue + (1.0f / 3));
		g = hue2rgb(v1, v2, hue);
		b = hue2rgb(v1, v2, hue - (1.0f / 3));
  }
  hsl[0] = r*255; hsl[1] = g*255; hsl[2] = b*255;
}

float distEucl(float * x, float * y, int len) {
  float dist = 0;
  for (int i = 0; i < len; i++) {
    dist += pow(y[i] - x[i], 2);
  }
  // return dist;
  return sqrt(dist);
}

float * vectorAverage(float ** w, int lenx, int nx) {
  float * av = (float *) calloc(lenx, sizeof(float));
  if (av == NULL) usage("vectorAverage : error malloc");

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < lenx; j++) {
      av[j] += w[i][j]; // additionne ts les composantes
    }
  }
  for (int j = 0; j < lenx; j++) {
    av[j] /= nx; // divises le total par le nombre de composantes
  }
  return av;
}

float ** create2Darray(int rows, int cols) {
  float ** cells = (float **) malloc(rows * sizeof(float *));
  if (cells == NULL) usage("getPoints : error malloc");

  for (int i = 0; i < rows; i++) {
    cells[i] = (float *) malloc(cols * sizeof(float));
    if (cells[i] == NULL) usage("getPoints : error malloc");
  }

  return cells;
}

void usage(const char * error) {
  fprintf(stderr, "%s\n", error); // affiche le message
  exit(1);                        // quitter
}
