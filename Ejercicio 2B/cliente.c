#include <stdio.h>
#include "ejercicio2b.h"

int main (int argc,char *argv[]) {
  CLIENT *clnt;
  float *result;
  char *server;
  struct timeval inicio,fin;
  char *args[]={"./EXEC",NULL};
  if (argc != 2) {
    printf ("Uso:   ./cliente servidor\n");
    exit(1);
  }
  server = argv[1];
  clnt = clnt_create(server,EJ2, EJ2VER1, "TCP");
  if(clnt == (CLIENT *) NULL) {
    printf("No hubo conexión\n");
    exit(1);
  }
  void *vacio;
  int i;
  double tiempo;
  double promedio=0;
  for (i=0;i<100;i++){
    gettimeofday(&inicio,NULL);
    float *resultado = f1_1(vacio,clnt);
    gettimeofday(&fin,NULL);
    tiempo = (double) ((fin.tv_sec * 1000000 - inicio.tv_sec * 1000000) + (fin.tv_usec - inicio.tv_usec));
    promedio=promedio+tiempo;
  }
  promedio=promedio/100;
  printf("Tardo %f μs\n", (float)promedio);
}
