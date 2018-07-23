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
    else return editImg(argv[2], argv[3], NULL, 0);
  }
  else {          // gui version
    QApplication app(argc, argv);
    QDesktopWidget dw;
    MainWindow w;
    w.setFixedSize(dw.width()*(.5/dw.screenCount()), dw.height()*.5); // fenetre 25% * 50% de l'écran principale
    w.show();
    return app.exec();
  }
  fprintf(stderr, "%s [-T] [imageIn.png] [imageOut.png]\n", argv[0]);
  return 1;
}
