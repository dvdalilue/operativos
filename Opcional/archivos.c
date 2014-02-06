//Universidad Simon Bolivar
//Autor: David Lilue       - Carnet: 09-10444
//       F. Miguel Saraiva - Carnet: 09-10794

#include "archivos.h"


void imprimirArchivo(char *dir, int i, int j, int nivel, char *salida){
  FILE *fp;
  char nombre[25];
  
  sprintf(nombre,"%u",(pthread_self()));
  fp=fopen(nombre, "w");  
  if (fp==NULL) {
    fputs ("File error",stderr);
    exit (1);
  }
  impEspFile(nivel, fp);
  fprintf(fp, "Directorio: %s\n",dir);
  impEspFile(nivel, fp);
  fprintf(fp, "Numero de archivos normales: %d\n",i);
  impEspFile(nivel, fp);
  fprintf(fp, "Numero de directorios: %d\n",j);
  fclose(fp);
}

void anexarArchivo(char * buffer){
  FILE * fp;
  char nombre[25];
  
  sprintf(nombre,"%u",pthread_self());
  fp=fopen(nombre, "a");  
  if (fp==NULL) {
    fputs ("File error",stderr);
    exit (1);
  }
  fprintf(fp,"%s",buffer);
  fclose(fp);
}

void leerArchivo(pthread_t archivo,int boolean){
  FILE * fp;
  long tamano;
  char * buffer;
  size_t result;
  char nombre[25];

  sprintf(nombre,"%u",archivo);
  fp = fopen (nombre,"r");
  if (fp==NULL) {
    fputs ("File error",stderr);
    exit (1);
  }

  fseek (fp , 0, SEEK_END);
  tamano = ftell(fp);
  rewind(fp);
  
  buffer = (char*) malloc (sizeof(char)*tamano);
  if (buffer == NULL) {
    fputs ("Memory error",stderr);
    exit (2);
  }

  result = fread(buffer,1,tamano,fp);
  if (result != tamano) {
    fputs ("Reading error",stderr);
    exit (3);
  }
  
  fclose (fp);
  anexarArchivo(buffer);
  if (boolean == 1){
    printf("%s",buffer);
  }
  free (buffer);
}