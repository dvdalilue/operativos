#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"


void lista_inic (tipoLista **c) {
  *c = (tipoLista *) malloc (sizeof(tipoLista));
  (**c).primero = NULL;
  (**c).ultimo = NULL;
  (**c).cantidad = 0;
}

int estaVacia(tipoLista *c) {
    if((*c).cantidad == 0) {
        return 1;
    }
    return 0;
}

void agregar (tipoLista* c, char* str) {
  tipoCaja* aux = (tipoCaja*) malloc (sizeof(tipoCaja));
  (*aux).elem = str;
  (*aux).anterior = NULL;
  (*aux).siguiente = NULL;

  if ((*c).cantidad == 0) {
    (*c).primero = aux; 
    (*c).ultimo = aux;
  } else {
    (*((*c).ultimo)).siguiente = aux;
    (*aux).anterior = (*c).ultimo;
    (*c).ultimo = aux;
  }
  (*c).cantidad++;
}

void agregarRep (tipoLista* c, char* str) {
  tipoCaja* aux;
  char *cad;
  int num;

  if ((*c).cantidad == 0) {
    aux = (tipoCaja*) malloc (sizeof(tipoCaja)); 
    (*aux).elem = str;
    (*aux).count = 1;
    (*aux).siguiente = NULL;
    (*aux).anterior = NULL;
    (*c).primero = aux; 
    (*c).ultimo = aux;
  } else {
    aux = (*c).primero;
    while ((aux != NULL) && (strcmp((*aux).elem, str) != 0)) {
      aux = (*aux).siguiente;
    }
    if (aux != NULL) {
      (*aux).count++;
      intercambio((*aux).anterior,aux);
    } else {
      aux = (tipoCaja*) malloc (sizeof(tipoCaja)); 
      (*aux).elem = str;
      (*aux).count = 1;
      (*aux).siguiente = NULL;
      (*aux).anterior = (*c).ultimo;
      (*((*c).ultimo)).siguiente = aux;
      (*c).ultimo = aux;
    }
  }
  (*c).cantidad++;
}

void intercambio(tipoCaja *izq, tipoCaja *der) {
  char *aux;
  int num;
  while(izq != NULL) {
    if ((*izq).count < (*der).count) {      
      num = (*izq).count;
      aux = (*izq).elem;
      (*izq).count = (*der).count;
      (*izq).elem = (*der).elem;
      (*der).count = num;
      (*der).elem = aux;
    }
    (izq) = (*izq).anterior;
    (der) = (*der).anterior;
  }
}

void imprimirLista (tipoLista *c) {
  tipoCaja *aux = (*c).primero;

  while (aux != NULL) {
    printf("%s %d\n", (*aux).elem, (*aux).count);
    aux = (*aux).siguiente;
  }
}
