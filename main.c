
#include <stdlib.h>
#include <stdio.h>

void phelp () {
  printf("juegodedados_p: imprime una secuencia de numeros aleatorios\nSINTAXIS:\njuegodedados_p [-n i] [-s x] [-h]\n-n i: tamano de la secuencia (por defecto, 10)\n-s x: semilla (por defecto, 1)\n-j y: numero de jugadores\n-h: imprime esta ayuda y sale\n");
  exit(0);
}


void main (int argc, char *argv[]) {
  int i = 0, numero = 1, jugadores = 10, semilla = 1;

  while (i < argc) {
    if (strcmp(argv[i], "-n") == 0) {
      numero = atoi(argv[i+1]);
    }
    else if (strcmp(argv[i], "-j") == 0) {
      jugadores = atoi(argv[i+1]);
    }
	
    else if (strcmp(argv[i], "-s") == 0) {
      semilla = atoi(argv[i+1]);
    }
    
    else if (strcmp(argv[i], "-h") == 0) {
      phelp();
    }
    i++;
  }

  printf("numero:%d\nsemilla:%d\njuga..:%d\n",numero,semilla,jugadores);
}
