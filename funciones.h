#ifndef funciones
#define funciones

void impDir(char *dir, int i, int j, int nivel, char *salida);
void impEsp(int nivel);
void impEspFile(int nivel, FILE *fp);
void desDir(char *dir, int nivel, char *salida, bool b, int *dirs, int *archs);

#endif
