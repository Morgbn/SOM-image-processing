#include "include/mainwindow.h"
#include "include/som.h"
#include <QApplication>

int MY_HSV, MY_HSL, MY_HSVRGB, MY_HSVL, makeTransparent, nw;

int main(int argc, char *argv[]) {
  /* DEF GLOBAL - par défaut : */
  MY_HSV = 1;              // utilisé l'espace HSV
  MY_HSL = MY_HSVRGB = MY_HSVL = 0;
  makeTransparent = 0;     // ne pas mettre l'arriére plan transparent
  nw = 2;                  // segmenter l'image en 2 couleurs

  if (argc > 3) { // terminal version
    if (strcmp(argv[1], "-T")) {
      fprintf(stderr, "%s: option non reconnue\n", argv[1]);
    }
    else {
      if (argc > 5 && !strcmp(argv[4], "-t")) // mettre le bg transparent ou pas
        makeTransparent = (argv[5][0] == '1') ? 1 : 0;
      if (argc > 6 && !strcmp(argv[6], "-n")) // choisir le nombre de neurones
        nw = atoi(argv[7]);
      if (argc > 8) { // changer le mode de traitement
        MY_HSV = MY_HSL = MY_HSVRGB = MY_HSVL = 0;
        if (!strcmp(argv[8], "HSV")) MY_HSV = 1;
        else if (!strcmp(argv[8], "HSL")) MY_HSL = 1;
        else if (!strcmp(argv[8], "HSVRGB")) MY_HSVRGB = 1;
        else if (!strcmp(argv[8], "HSVL")) MY_HSVL = 1;
      }
      return editImg(argv[2], argv[3], nw, NULL, 0);
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
  fprintf(stderr, "%s [-T] [imageIn.png] [imageOut.png] [-t (0|1)] [-n (nombre)] [mode(HSV|HSL|HSVRGB|HSVL)]\n", argv[0]);
  return 1;
}
