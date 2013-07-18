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
    fprintf(fd,buffer);
    sprintf(buffer,"%s%d%s","Numero de Tiradas: ",tiradas,"\n");
    fprintf(fd,buffer);
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
    fprintf(fd,buffer);
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
    fprintf(fd,buffer);
    fclose(fd);
  }
}

int encontrarPuntaje(int jugador, int numero){
  FILE *fd;
  char buffer[30];
  int i = 0;
  sprintf(buffer,"%s%d%s",NOMBRE_ARCHIVO,jugador,".txt");

  fd = fopen(buffer,"r");
  
  while (i <= numero+2) {
    fgets(buffer,30,fd);
    i++;
  }
  
  return atoi(&buffer[9]);
}

void dados(int jugador, int tiradas, int semilla){
  int i = 1,j,k = 0;
  crearArchivo(jugador,tiradas);
  while (i <= tiradas) {
    j = (drandom(jugador,semilla)%12);
    j++;
    k+=j;
    imprimirTirada(j,jugador,i);
    i++;
  }
  imprimirTotal(k,jugador);
}

