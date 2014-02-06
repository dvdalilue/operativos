//Universidad Simon Bolivar
//Autor: David Lilue       - Carnet: 09-10444
//       F. Miguel Saraiva - Carnet: 09-10794

#ifndef funciones
#define funciones

/// Declaracion de tipoArgsHilo ///

typedef struct _argsHilo {
  char *dir;
  int nivel;
  char *salida;
  bool b;
  int *numDirs;
  int *numArchs;
} tipoArgsHilo;

/// Declaracion de todas las funciones ///

void impDir(char *dir, int i, int j, int nivel, char *salida);
void impEsp(int nivel);
void impEspFile(int nivel, FILE *fp);
void desDir(char *dir, int nivel, char *salida, int *dirs, int *archs);
void* crearVoid (char *dir, int nivel, char *salida, bool b, int *dirs, int *archs);
void* desDirHilo(void *arg);


#endif
