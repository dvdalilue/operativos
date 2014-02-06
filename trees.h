#ifndef queue
#define queue


typedef struct _colaArb {
  struct _arbol *primero;
  struct _arbol *ultimo;
  int cantidad;
} tipoColaArb;

typedef struct _arbol {
  char *dir;
  int numArchs;
  int numDirs;
  struct _arbol *siguiente;
  struct _colaArb *hijos;
} tipoArbol;

void cola_inic (tipoCola** c);
int estaVacio (tipoCola* c);
void encolar (tipoCola* c, char* str);
char * desencolar (tipoCola* c);
void cola_finic(tipoCola **cola);


#endif
