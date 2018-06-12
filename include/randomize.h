#ifndef RANDOMIZE_INCLUDED
#define RANDOMIZE_INCLUDED

#include <stdlib.h>

/**
 * Mélange un vecteur de vecteurs de float
 * @param a   vecteurs à mélanger
 * @param len taille du vecteur
 */
void shuffleVects(float ** a, int len);

/**
 * Générateur de nombres aléatoires
 * @return un nombres compris entre [min; max[
 */
float randomFloat(float min, float max);

/**
 * Générateur de flottants aléatoires
 * @param  min borne inférieur comprise
 * @param  max borne supérieur exclue
 * @return un flottant compris entre [min; max[
 */
int randomInt(int min, int max);

#endif
