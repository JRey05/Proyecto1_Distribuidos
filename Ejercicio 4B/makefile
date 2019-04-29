.PHONY: all
all: pt4sv_b pt4client_b
.PHONY: clean
clean :
	rm pt4client_b pt4sv_b
pt4sv: pt4sv_b.c
	gcc -o pt4sv_b pt4sv_b.c
pt4client: pt4client_b.c
	gcc -o pt4client_b pt4client_b.c
