#include "som.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL)); // initialise rand

  int nx = 0;   // nombres de capteurs
  int nw = 3*3;   // nombres de neurones
  int lenx = 0; // taille des capteurs

  if (argc < 2) usage("need a filename");
  float ** allx = getPoints((char *) argv[1], &nx, &lenx);

  // Normalisation de tous les vecteurs x de données
  normalizeAll(allx, nx, lenx);


 #if GNUPLOT
  if (lenx != 2) usage("gnuplotGrid: 2D seulement (3D non implémenté)!");
  FILE * gnuplot = gnuplotInit();
 #endif

  float * av = vectorAverage(allx, lenx, nx); // calcule la moyenne
  float ** w = create2Darray(nw, lenx);

 #if NOGRID  // pas de grille : connexions montantes wij aléatoires et non ordonnées
  for (size_t i = 0; i < nw; i++) {
    for (size_t j = 0; j < lenx; j++) {
      float min = (av[j]-.3 > 0) ? av[j]-.3 : 0;
      float max = (av[j]+.3 < 1) ? av[j]+.3 : 1;
      w[i][j] = randomFloat(min, max); // intervalle autour de la moyenne
    }
  }
 #else       // grille : connexions montantes wij aléatoires mais ordonnées
  int row = sqrt(nw); // nombre de ligne
  float min, max, dist[lenx];
  for (size_t j = 0; j < lenx; j++) {
    min = (av[j]-.15 > 0) ? av[j]-.15 : 0;
    max = (av[j]+.15 < 1) ? av[j]+.15 : 1;
    dist[j] = (max - min) / row;
  }

  int * dim = malloc(lenx * sizeof(int));
  dim[1] = 1;
  for (size_t i = 0; i < nw; i++) {
    dim[0] = (i % row) + 1;
    for (int j = 0; j < lenx; j++) {
      w[i][j] = randomFloat(min + dist[j] * dim[j], min + dist[j] * (dim[j]+1)); // les positionner en carré, espacées aléatoirement
      // w[i][j] = dist[j] * dim[j]; // les positionner en carré, espacée non aléatoirement
    }
    for (int j = 0; j < lenx; j++) {
      if (! (dim[j] % row)) dim[j+1]++; // passer à la nouvelle 'ligne' pour la dimensions supérieur
    }
  }
  free(dim);
 #endif

  float N0 = nw/2;    // rayon initiale = 50% des neurones
  float NhdSize = N0;
  float a0 = .95;      // coefficient initiale d'apprentissage
  float coefA = a0;
  int Nit = nx * 500; // nombre d'itérations

  // phase 1
  int T = Nit;
  int t2 = 0; // pr la phase 2
  for (size_t t = 0; t < T; t++) {
    // shuffleVects(allx, nx); // mélanger les vecteurs
    // for (size_t k = 0; k < nx; k++) {
    //   float * x = allx[k];
    float * x = allx[t % nx];
    // float * x = allx[randomInt(0, nx)];

    // calcule de distance pour trouver le J*
    int bmuIndex = findBmuIndex(w, x, lenx, nw);

    // apprentissage
   #if NOGRID  // utiliser le rayon pour trouver les voisins
    for (size_t i = 0; i < nw; i++) { // pour chaque neurones
      float d = distEucl(w[i], w[bmuIndex], lenx); // distance j j*
      float hij = h(d, coefA, NhdSize); // func de voisinage
      if (d < NhdSize) {
        for (size_t j = 0; j < lenx; j++) { // apprentissage
          w[i][j] += coefA * hij * (x[j] - w[i][j]);
        }
      }
    }
   #else       // voisins selon une grille
    int lenv;                                           // nombre de voisins
    float ** nei = getNei(w, bmuIndex, ceil(NhdSize), nw, lenx, &lenv); // voisins
    for (size_t i = 0; i < lenv; i++) {
      float d   = distEucl(nei[i], w[bmuIndex], lenx);  // distance j j*
      float hij = h(d, coefA, NhdSize);                 // func de voisinage
      for (size_t j = 0; j < lenx; j++) {               // apprentissage
        nei[i][j] += coefA * hij * (x[j] - nei[i][j]);
      }
    }
   #endif

    decreaseA(&coefA, a0, t-t2, T);
    decreaseNhdSize(&NhdSize, N0, t, T);

    // }
    if (t == Nit/5) { // phase 2
      a0 = coefA = .1;
      printf("PHASE 2 %f\n", coefA);
      t2 = t;
    }
    #if GNUPLOT
     if (t > Nit-500) { // afficher les 2000 dernières iterations
       gnuplotShowVars(gnuplot, t, coefA, NhdSize);
       gnuplotGrid(gnuplot, w, nw, allx, nx);
     }
    #endif
  }
  print2Darray("%g", w, lenx, nw);
  printf("FIN (%i iterations): a = %g; NhdSize = %g\n", Nit, coefA, NhdSize);

  write2Darray("normalized.txt", allx, lenx, nx);
  write2Darray("data.txt", w, lenx, nw);
  return 0;
}
