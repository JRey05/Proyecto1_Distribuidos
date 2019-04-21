#include "SumaArreglos.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
int main(int argc,char *argv[]) {
  CLIENT *clnt;
  char *server;
  nametype *resultado;
  nametype entrada;
  if (argc != 2) {
    printf ("Error cantidad de parametros.\n");
    exit(1);
  }
  server = argv[1];
  clnt = clnt_create(server,SUMAARREGLOS, VERSION1, "TCP");
  if(clnt == (CLIENT *) NULL) {
    printf("No hubo conexión\n");
    exit(1);
  }
  entrada = "ASDFASDF";
  resultado = cadena_1(&entrada,clnt);
  printf("%s",*resultado);
}
