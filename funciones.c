#include "funciones.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
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

void impEspFile(int nivel, FILE *fp) {
  int i = 0;
  while (i < nivel) {
    fprintf(fp, "  ");
    i++;
  }
}

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

void desDir(char *dir, int nivel, char *salida, bool b, int *dirs, int *archs) {
  
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
    impDir(dir,i,j,nivel,salida);
    *dirs = *dirs + j;
    *archs = *archs + i;

    while (!estaVacio(cola)) {
      aux_dir = desencolar(cola);
      desDir(aux_dir,nivel+1,salida,b,dirs,archs);
      free(aux_dir);
    }
    cola_finic(&cola);
  }
}


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


void* desDirHilo(void *arg) {
  DIR *aux;
  char esDir = 0x4, *aux_dir;
  struct dirent *dir_ls;
  tipoCola *cola;
  int i = 0, j = 0, k, result;
  pthread_t id;
  void* auxiliar1;
  tipoArgsHilo* info;

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
    *info->numDirs = *info->numDirs + j;
    *info->numArchs = *info->numArchs + i;

    while (!estaVacio(cola)) {
      aux_dir = desencolar(cola);
      auxiliar1 = (crearVoid(aux_dir,(info->nivel)+1,info->salida,info->b,info->numDirs,info->numArchs));
     result = pthread_create(&id,NULL,desDirHilo,auxiliar1);
     pthread_join(id,NULL);
     free(aux_dir);
     free(info);
    }
    cola_finic(&cola);
  }
 pthread_exit(0);
}