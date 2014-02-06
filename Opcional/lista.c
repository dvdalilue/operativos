//Universidad Simon Bolivar
//Autor: David Lilue       - Carnet: 09-10444
//       F. Miguel Saraiva - Carnet: 09-10794

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>




int listaVacio(listaCabeza *cabeza){
  if (cabeza->cantidad == 0){
    return(1);
  } else {
    return(0);
  }
}

listaCabeza* crearCabeza(){
  listaCabeza *aux;
  aux = malloc(sizeof(listaCabeza));
  aux->primero = NULL;
  aux->ultimo = NULL;
  aux->cantidad = 0;
}

void agregarLista(listaCabeza* cabeza, pthread_t elem){
  tipoLista *aux;
  aux = malloc(sizeof(tipoLista));
  
  aux->elem = elem;
  aux->siguiente = NULL;
  
  if (cabeza->cantidad == 0) {
    cabeza->primero = aux;
    cabeza->ultimo = aux;
  } else if (cabeza->cantidad > 0) {
    cabeza->ultimo->siguiente = aux;
    cabeza->ultimo = aux;
  } else {
    perror("\nLISTA CON CANTIDAD NEGATIVA\n");
    exit(1);
  }
  
  cabeza->cantidad ++;
}


tipoLista * obtenerLista(listaCabeza *cabeza){
  tipoLista *aux; 
  aux = cabeza->primero;
  cabeza->primero = aux->siguiente;
  cabeza->cantidad --;
  aux->siguiente = NULL;
  return(aux);
}
  
  