#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>
#include "funciones.c"

int counter = 0;

void manejador_signal(int sig) {
  if (counter == 0) {
    printf("\n\nSe ha habilitado la interrupción con SIGINT\n");
    fflush(stdout);
  }
  if (counter == 1) {
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%I:%M%p del %d de %B de %Y",tlocal);
    printf("\narbol: termina al recibir dos SIGINT, a las %s\n\n",output);
    exit(0);
  }
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
  
  int i = 1, j, dirs, archs;
  bool b = false;
  char input[200] = "";
  char act_input;

  signal(SIGINT, &manejador_signal);

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
    dirs = 0;
    archs = 0;

    j = 0;
    while (j < 200 && counter == 0) {
      act_input = getchar();
      if(act_input != '\n') {
	input[j] = act_input;
      } else {
	break;
      }
      j++;
    }
    if (counter == 0) {
    desDir(input,0,argv[i],b,&dirs,&archs);
    numDir(input,archs,dirs);
    clean_array(input);
    }
  }

  while (counter < 2) {
    continue;
  }
}
