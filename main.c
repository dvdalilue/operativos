#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>
#include "funciones.c"

int main (int argc, char *argv[]) {
  
  int i = 1, j;
  bool b = false;
  char input[200] = "";
  char act_input;

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

  printf("Introduzca nombre del directorio: ");

  j = 0;
  while (j < 200) {
    act_input = getchar();
    if(act_input != '\n') {
      input[j] = act_input;
    } else {
      break;
    }
    j++;
  }
  desDir(input,0,argv[i],b);
}
