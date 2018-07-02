#include "include/display.h"

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

void print2Darray(const char * format, float ** a, int lenx, int nx) {
  printf("[");

  for (int i = 0; i < nx; i++) {
    printf((i == 0) ? "  " : "   ");  // pour l'alignement  2 ou 3 espaces
    printVect(format, a[i], lenx, 0);
    printf((i+1 == nx) ? "" : ",\n");
  }

  printf("]\n");
}

void printVect(const char * format, float * a, int len, int ret) {
  char format_dot[12];
  strcpy(format_dot, format);
  strcat(format_dot, ", ");

  printf("( ");
  for (int i = 0; i < len; i++)
    printf((i+1 == len) ? format : format_dot, a[i]); // avec ou sans virgule
  printf((ret) ? ")\n" : ")");
}
