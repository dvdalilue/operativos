
#include <stdlib.h>
#include <stdio.h>
#include "lista.c"

void main (int argc, char *argv[]) {
  FILE *archivo;
  char *cadena;
  tipoLista *list;

  archivo = fopen(argv[1], "r");

  if (archivo == NULL) {
    printf("El Nombre Del Archivo No Existe En El Directorio\n");
    exit(0);
  }

  lista_inic(&list);

  while(feof(archivo) == 0) {
    cadena = (char*) malloc (sizeof(char*));
    if (fscanf(archivo,"%s",cadena) == 1) {
      agregarRep(list, cadena);
    }
  }

  imprimirLista(list);

  fclose(archivo);
}
