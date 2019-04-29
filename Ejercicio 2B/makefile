.PHONY : all
all: EXEC ejercicio2b cliente servidor
.PHONY : clean
clean :
	rm *.o
ejercicio2b : cliente servidor
cliente : cliente.c ejercicio2b_clnt.c ejercicio2b.h
	gcc -ltirpc -I/usr/include/tirpc -o cliente cliente.c ejercicio2b_clnt.c
servidor : servidor.c ejercicio2b_svc.c ejercicio2b.h
	gcc -ltirpc -I/usr/include/tirpc -o servidor servidor.c ejercicio2b_svc.c
ejercicio2b_svc.c ejercicio2b_clnt.c ejercicio2b.h : ejercicio2b.x
	rpcgen ejercicio2b.x
