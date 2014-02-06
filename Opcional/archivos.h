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

void imprimirArchivo(char *dir, int i, int j, int nivel, char *salida);
void anexarArchivo(char * buffer);
void leerArchivo(pthread_t nombre, int boolean);