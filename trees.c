#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

void cola_arb_inic (tipoColaArb **c) {
  *c = (tipoColaArb *) malloc (sizeof(tipoColaArb));
  (**c).primero = NULL;
  (**c).ultimo = NULL;
  (**c).cantidad = 0;
}

int estaVacio(tipoColaArb *c) {
    if((*c).cantidad == 0) {
        return 1;
    }
    return 0;
}

void encolar (tipoColaArb* c, char *dir, int numArchs, int numDirs) {
  tipoArbol* aux = (tipoArbol*) malloc (sizeof(tipoArbol));
  
  (*aux).dir = dir;
  (*aux).numArchs = numArchs;
  (*aux).numDirs = numDirs;
  (*aux).siguiente = NULL;
  (*aux).hijos = cola_arb_inic(&((*aux).hijos));

  if ((*c).cantidad == 0) {
    (*c).primero = aux; 
    (*c).ultimo = aux;
  } else {
    (*((*c).ultimo)).siguiente = aux;
    (*c).ultimo = aux;
  }
  c->cantidad++;
}

nodo * desencolar (tipoColaArb* c) {
  tipoArbol *x;
  char *ret;
  if ((*c).cantidad != 0) {
    x = (*c).primero;
    ret = (*x).elem;
    x = (*x).siguiente;
    free((*c).primero);
    (*c).primero = x;
    c->cantidad--;

    return ret;
  }
  return NULL;
}

void cola_finic(tipoColaArb **cola) {
  free(*cola);
}

