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

void impEsp(int nivel) {
  int i = 0;
  while (i < nivel) {
    printf("  ");
    i++;
  }
}

void desdir(char *dir, int nivel) {
  
  DIR *aux;
  char esDir = 0x4, *aux_dir;
  struct dirent *dir_ls;
  int i = 0, j = 0;

  aux = opendir(dir);
  if (aux == NULL) {
    perror("*No puedo abrir el directorio!!");
  } else {
    while ((dir_ls = readdir(aux)) != NULL) {
      if ((*dir_ls).d_type == esDir) {
	if (strcmp((*dir_ls).d_name,".") != 0 && strcmp((*dir_ls).d_name,"..") != 0) {

	  aux_dir = (char *) malloc (sizeof(dir)+70);
	  strcpy(aux_dir,dir);
	  strcat(aux_dir,(*dir_ls).d_name);
	  strcat(aux_dir,"/");

	  desdir(aux_dir,nivel+1);

	  free(aux_dir);
	  j++;
	}
      } else {
	i++;
      }
    }
  
  impEsp(nivel);
  printf("Directorio: %s\n",dir);
  impEsp(nivel);
  printf("Numero de archivos normales: %d\n",i);
  impEsp(nivel);
  printf("Numero de directorios: %d\n",j);
  }
}

void buscadir() {
  printf("\n");
}

/* void cmd_ls(char* patron) { */
  
/*   int b = 0; */
/*   unsigned char esDir =0x4; */
/*   char *aux_patron; */
/*   DIR  *dir;  */
/*   struct dirent *dir_ls; */
/*   struct stat info_ls; */
/*   struct passwd *user_arc; */
/*   struct group *group_arc; */
/*   time_t tmp; */
/*   char aux[80]; */
/*   struct tm *t_aux; */

/*   dir = opendir(patron); */
/*   if (dir == NULL) { */
/*     perror("No puedo abrir el directorio"); */
/*   } else { */

/*     while ((dir_ls = readdir(dir)) != NULL) { */
/*       aux_patron = (char *) malloc (sizeof(patron)+100); */
/*       strcpy(aux_patron,patron); */
/*       if (dir_ls->d_type == esDir) { */
/* 	strcat(aux_patron,dir_ls->d_name); */
/* 	strcat(aux_patron,"/"); */
/* 	stat(aux_patron,&info_ls); */
/* 	user_arc = getpwuid(info_ls.st_uid); */
/* 	group_arc = getgrgid(info_ls.st_gid); */
/* 	tmp = info_ls.st_atime; */
/* 	t_aux = localtime(&tmp); */
/* 	strftime(aux,sizeof(aux), "%b %d %R", t_aux); */

/* 	permisos(info_ls, user_arc, group_arc, dir_ls, aux); */
/*       } else { */
/* 	strcat(aux_patron,dir_ls->d_name); */
/* 	stat(aux_patron,&info_ls); */
/* 	user_arc = getpwuid(info_ls.st_uid); */
/* 	group_arc = getgrgid(info_ls.st_gid); */
/* 	tmp = info_ls.st_atime; */
/* 	t_aux = localtime(&tmp); */
/* 	strftime(aux,sizeof(aux), "%b %d %R", t_aux); */
         
/* 	permisos(info_ls, user_arc, group_arc, dir_ls, aux); */
/*       } */
/*       free(aux_patron); */
/*     } */
/*     b = 0; */
/*   } */
/* } */
