#include <time.h>
#include "include/core.h"
#include "include/display.h"
#include "include/randomize.h"
#include "include/utilities.h"

/**
 * Ouvrir/Editer/Enregistrer une image png
 * @param  fin     nom du png à ouvrir
 * @param  fout    nom pour l'Enregistrer
 * @param  verbose
 * @return         0->pas d'erreur, 1->erreur
 */
int editImg(const char * fin, const char * fout, int verbose);
