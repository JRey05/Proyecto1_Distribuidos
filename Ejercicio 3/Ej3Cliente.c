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
    printf ("\nUso: ./Ej3Cliente ipServidor\n");
    exit(1);
  }
  server = argv[1];
  clnt = clnt_create(server,SUMAARREGLOS, VERSION1, "TCP");
  if(clnt == (CLIENT *) NULL) {
    printf("No hubo conexión\n");
    exit(1);
  }
  entrada = "ASDFASDF";
  double tiempo;
  double promedio=0;
  struct timeval inicio,final;
  int i;
  for (i=0;i<100;i++){
    //inicio el temporizador
    gettimeofday(&inicio,NULL);
    resultado = cadena_1(&entrada,clnt);
    //finalizo el temporizador
    gettimeofday(&final,NULL);
    tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
    promedio=promedio+tiempo;
  }
  promedio=promedio/100;

  printf("Resultado: %s\n",*resultado);
  printf("Tiempo que demoro: %.2f μs\n", promedio);
}
