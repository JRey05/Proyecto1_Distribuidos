#include <stdio.h>
#include "ejercicio2b.h"

int main (int argc,char *argv[]) {
  CLIENT *clnt;
  float *result;
  char *server;
  struct timeval inicio,fin;
  char *args[]={"./EXEC",NULL};
  if (argc != 2) {
    printf ("Error cantidad de parametros.\n");
    exit(1);
  }
  server = argv[1];
  clnt = clnt_create(server,EJ2, EJ2VER1, "TCP");
  if(clnt == (CLIENT *) NULL) {
    printf("No hubo conexión\n");
    exit(1);
  }
  void *vacio;
  gettimeofday(&inicio,NULL);
  float *resultado = f1_1(vacio,clnt);
  gettimeofday(&fin,NULL);
  double tiempo = (double) (fin.tv_usec - inicio.tv_usec);
  printf("Tardo %f microsegundos\n", (float)tiempo);
  printf("anduvo todo joya, %f\n",*resultado);
}
