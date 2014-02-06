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
    printf("\nIntroduzca nombre del directorio: ");
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

bool file_exists(char * filename) {

  FILE * file;
  if (file = fopen(filename, "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
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
  tipoArgsHilo *aux;
  pthread_t pid;

  signal(SIGINT, &manejador_signal);

  while (i < argc) {
    if (strcmp(argv[i], "-r") == 0) {
      b = true;
    }
    else if (strcmp(argv[i], "-f") == 0) {
      i++;
      j = i;
    }
    i+=1;
  }

  if (argv[j] == NULL) {
    printf("\nERROR: No Se Especifico El Nombre De Archivo De Salida\n\n");
    exit(0);
  }

  while (counter < 2) {

    printf("\nIntroduzca nombre del directorio: ");
    dirs = 0;
    archs = 0;

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

    if (input[j-1] != 47) {
      input[j] = 47;
    }

    if (file_exists(argv[j]) == 1) {
      remove(argv[j]);
    }
    if (b == false) {
      desDir(input,0,argv[j],b,&dirs,&archs);
      numDir(input,archs,dirs);
      clean_array(input);
    } else {
      aux = crearVoid(input,0,argv[j],b,&dirs,&archs);
      if (pthread_create(&pid,NULL,desDirHilo,aux) != 0) {
	      perror("\nNo se pudo crear el hilo\n");
      }
      pthread_join(pid,NULL);  
      numDir(input,archs,dirs);
      clean_array(input);
    }
  }
}
