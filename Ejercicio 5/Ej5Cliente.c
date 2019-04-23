#include "Ej5.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include <time.h>
int main(int argc,char *argv[]) {
  CLIENT *clnt;
  char *server;
  if (argc != 2) {
    printf ("Error cantidad de parametros.\n");
    exit(1);
  }
  int opcion;
  printf("Ingrese el numero de la opción solicitada:\n\
  \t1: Numero decimal a binario.\n\
  \t2: Numero binario a hexadecimal.\n\
  \t3: Peso a dolar.\n\
  \t4: Peso a euro.\n\
  \t5: Hora del servidor.\n\
  \t6: Dia del servidor.\n\
  \t7: Sumar numeros.\n\
  \t8: Multiplicar numeros.\n");
  scanf("%i",&opcion);
  switch(opcion){
    case 1:{
      printf("Ingrese el numero:\n");
      scanf("%s\n", );
    }break;
    case 2:{}break;
    case 3:{}break;
    case 4:{}break;
    case 5:{}break;
    case 6:{}break;
    case 7:{}break;
    case 8:{}break;
  }
  /*
  server = argv[1];
  clnt = clnt_create(server,MINIOPS, VERSION1, "TCP");
  if(clnt == (CLIENT *) NULL) {
    printf("No hubo conexión\n");
    exit(1);
  }
  */
  return 0;
}
