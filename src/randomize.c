#include "randomize.h"

void shuffleVects(float ** a, int len) {
  float * tmp;
  int n;

  for (int i = 0; i < len; i++) {
    n = randomInt(0, len); // prend un index aléaléatoirement
    tmp  = a[i];
    a[i] = a[n];                    // échange les pointeurs a[i] et a[n]
    a[n] = tmp;
  }
}

int randomInt(int min, int max) {
  return rand() % (max - min) + min;
}

float randomFloat(float min, float max) {
  return (rand() / (float) RAND_MAX) * (max - min) + min;
}
