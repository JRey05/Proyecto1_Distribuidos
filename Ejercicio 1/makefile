.PHONY : all
all: ejercicio1 ejercicio1b
.PHONY : clean
clean :
	rm ejercicio1 ejercicio1b *.o
ejercicio1 : ejercicio1.o
	gcc -o ejercicio1 ejercicio1.o
ejercicio1.o : ejercicio1.c
	gcc -c ejercicio1.c
ejercicio1b : ejercicio1b.o
	gcc -o ejercicio1b ejercicio1b.o
ejercicio1b.o : ejercicio1b.c
	gcc -c ejercicio1b.c
