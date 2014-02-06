#MakeFile
#Universidad Simon Bolivar
#Autor: David Lilue
#Carnet: 09-10444


juegodedados_h: funciones.o main.o
	gcc funciones.o main.o -lm -lpthread -o juegodedados_h

funciones.o: funciones.c
	gcc -c funciones.c -lpthread
#lista.o: lista.c
#	gcc -c lista.c -lpthread
main.o: main.c
	gcc -c main.c -lpthread

clean: 
	rm -f *.o juegodedados_h