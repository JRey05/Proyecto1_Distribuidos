.PHONY: all
all: Ej5Cliente Ej5Servidor
.PHONY: clean
clean :
	rm Ej5Servidor Ej5Cliente Ej5_svc.c Ej5_xdr.c Ej5_clnt.c Ej5.h

Ej5Cliente: Ej5Cliente.c Ej5_clnt.c Ej5_xdr.c Ej5.h
	gcc -lnsl -o Ej5Cliente Ej5Cliente.c Ej5_clnt.c Ej5_xdr.c Ej5.h
Ej5Servidor: Ej5Servidor.c Ej5_svc.c Ej5_xdr.c Ej5.h
	gcc -lnsl -o Ej5Servidor Ej5Servidor.c Ej5_svc.c Ej5_xdr.c Ej5.h
Ej5_svc.c Ej5_xdr.c Ej5_clnt.c Ej5.h: Ej5.x
	rpcgen Ej5.x
