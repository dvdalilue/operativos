//Universidad Simon Bolivar
//Autor: David Lilue       - Carnet: 09-10444
//       F. Miguel Saraiva - Carnet: 09-10794

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "queue.c"
#include "funciones.h"
#include "lista.c"
#include "archivos.c"

/// Funcion que inserta espacios para ///
/// que la impresion sea la deseada ///
/// dependiendo del nivel del directorio ///

void impEsp(int nivel) {
  int i = 0;
  while (i < nivel) {
    printf("  ");
    i++;
  }
}

/// Funcion que inserta espacios para ///
/// que la impresion sea la deseada ///
/// dependiendo del nivel del directorio ///
/// en el archivo de salida ///

void impEspFile(int nivel, FILE *fp) {
  int i = 0;
  while (i < nivel) {
    fprintf(fp, "  ");
    i++;
  }
}

/// Funcion que realiza la imprsion de toda la ///
/// informacion ya sea en el archivo o el terminal ///

void impDir(char *dir, int i, int j, int nivel, char *salida) {
  FILE *fp;

  fp=fopen(salida, "a");
  impEspFile(nivel, fp);
  fprintf(fp, "Directorio: %s\n",dir);
  impEspFile(nivel, fp);
  fprintf(fp, "Numero de archivos normales: %d\n",i);
  impEspFile(nivel, fp);
  fprintf(fp, "Numero de directorios: %d\n",j);

  fclose(fp);

  impEsp(nivel);
  printf("Directorio: %s\n",dir);
  impEsp(nivel);
  printf("Numero de archivos normales: %d\n",i);
  impEsp(nivel);
  printf("Numero de directorios: %d\n",j);
}

/// Funcion principal para la version normal ///
/// del recorrido de los directorios de forma ///
/// recursiva haciendo uso de una cola para ///
/// guardar los directorios hijos para luego ///
/// aplicar esta misma funcion en ellos ///

void desDir(char *dir, int nivel, char *salida, int *dirs, int *archs) {
  
  /// Declaracion de variables ///

  DIR *aux;
  char esDir = 0x4, *aux_dir;
  struct dirent *dir_ls;
  tipoCola *cola;
  int i = 0, j = 0, k;

  /// Primera apertura del directorio ///
  /// en busca de los directorios hijos ///
  /// cantidad de archivos ///

  aux = opendir(dir);
  if (aux == NULL) {
    perror("*No puedo abrir el directorio!!");
  } else {
    cola_inic(&cola);
    while ((dir_ls = readdir(aux)) != NULL) {
      if ((*dir_ls).d_type == esDir) {
	if (strcmp((*dir_ls).d_name,".") != 0 && strcmp((*dir_ls).d_name,"..") != 0) {
	  aux_dir = (char *) malloc (sizeof(dir)+200);
	  strcpy(aux_dir,dir);
	  strcat(aux_dir,(*dir_ls).d_name);
	  strcat(aux_dir,"/");
	  encolar(cola,aux_dir);
	  j++;
	} 
      } else {
	i++;
      }
    }
    closedir(aux);
    impDir(dir,i,j,nivel,salida);
    *dirs = *dirs + j;
    *archs = *archs + i;

    /// Llamada recursiva para los hijos ///

    while (!estaVacio(cola)) {
      aux_dir = desencolar(cola);
      desDir(aux_dir,nivel+1,salida,dirs,archs);
      free(aux_dir);
    }
    cola_finic(&cola);
  }
}


/// Funcion principal para el recorrido de ///
/// los directorios para la version de hilos ///

void* crearVoid (char *dir, int nivel, char *salida, bool b, int *dirs, int *archs) {
  tipoArgsHilo *aux;

  aux = malloc(sizeof(tipoArgsHilo));
  aux->dir = dir;
  aux->nivel = nivel;
  aux->salida = salida;
  aux->b = b;
  aux->numDirs = dirs;
  aux->numArchs = archs;
  return ((void*)(aux));
}

/// Funcion que inicializa estructura para ///
/// la version de hilos, necesaria para la ///
/// creacion de los mismos ///

void* desDirHilo(void *arg) {
  DIR *aux;
  char esDir = 0x4, *aux_dir;
  struct dirent *dir_ls;
  tipoCola *cola;
  int i = 0, j = 0, k, result;
  pthread_t id;
  void* auxiliar1;
  tipoArgsHilo* info;
  char nombre[25];
  listaCabeza *cabeza;
  tipoLista *auxiliar2;
  
  info = (tipoArgsHilo*)(arg);
  aux = opendir(info->dir);
  if (aux == NULL) {
    perror("*No puedo abrir el directorio!!");
  } else {
    cola_inic(&cola);
    while ((dir_ls = readdir(aux)) != NULL) {
      if ((*dir_ls).d_type == esDir) {
	if (strcmp((*dir_ls).d_name,".") != 0 && strcmp((*dir_ls).d_name,"..") != 0) {
	  aux_dir = (char *) malloc (sizeof(info->dir)+200);
	  strcpy(aux_dir,info->dir);
	  strcat(aux_dir,(*dir_ls).d_name);
	  strcat(aux_dir,"/");
	  encolar(cola,aux_dir);
	  j++;
	}
      } else {
	i++;
      }
    }
    closedir(aux);
    impDir(info->dir,i,j,info->nivel,info->salida);
    imprimirArchivo(info->dir,i,j,info->nivel,info->salida);
    
    *info->numDirs = *info->numDirs + j;
    *info->numArchs = *info->numArchs + i;
    
    i = 0;
    cabeza = crearCabeza();
    while (!estaVacio(cola)) {
      aux_dir = desencolar(cola);
      auxiliar1 = (crearVoid(aux_dir,(info->nivel)+1,info->salida,info->b,info->numDirs,info->numArchs));
      result = pthread_create(&id,NULL,desDirHilo,auxiliar1);
      if (result != 0) {
        perror("\nNO SE CREO EL HILO\n");
	exit(1);
      }
      agregarLista(cabeza,id);
      i++;
      free(aux_dir);
    }
    cola_finic(&cola);
    while (listaVacio(cabeza) == 0){ 
      auxiliar2 = obtenerLista(cabeza);
      pthread_join(auxiliar2->elem);
      leerArchivo(auxiliar2->elem,0);
      remove(auxiliar2->elem);
      free(auxiliar2);
    }
  }
 pthread_exit(0);
}
