.PHONY :all
all: Ej3Cliente Ej3Servidor
.PHONY : clear
Ej3Cliente: Ej3Cliente.o SumaArreglos_clnt.o SumaArreglos_xdr.o SumaArreglos.h
	gcc -lnsl -o Ej3Cliente Ej3Cliente.o SumaArreglos_clnt.o SumaArreglos_xdr.o
Ej3Cliente.o: Ej3Cliente.c
	gcc -c Ej3Cliente.c
SumaArreglos_clnt.o: SumaArreglos_clnt.c
	gcc -c SumaArreglos_clnt.c
SumaArreglos_xdr.o: SumaArreglos.c
	gcc -c SumaArreglos_xdr.c
Ej3Servidor: Ej3Servidor.o SumaArreglos_svc.o SumaArreglos_xdr.o SumaArreglos.h
	gcc -lnsl -o Ej3Servidor Ej3Servidor.o SumaArreglos_svc.o SumaArreglos_xdr.o
Ej3Servidor.o: Ej3Servidor.c
	gcc -c Ej3Servidor.c
SumaArreglos_svc.o: SumaArreglos_svc.c
	gcc -c SumaArreglos_svc.c
SumaArreglos_svc.c SumaArreglos_xdr.c SumaArreglos_clnt.c: SumaArreglos.x
	rpcgen SumaArreglos.x
