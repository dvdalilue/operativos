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

void impEsp(int nivel) {
  int i = 0;
  while (i < nivel) {
    printf("  ");
    i++;
  }
}

void impDir(char *dir, int i, int j, int nivel) {
  impEsp(nivel);
  printf("Directorio: %s\n",dir);
  impEsp(nivel);
  printf("Numero de archivos normales: %d\n",i);
  impEsp(nivel);
  printf("Numero de directorios: %d\n",j);
}

void desDir(char *dir, int nivel) {
  
  DIR *aux;
  char esDir = 0x4, *aux_dir;
  struct dirent *dir_ls;
  tipoCola *cola;
  int i = 0, j = 0, k;

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
    impDir(dir,i,j,nivel);
    while (!estaVacio(cola)) {
      aux_dir = desencolar(cola);
      desDir(aux_dir,nivel+1);
      free(aux_dir);
    }
    cola_finic(&cola);
  }
}
