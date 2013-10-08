#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>
#include "funciones.c"

int counter = 0;

void manejador_signal(int sig) {
  printf("Se ha habilitado la interrupción con SIGINT");
  counter++;
}

void clean_array(char *input) {
  int i;

  for (i = 0; i < 200 && input[i] != '\0'; i++) {
    input[i] = '\0';
  }
}

void numDir(char *input, int i, int j) {
  printf("\nNumero total de archivos normales bajo %s: %d\n",input,i);
  printf("Numero total de directorios bajo %s: %d\n",input,j);
}

int main (int argc, char *argv[]) {
  
  int i = 1, j, dirs = 0, archs = 0;
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

  while (counter < 1) {

    printf("\nIntroduzca nombre del directorio: ");

    signal(SIGINT, manejador_signal);

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
    desDir(input,0,argv[i],b,&dirs,&archs);
    numDir(input,i,j);
    clean_array(input);
  }

  while (counter < 2) {
    continue;
  }
}
