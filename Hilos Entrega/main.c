#include "funciones.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct elem{
	int jugador;
	int tiradas;
	int semilla;
} elementos;

void *imprimir(void *arg){
	elementos *aux;
	int *total;
	total = malloc(sizeof(int));
	aux = (elementos*)(arg);
	*total = dados(aux->jugador,aux->tiradas,aux->semilla);
	pthread_exit((void*)total);
}

void phelp () {
  printf("\njuegodedados_p: imprime una secuencia de numeros aleatorios\n");
  printf("SINTAXIS:\njuegodedados_p [-n i] [-s x] [-h]\n-n i: tamano de la");
  printf(" secuencia (por defecto, 10)\n-s x: semilla (por defecto, 1)\n-j ");
  printf("y: numero de jugadores\n-h: imprime esta ayuda y sale\n\n");
  exit(0);
}

void verif(int i, int argc) {
  if (i >= argc-1) {
    phelp();
  }
}

int main(int argc,char* argv[]){
	void *total;
	int mayor,i = 1, numero = 10, jugadores = 0, semilla = 1, status, result;
  pid_t hijo;
	elementos *arregloElem;
	int *totales;
	pthread_t arregloId[jugadores];
	
  while (i < argc) {
      if (strcmp(argv[i], "-n") == 0) {
	verif(i, argc);
	if ((numero = abs(atoi(argv[i+1]))) == 0) {
	  printf("**** El valor de las jugadas no es valido\n");
	  exit(0);
	}
      }
      else if (strcmp(argv[i], "-j") == 0) {
	verif(i, argc);
	if ((jugadores = abs(atoi(argv[i+1]))) == 0) {
	  printf("**** El valor de los jugadores no es valido\n");
	  exit(0);
	}
      }
      else if (strcmp(argv[i], "-s") == 0) {
	verif(i, argc);
	if ((semilla = abs(atoi(argv[i+1]))) == 0) {
	  printf("**** El valor de la semilla no es valido\n");
	  exit(0);
	}
      }
      else {
	phelp();
      }
      i+=2;
  }
  if (numero > 20) {
    printf("**** Numero de tiradas es mayor a 20\n");
    exit(0);
  }
  else if (jugadores == 0) {
    printf("**** No especifico el numero de jugadores\n");
    exit(0);
  }
	
	printf("Numero de tiradas: %d\n",numero);
	printf("Semilla: %d\n",semilla);
	printf("Jugadores: %d\n",jugadores);
	
	arregloElem = malloc(sizeof(elementos)*jugadores);
	totales = malloc(sizeof(int)*jugadores);
	srand(semilla);
	for (i=0;i<jugadores;i++){
		arregloElem[i].semilla = rand();
		arregloElem[i].jugador = i+1;
		arregloElem[i].tiradas = numero;
	};
	printf("Jugadores -> %d\n",jugadores);
	for (i=0;i<jugadores;i++){
		result = pthread_create(&arregloId[i],NULL,imprimir,&(arregloElem[i]));
		pthread_join(arregloId[i],&total);
		totales[i] = *(int*)total;
	}
	mayor = 0;
	for (i=0;i<jugadores;i++){
		if (totales[mayor]<=totales[i]){
			mayor = i;
		};
	}
	printf("**** Gana el jugador %d, con %d puntos\n",(mayor+1),totales[mayor]);
}
