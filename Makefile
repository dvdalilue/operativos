#MakeFile
#Universidad Simon Bolivar
#Autor: David Lilue
#Carnet: 09-10444

CC = gcc
OPS = -ggdb -O3
MAIN = main.c
DEPS = 
OBJS = main.o

frecpal: $(OBJS)
	$(CC) $(OPS) $(MAIN) -o $@ 

%.o: %.c $(DEPS)
	$(CC) $(OPS) -c $<

check-syntax:
	$(CC) -o nul -S ${CHK_SOURCES}

clean:
	\rm -f *.o *.out frecpal nul

