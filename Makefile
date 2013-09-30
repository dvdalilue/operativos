#MakeFile
#Universidad Simon Bolivar
#Autor: David Lilue
#Carnet: 09-10444

CC = gcc
MAIN = main.c
DEPS = funciones.h queue.h
OBJS = funciones.o queue.o main.o

arbol: $(OBJS)
	$(CC) -ggdb $(MAIN) -o $@ 

%.o: %.c $(DEPS)
	$(CC) -c $<

check-syntax:
	$(CC) -o nul -S ${CHK_SOURCES}

clean:
	\rm -f *.o *.out *.txt arbol nul