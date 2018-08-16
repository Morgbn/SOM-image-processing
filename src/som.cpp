#include "include/core.h"

float ** getPoints(png_bytep * rowImg, int * lenx, int *nx, int width, int height) {
  *nx = width * height;
  *lenx = 3; // R,G,B,(A)

  float ** cells = create2Darray(*nx, *lenx);

  int j = 0;
  for(int y = 0; y < height; y++) {
    png_bytep row = rowImg[y];
    for(int x = 0; x < width; x++) {
      png_bytep px = &(row[x * 4]); // un pixel = [R,G,B,A]
      for (int i = 0; i < *lenx; i++) cells[j][i] = px[i];
      j++;
    }
  }
  return cells;
}

float ** som(float ** allx, int lenx, int nx, int nw, QProgressBar *progressBar, int verbose) {
  // Normalisation de tous les vecteurs x de données
  normalizeAll(allx, nx, lenx);

  float * av = vectorAverage(allx, lenx, nx); // calcule la moyenne
  float ** w = create2Darray(nw, lenx);

 // connexions montantes wij aléatoires et non ordonnées
  for (int i = 0; i < nw; i++) {
    for (int j = 0; j < lenx; j++) {
      float min = (av[j]-.3 > 0) ? av[j]-.3 : 0;
      float max = (av[j]+.3 < 1) ? av[j]+.3 : 1;
      w[i][j] = randomFloat(min, max); // intervalle autour de la moyenne
    }
  }

  float N0 = nw/2;    // rayon initiale = 50% des neurones
  float NhdSize = N0;
  float a0 = .95;      // coefficient initiale d'apprentissage
  float coefA = a0;
  // int Nit = nx * 500; // nombre d'itérations
  int Nit = nx; // nombre d'itérations

  // phase 1
  int T = Nit;
  int t2 = 0; // pr la phase 2
  if (progressBar) {
    progressBar->setMinimum(0);
    progressBar->setMaximum(T);
  }
  for (int t = 0; t < T; t++) {
    float * x = allx[t % nx];

    // calcule de distance pour trouver le J*
    int bmuIndex = findBmuIndex(w, x, lenx, nw);

    // apprentissage
    // utiliser le rayon pour trouver les voisins
    for (int i = 0; i < nw; i++) { // pour chaque neurones
      float d = distEucl(w[i], w[bmuIndex], lenx); // distance j j*
      float hij = h(d, coefA);           // func de voisinage
      if (d < NhdSize) {
        for (int j = 0; j < lenx; j++) { // apprentissage
          w[i][j] += coefA * hij * (x[j] - w[i][j]);
        }
      }
    }

    decreaseA(&coefA, a0, t-t2, T);
    decreaseNhdSize(&NhdSize, N0, t, T);

    if (t == Nit/5) { // phase 2
      a0 = coefA = .1;
      if (verbose) printf("PHASE 2 %f\n", coefA);
      t2 = t;
    }

    if (progressBar) progressBar->setValue(t);
  }

  for (int i = 0; i < nw; i++)
    if (MY_HSV || MY_HSL || MY_HSVL)
      w[i][0] = floor(w[i][0] * 360);
    else
      for (int j = 0; j < lenx; j++) w[i][j] = floor(w[i][j] * 255);

  if (verbose) printf("FIN (%i iterations): a = %g; NhdSize = %g\n", Nit, coefA, NhdSize);
  return w;
}

void decreaseA(float * a, float a0, int t, int T) {
  *a = a0 * exp( -(double)t / T);
}

void decreaseNhdSize(float * NhdSize, int Nit, int t, int T) {
  *NhdSize = Nit * (1 - (1.0 * t) / T);
}

float h(float dist, float a) {
    return (float) exp((- dist * dist) / (2 * a * a));
}

int findBmuIndex(float ** w, float * x, int lenx, int lenw) {
  int bmuIndex = 0;
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

float ** getNei(float ** w, int bmuIndex, int r, int nw, int lenx, int * l) {
  float ** nei = create2Darray(2*r, lenx);              // allocation pr voisins
  int nNei = -1;                                        // nb de voisins
  for (int i = -r; i <= r; i++) {
    if (!i) continue;                                   // le bmu (l'exclure de la liste)
    if (bmuIndex + i < 0 || bmuIndex + i > nw) continue;
    nei[++nNei] = w[bmuIndex + i];
  }
  for (int i = nNei+1; i < 2*r; i++) free(nei[i]);   // libére espace non utilisé
  *l = nNei;                                            // nombre de voisins
  return nei;
}

void normalizeAll(float **w, int lenw, int lenx) {
  for (int i = 0; i < lenw; i++) {
    if (MY_HSV || MY_HSL)
      w[i][0] /= 360;
    else if (MY_HSVL) {
      w[i][0] /= 360;
      w[i][4] /= 255;
    }
    else for (int j = 0; j < lenx; j++) w[i][j] /= 255; // et le diviser par le maximum
  }
}
