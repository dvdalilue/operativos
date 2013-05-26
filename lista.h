#ifndef lista
#define lista

typedef struct _caja {
  char* elem;
  int count;
  struct _caja *anterior;
  struct _caja *siguiente;
} tipoCaja;

typedef struct _lista {
  struct _caja *primero;
  struct _caja *ultimo;
  int cantidad;
} tipoLista;

void lista_inic (tipoLista **c);
int estaVacia (tipoLista *c);
void agregar (tipoLista *c, char *str);
void agregarRep (tipoLista *c, char *str);
void intercambio(tipoCaja *izq, tipoCaja *der);
void imprimirLista (tipoLista *c);

#endif
