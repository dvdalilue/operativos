#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>
#include "funciones.c"

int main (int argc, char *argv[]) {
  
  int i = 1;
  bool b = false;

  while (i < argc) {
    if (strcmp(argv[i], "-r") == 0) {
      b = true;
    }
    else if (strcmp(argv[i], "-f") == 0) {
      i++;
      break;
    }
    i+=1;
  }
  desdir(argv[i],0);
}
