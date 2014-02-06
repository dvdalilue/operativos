#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

/// IMPLEMENTACION DE UNA COLA ///
/// CON SUS FUNCIONES BASICAS ///

void cola_inic (tipoCola **c) {
  *c = (tipoCola *) malloc (sizeof(tipoCola));
  (**c).primero = NULL;
  (**c).ultimo = NULL;
  (**c).cantidad = 0;
}

int estaVacio(tipoCola *c) {
    if((*c).cantidad == 0) {
        return 1;
    }
    return 0;
}

void encolar (tipoCola* c, char* str) {
  tipoCaja* aux = (tipoCaja*) malloc (sizeof(tipoCaja));
  (*aux).elem = str;
  (*aux).siguiente = NULL;

  if ((*c).cantidad == 0) {
    (*c).primero = aux; 
    (*c).ultimo = aux;
  } else {
    (*((*c).ultimo)).siguiente = aux;
    (*c).ultimo = aux;
  }
  c->cantidad++;
}

char * desencolar (tipoCola* c) {
  tipoCaja *x;
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

void cola_finic(tipoCola **cola) {
  free(*cola);
}

