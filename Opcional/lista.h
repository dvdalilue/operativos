//Universidad Simon Bolivar
//Autor: David Lilue       - Carnet: 09-10444
//       F. Miguel Saraiva - Carnet: 09-10794

#ifndef lista
#define lista

#include <signal.h>

typedef struct _elemento {
  pthread_t elem;
  struct _elemento *siguiente;
} tipoLista;

typedef struct _cabeza{
  struct _elemento *primero;
  struct _elemento *ultimo;
  int cantidad;
} listaCabeza;

int listaVacio(listaCabeza *elem);
listaCabeza*  crearCabeza();
void agregarLista(listaCabeza *lista, pthread_t elem);
tipoLista * obtenerLista(listaCabeza *elem);

#endif
