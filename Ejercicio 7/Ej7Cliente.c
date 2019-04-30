#include "Ej7.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include <time.h>

/*
  Para medir la variacion con respecto al reloj servidor:
    1. El cliente envia su hora actual
    2. El servidor la recibe y compara con la propia, de esta manera tenemos que t1= dif de relojes + tiempo de envio.
    3. El servidor envia su hora actual junto con la diferencia calculada anteriormente.
    4. El cliente  la recibe y compara con la propia, de esta manera tenemos que t2= -dif de relojes + tiempo de envio.
    5. Se calcula las diferenceias de los relojes como (t1-t2)/2,
     si reemplazamos [dif de relojes + tiempo de envio - (-dif de relojes + envio)]/2 = diferencia de relojes
    6. Se itera 10000 veces y se calcula el promedio para conseguir una medicion mas exacta.
*/

int main(int argc,char *argv[]) {
  CLIENT *clnt;
  char *server;
  spectime tCliente;
  struct timespec tCli;
  clockid_t clk_id=CLOCK_REALTIME;
  struct respuesta *t1;
  long int t2,suma=0;
  if (argc < 2) {
    printf ("Error cantidad de parametros.\n");
    exit(1);
  }
  int j;
  for (j=0; j<argc-1; j++)
  {
    server = argv[1+j];
    clnt = clnt_create(server,SYNCCLOCK, VER1, "TCP");
    if(clnt == (CLIENT *) NULL) {
      printf("No hubo conexión\n");
      exit(1);
    }
    sincronizar_1((&tCliente),clnt);    //Descarta los tiempos de la primer medicion, son poco confiables.
    int i;
    for(i=0;i<10000;i++){
      clock_gettime(clk_id, (&tCli));
      tCliente.tv_sec = (long) tCli.tv_sec;
      tCliente.tv_nsec = tCli.tv_nsec;
      t1 = sincronizar_1((&tCliente),clnt);
      clock_gettime(clk_id, (&tCli));
      t2 = (long) ((tCli.tv_sec * 1000000000 + tCli.tv_nsec) - (t1->tSv.tv_sec * 1000000000 + t1->tSv.tv_nsec));
      suma+=(t2-t1->t1)/2;
    }
    printf("DifReloj con el servidor %i =%li nanosegundos\n",j+1,suma/10000);
  }
}
