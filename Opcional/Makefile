#MakeFile
#Universidad Simon Bolivar
#Autor: David Lilue       - Carnet: 09-10444
#       F. Miguel Saraiva - Carnet: 09-10794
CC = gcc
MAIN = main.c
DEPS = funciones.h queue.h archivos.h lista.h
OBJS = funciones.o queue.o archivos.o lista.o main.o

arbol: $(OBJS)
	$(CC) -ggdb $(MAIN) -lpthread -o $@ 

%.o: %.c $(DEPS)
	$(CC) -c $<

check-syntax:
	$(CC) -o nul -S ${CHK_SOURCES}

clean:
	\rm -f *.o *.out *.txt arbol nul