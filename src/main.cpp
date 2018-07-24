#include "include/mainwindow.h"
#include "include/som.h"
#include <QApplication>

int MY_HSV, MY_HSL, MY_HSVRGB, MY_HSVL;

int main(int argc, char *argv[]) {
  /* DEF GLOBAL */
  MY_HSV = 1; // utilisé l'espace HSV par défaut
  MY_HSL = MY_HSVRGB = MY_HSVL = 0;

  if (argc > 3) { // terminal version
    if (strcmp(argv[1], "-T")) {
      fprintf(stderr, "%s: option non reconnue\n", argv[1]);
    }
    else {
      if (argc > 4) { // changer le mode de traitement
        MY_HSV = MY_HSL = MY_HSVRGB = MY_HSVL = 0;
        if (!strcmp(argv[4], "HSV")) MY_HSV = 1;
        else if (!strcmp(argv[4], "HSL")) MY_HSL = 1;
        else if (!strcmp(argv[4], "HSVRGB")) MY_HSVRGB = 1;
        else if (!strcmp(argv[4], "HSVL")) MY_HSVL = 1;
      }
      return editImg(argv[2], argv[3], NULL, 0);
    }
  }
  else {          // gui version
    QApplication app(argc, argv);
    QDesktopWidget dw;
    MainWindow w;
    w.setFixedSize(dw.width()*(.5/dw.screenCount()), dw.height()*.5); // fenetre 25% * 50% de l'écran principale
    w.show();
    return app.exec();
  }
  fprintf(stderr, "%s [-T] [imageIn.png] [imageOut.png] [mode(HSV|HSL|HSVRGB|HSVL)]\n", argv[0]);
  return 1;
}
