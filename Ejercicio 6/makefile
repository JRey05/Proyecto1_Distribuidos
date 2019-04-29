.PHONY: all
all: pt6AgenciaA pt6AgenciaB pt6cliente
.PHONY: clean
clean :
	rm pt6AgenciaA pt6AgenciaB pt6cliente
pt6cliente : pt6cliente.c
	gcc -o pt6Cliente pt6cliente.c
pt6AgenciaA : pt6AgenciaA.c
	gcc -o pt6AgenciaA pt6AgenciaA.c
pt6AgenciaB : pt6AgenciaB.c
	gcc -o pt6AgenciaB pt6AgenciaB.c
