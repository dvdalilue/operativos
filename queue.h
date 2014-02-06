#ifndef queue
#define queue

typedef struct _caja {
  char* elem;
  struct _caja *siguiente;
} tipoCaja;

typedef struct _cola {
  struct _caja *primero;
  struct _caja *ultimo;
  int cantidad;
} tipoCola;

void cola_inic (tipoCola** c);
int estaVacio (tipoCola* c);
void encolar (tipoCola* c, char* str);
char * desencolar (tipoCola* c);
void cola_finic(tipoCola **cola);

#endif
