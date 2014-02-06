#include <stdio.h>
#include <string.h>
#include "funciones.h"

int drandom(int jugador, int semilla) {
  int i;
  i = (rand()*jugador*semilla);
  i+=jugador;
  return abs(i);
}

void crearArchivo(int jugador,int tiradas){
  FILE *fd;
  char buffer[30];
  sprintf(buffer,"%s%d%s",NOMBRE_ARCHIVO,jugador,".txt");
  fd = fopen(buffer,"w");
  if (fd!= NULL) {
    sprintf(buffer,"%s%d%s","Jugador: ",jugador,"\n");
    fprintf(fd,"%s",buffer);
    sprintf(buffer,"%s%d%s","Numero de Tiradas: ",tiradas,"\n");
    fprintf(fd,"%s",buffer);
    fclose(fd);
  }
}

void imprimirTirada(int dados,int jugador,int numTirada){
  FILE *fd;
  char buffer[30];
  sprintf(buffer,"%s%d%s",NOMBRE_ARCHIVO,jugador,".txt");
  fd = fopen(buffer,"a");
  if (fd!=NULL){
    sprintf(buffer,"%s%d%s%d%s","Tirada ",numTirada,": ",dados,"\n");
    fprintf(fd,"%s",buffer);
    fclose(fd);
  }
}

void imprimirTotal(int total,int jugador){
  FILE *fd;
  char buffer[30];
  sprintf(buffer,"%s%d%s",NOMBRE_ARCHIVO,jugador,".txt");
  fd = fopen(buffer,"a");
  if (fd!=NULL){
    sprintf(buffer,"%s%d","TOTAL:   ",total);
    fprintf(fd,"%s",buffer);
    fclose(fd);
  }
}


int dados(int jugador, int tiradas, int semilla){
  int i = 1,j,k = 0;
  crearArchivo(jugador,tiradas);
  while (i <= tiradas) {
    j = (drandom(jugador,semilla)%11);
    j++;
		j++;
    k+=j;
    imprimirTirada(j,jugador,i);
    i++;
  }
  imprimirTotal(k,jugador);
	return(k);
}

