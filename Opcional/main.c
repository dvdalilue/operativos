//Universidad Simon Bolivar
//Autor: David Lilue       - Carnet: 09-10444
//       F. Miguel Saraiva - Carnet: 09-10794

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>
#include "funciones.c"

//// Declaracion de Unica variable global para las seniales /////
int counter = 0;

//// Manejador de seniales, que captura CRT-C y varia su accion /////
//// dependiendo de cuantas veces se haya presionado /////

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

//// Funcion que verifica si un archivo existe /////
//// en el directorio, retornando true en acierto /////
//// false en caso de fallo /////

bool file_exists(char * filename) {

  FILE * file;
  if (file = fopen(filename, "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

//// Funcion que vacia un arreglo de char /////
//// sustituye todo con \0 /////

void clean_array(char *input) {
  int i;

  for (i = 0; i < 200 && input[i] != '\0'; i++) {
    input[i] = '\0';
  }
}

//// Funcion que realiza impresion de los totales /////
//// al final del recorrido de los directorios /////
//// ya sea en el archivo y por pantalla /////

void numDir(char *input, int i, int j, char *salida) {
  FILE *fp;

  fp=fopen(salida, "a");
  fprintf(fp, "\nNumero total de archivos normales bajo %s: %d\n",input,i);
  fprintf(fp, "Numero total de directorios bajo %s: %d\n",input,j);

  fclose(fp);

  printf("\nNumero total de archivos normales bajo %s: %d\n",input,i);
  printf("Numero total de directorios bajo %s: %d\n",input,j);
}

//// Funcion MAIN, que captura todo desde el principio /////
//// verificando tipo de ejecucion y archivo de salida /////

int main (int argc, char *argv[]) {

  /// Declaracion de variables ///
  
  int i = 1, j, k = 0, dirs, archs;
  bool b = false;
  char input[200] = "";
  char act_input;
  char nombre[25];
  tipoArgsHilo *aux;
  pthread_t pid;

  /// Permite manejar la senial de CRT-C ///

  signal(SIGINT, &manejador_signal);

  /// Reconocimiento de flags y nombre del archivo ///
  /// de salida, ademas de casos borde que no ///
  /// especifican bien en la ejecucion ///

  while (i < argc) {
    if (strcmp(argv[i], "-r") == 0) {
      b = true;
    }
    else if (strcmp(argv[i], "-f") == 0) {
      i++;
      k = i;
    }
    i+=1;
  }

  if (argv[k] == NULL || strcmp(argv[k],"./arbol") == 0) {
    printf("\nERROR: No Se Especifico El Nombre De Archivo De Salida\n\n");
    exit(0);
  }

  /// Ciclo que permite la solicitud de varios ///
  /// directorios hasta que se hagan 2 CRT-C ///

  while (counter < 2) {

    printf("\nIntroduzca nombre del directorio: ");
    dirs = 0;
    archs = 0;

    /// Captura del directorio a buscar ///

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

    /// Coloca el '/' en caso de no estar ///

    if (input[j-1] != 47) {
      input[j] = 47;
    }

    /// Si ya existe el archivo de salida ///
    /// con el mismo nombre, si esta ///
    /// lo elimina para crear uno nuevo ///

    if (file_exists(argv[k]) == 1) {
      remove(argv[k]);
    }

    /// Separa los tipos de ejecucion ///
    /// dependiendo de lo que se haya ///
    /// solicitado por el terminal ///
    /// ya sea concurrente con hilos ///
    /// o la version normal ///

    if (b == false) {
      desDir(input,0,argv[k],&dirs,&archs);
      numDir(input,archs,dirs,argv[k]);
      clean_array(input);
    } else {
      aux = crearVoid(input,0,argv[k],b,&dirs,&archs);
      if (pthread_create(&pid,NULL,desDirHilo,aux) != 0) {
	      perror("\nNo se pudo crear el hilo\n");
      }
      pthread_join(pid,NULL);
      leerArchivo(pid,1);
      sprintf(nombre,"%u",pid);
      numDir(input,archs,dirs,nombre);
      rename(nombre,argv[k]);
      unlink(nombre);
      clean_array(input);
    }
  }
}

