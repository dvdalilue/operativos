
#include <stdlib.h>
#include <stdio.h>
#include "funciones.c"

void phelp () {
  printf("\njuegodedados_p: imprime una secuencia de numeros aleatorios\nSINTAXIS:\njuegodedados_p [-n i] [-s x] [-h]\n-n i: tamano de la secuencia (por defecto, 10)\n-s x: semilla (por defecto, 1)\n-j y: numero de jugadores\n-h: imprime esta ayuda y sale\n\n");
  exit(0);
}

void verif(int i, int argc) {
  if (i >= argc-1) {
    phelp();
  }
}

void main (int argc, char *argv[]) {
  int i = 1, numero = 10, jugadores = 0, semilla = 1, status, ganador, resultado = 0;
  pid_t hijo;

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

  i = 1;
  while (i <= jugadores) {

    if ((hijo = fork()) < 0) {
      perror("fork:");
      exit(1);  
    }

    if (hijo == 0) {
      dados(i,numero,semilla);
      exit(0);
    }
    i++;
  }
  
  for (i = 0; i<jugadores; i++){
    wait(&status);
  }

  i = 1;
  while (i <= jugadores) {
    status = encontrarPuntaje(i, numero);
    if (resultado < status) {
      resultado = status;
      ganador = i;
    }
    i++;
  }

  printf("Numero de tiradas: %d\nSemilla: %d\nJugadores: %d\n**** Gana el jugador %d, con %d puntos\n",numero, semilla,jugadores,ganador,resultado);

  

}
