.PHONY: all
all: Ej7Cliente Ej7Servidor
.PHONY: clean
clean :
	rm Ej7Servidor Ej7Cliente Ej7_svc.c Ej7_xdr.c Ej7_clnt.c Ej7.h

Ej7Cliente: Ej7Cliente.c Ej7_clnt.c Ej7_xdr.c Ej7.h
	gcc -lnsl -o Ej7Cliente Ej7Cliente.c Ej7_clnt.c Ej7_xdr.c Ej7.h
Ej7Servidor: Ej7Servidor.c Ej7_svc.c Ej7_xdr.c Ej7.h
	gcc -lnsl -o Ej7Servidor Ej7Servidor.c Ej7_svc.c Ej7_xdr.c Ej7.h
Ej7_svc.c Ej7_xdr.c Ej7_clnt.c: Ej7.x
	rpcgen Ej7.x
