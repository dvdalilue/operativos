#ifndef funciones
#define funciones
#include <stdbool.h>
#include <stdio.h>

typedef struct _argsHilo {
  char*	dir;
  int nivel;
  char *salida;
  bool b;
  int* numDirs;
  int* numArchs;
} tipoArgsHilo;

void impDir(char *dir, int i, int j, int nivel, char *salida);
void impEsp(int nivel);
void impEspFile(int nivel, FILE *fp);
void desDir(char *dir, int nivel, char *salida, bool b, int *dirs, int *archs);
void* crearVoid (char *dir, int nivel, char *salida, bool b, int *dirs, int *archs);
void* desDirHilo(void *arg);

#endif
