#ifndef funciones
#define funciones
#define NOMBRE_ARCHIVO "tiradas_"

int drandom(int jugador, int semilla);
void crearArchivo(int jugador,int tiradas);
void imprimirTirada(int dados,int jugador,int numTirada);
void imprimirTotal(int total,int jugador);
int dados(int jugador, int tiradas, int semilla);

#endif
