.PONY : all
all: ejercicio1 ejercicio1b ejercicio2a ejercicio2b
.PHONY : clean
objects = ejercicio1 ejercicio2a EXEC *.o
.PHONY : ejercicio2b
clean :
	rm $(objects)
ejercicio1 : ejercicio1.o
	gcc -o ejercicio1 ejercicio1.o
ejercicio1.o : ejercicio1.c
	gcc -c ejercicio1.c
ejercicio1b : ejercicio1b.o
	gcc -o ejercicio1b ejercicio1b.o
ejercicio1b.o : ejercicio1b.c
	gcc -c ejercicio1b.c
ejercicio2a : ejercicio2a.o
	gcc -o ejercicio2a ejercicio2a.o
ejercicio2a.o : ejercicio2a.c EXEC
	gcc -c ejercicio2a.c
EXEC : EXEC.o
	gcc -o EXEC EXEC.c
EXEC.o : EXEC.c
	gcc -c EXEC.c
ejercicio2b : cliente servidor
cliente : cliente.o ejercicio2b_clnt.o ejercicio2b.h
	gcc -lnsl -o cliente cliente.o ejercicio2b_clnt.o
cliente.o: cliente.c
	gcc -c cliente.c
ejercicio2b_clnt.o : ejercicio2b_clnt.c
	gcc -c ejercicio2b_clnt.c
servidor : servidor.o ejercicio2b_svc.o ejercicio2b.h
	gcc -lnsl -o servidor servidor.o ejercicio2b_svc.o
servidor.o : servidor.c
	gcc -c servidor.c
ejercicio2b_svc.o : ejercicio2b_svc.o
	gcc -c ejercicio2b_svc.c
ejercicio2b_svc.c ejercicio2b_clnt.c ejercicio2b.h : ejercicio2b.x
	rpcgen ejercicio2b.x