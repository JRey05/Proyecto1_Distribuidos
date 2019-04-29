.PHONY : all
all: ejercicio2a
ejercicio2a : ejercicio2a.o
	gcc -o ejercicio2a ejercicio2a.o
ejercicio2a.o : ejercicio2a.c EXEC
	gcc -c ejercicio2a.c
EXEC : EXEC.o
	gcc -o EXEC EXEC.c
EXEC.o : EXEC.c
	gcc -c EXEC.c
