#include "display.h"

void write2Darray(char * filename, float ** a, int x, int y) {
  FILE * fp = fopen(filename, "w");
  if (fp == NULL) usage("write2Darray : error creating the file");

  for (int yi = 0; yi < y; yi++) {
    for (int xi = 0; xi < x; xi++) {
      fprintf(fp, "%g\t", a[yi][xi]);
    }
    fprintf(fp, "\n");
  }
}

void print2Darray(char * format, float ** a, int lenx, int nx) {
  printf("[");

  for (int i = 0; i < nx; i++) {
    printf((i == 0) ? "  " : "   ");  // pour l'alignement  2 ou 3 espaces
    printVect(format, a[i], lenx, 0);
    printf((i+1 == nx) ? "" : ",\n");
  }

  printf("]\n");
}

void printVect(char * format, float * a, int len, int ret) {
  char format_dot[12];
  strcpy(format_dot, format);
  strcat(format_dot, ", ");

  printf("( ");
  for (int i = 0; i < len; i++)
    printf((i+1 == len) ? format : format_dot, a[i]); // avec ou sans virgule
  printf((ret) ? ")\n" : ")");
}

FILE * gnuplotInit() {
  FILE * gnuplot = popen("gnuplot -p", "w");
  return gnuplot;
}

void gnuplotGrid(FILE * gnuplot, float ** w, int nw, float ** allx, int nx) {
  fprintf(gnuplot, "plot [-.01:1.1][-.01:1.1] '-' with p pt 5 lt rgb \"red\", '-' with lines lt rgb \"green\"\n");
  // Points
  for (int i = 0; i < nx; i++)
    fprintf(gnuplot, "%g %g\n", allx[i][0], allx[i][1]);
  fprintf(gnuplot, "e\n");
  // Grid
  int size = sqrt(nw);
  for (int i = 0; i < nw; i++) {
    if (i+size < nw) {
      fprintf(gnuplot, "%g %g\n", w[i][0], w[i][1]);
      fprintf(gnuplot, "%g %g\n\n", w[i+size][0], w[i+size][1]);
    }
    if (i+1 < nw && (i+1) % size) {
      fprintf(gnuplot, "%g %g\n", w[i][0], w[i][1]);
      fprintf(gnuplot, "%g %g\n\n", w[i+1][0], w[i+1][1]);
    }
  }
  fprintf(gnuplot, "e\n");
  fprintf(gnuplot, "pause 0.00001\n");
}

void gnuplotShowVars(FILE * gnuplot, int t, float coefA, float NhdSize) {
  fprintf(gnuplot, "unset label\n");
  fprintf( gnuplot,
    "set label \"%i: a = %g, NhdSize = %g\" at graph 0.2,0.9 font \"Helvetica,20\"\n",
    t, coefA, NhdSize );
}
