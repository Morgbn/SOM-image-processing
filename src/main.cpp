#include "include/mainwindow.h"
#include "include/som.h"
#include <QApplication>

int MY_HSV, MY_HSL, MY_HSVRGB, MY_HSVL, makeTransparent, nw, postProcess;

void changeOption(int i, char *argv[]) {
  if (!strcmp(argv[i], "-t"))      // mettre le bg transparent ou pas
    makeTransparent = (argv[i+1][0] == '1') ? 1 : 0;
  else if (!strcmp(argv[i], "-n")) // choisir le nombre de neurones
    nw = atoi(argv[i+1]);
  else if (!strcmp(argv[i], "-p")) // aplliquer du post process ou pas
    postProcess = atoi(argv[i+1]);
}

int main(int argc, char *argv[]) {
  /* DEF GLOBAL - par défaut : */
  MY_HSV = MY_HSL = MY_HSVRGB = MY_HSVL = 0; // utiliser l'espace RGB
  postProcess = 1;         // retouche final
  makeTransparent = 0;     // ne pas mettre l'arriére plan transparent
  nw = 2;                  // segmenter l'image en 2 couleurs

  if (argc > 1) { // terminal version
    if (strcmp(argv[1], "-T")) {
      fprintf(stderr, "%s: option non reconnue\n", argv[1]);
    }
    else {
      if (argc > 8) changeOption(8, argv); // 3eme option
      if (argc > 6) changeOption(6, argv); // 2eme option
      if (argc > 4) changeOption(4, argv); // 1er option
      // changer le mode de traitement
      if (!strcmp(argv[argc-1], "HSL")) MY_HSL = 1;
      else if (!strcmp(argv[argc-1], "HSVRGB")) MY_HSVRGB = 1;
      else if (!strcmp(argv[argc-1], "HSVL")) MY_HSVL = 1;
      if (!strcmp(argv[argc-1], "HSL")) MY_HSL = 1;

      if (argc > 3) return editImg(argv[2], argv[3], nw, NULL, 0);
    }
  }
  else {          // gui version
    QApplication app(argc, argv);
    QDesktopWidget dw;
    MainWindow w;
    w.resize(dw.width()*(.5/dw.screenCount()), dw.height()*.5); // fenetre 25% * 50% de l'écran principale
    w.show();
    return app.exec();
  }
  fprintf(stderr, "%s [-T] [imageIn.png] [imageOut.png] [-t (0|1)] [-n (number)] [-p (0|1)] [mode(HSV|HSL|HSVRGB|HSVL)]\n", argv[0]);
  return 1;
}
