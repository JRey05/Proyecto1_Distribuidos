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
  server = argv[1];
  clnt = clnt_create(server,MINIOPS, VERSION1, "TCP");
  if(clnt == (CLIENT *) NULL) {
    printf("No hubo conexión\n");
    exit(1);
  }
  int opcion;
  char *entrada=(char*)malloc(32);
  printf("Ingrese el numero de la opción solicitada:\n\
  \t1: Numero decimal a binario.\n\
  \t2: Numero binario a hexadecimal.\n\
  \t3: Peso a dolar.\n\
  \t4: Peso a euro.\n\
  \t5: Hora del servidor.\n\
  \t6: Dia del servidor.\n\
  \t7: Sumar numeros.\n\
  \t8: Restar numeros.\n\
  \t9: Multiplicar numeros.\n\
  \t10: Dividir numeros.\n");
  scanf("%i",&opcion);
  switch(opcion){
    case 1:{
      printf("Ingrese el numero:\n");
      scanf("%s",entrada);
      char *salida=(char*)malloc(32);
      salida = *dectobin_1(&entrada,clnt);
      printf("\nSu numero en binario es:\n\t%s.\n", salida);
    }break;
    case 2:{
      printf("Ingrese el numero:\n");
      scanf("%s",entrada);
      char *salida=(char*)malloc(32);
      salida = *bintohex_1(&entrada,clnt);
      printf("\nSu numero en hexadecimal es:\n\t%s.\n", salida);
    }break;
    case 3:{
      printf("Ingrese la cantidad de pesos:\n");
      float pesos=0;
      scanf("%f",&pesos);
      float *salida;
      salida = pesoadolar_1(&pesos,clnt);
      printf("\nRepresentan %.2f dolares.\n", *salida);
    }break;
    case 4:{
      printf("Ingrese la cantidad de pesos:\n");
      float pesos=0;
      scanf("%f",&pesos);
      float *salida;
      salida = pesoaeuro_1(&pesos,clnt);
      printf("\nRepresentan %.2f euros.\n", *salida);
    }break;
    case 5:{
      st_hora *hora;
      void * vacio;
      hora = f_hora_1(vacio,clnt);
      printf("La hora es: %i:%i:%i\n",hora->hora,hora->minuto,hora->segundo);
    }break;
    case 6:{
      st_dia *dia;
      void * vacio;
      dia = f_dia_1(vacio,clnt);
      printf("El dia es: %i/%i/%i\n",dia->dia,dia->mes,dia->anho);
    }break;
    case 7:{
      printf("Ingrese la cantidad de numeros a sumar\n");
      arregloFloats arreglo;
      int i;
      scanf("%i",&(arreglo.cant));
      for (i=0;i<arreglo.cant;i++){
        printf("Ingrese el numero\n");
        scanf("%f", &(arreglo.arr[i]));
      }
      float *resultado;
      resultado = suma_1(&arreglo,clnt);
      printf("Resultado: %.2f\n",*resultado);
    }break;
    case 8:{
      printf("Ingrese la cantidad de numeros a restar.\n");
      arregloFloats arreglo;
      int i;
      scanf("%i",&(arreglo.cant));
      for (i=0;i<arreglo.cant;i++){
        printf("Ingrese el numero\n");
        scanf("%f", &(arreglo.arr[i]));
      }
      float *resultado;
      resultado = resta_1(&arreglo,clnt);
      printf("Resultado: %.2f\n",*resultado);
    }break;
    case 9:{
      arregloFloats arreglo;
      int i;
      arreglo.cant=2;
      for (i=0;i<arreglo.cant;i++){
        printf("Ingrese el numero\n");
        scanf("%f", &(arreglo.arr[i]));
      }
      float *resultado;
      resultado = multiplicacion_1(&arreglo,clnt);
      printf("Resultado: %.2f\n",*resultado);
    }break;
    case 10:{
      arregloFloats arreglo;
      int i;
      arreglo.cant=2;
      for (i=0;i<arreglo.cant;i++){
        printf("Ingrese el numero\n");
        scanf("%f", &(arreglo.arr[i]));
      }
      if(arreglo.arr[1] == 0) {
        printf("No se puede dividir por 0.\n");
      } else {
        float *resultado;
        resultado = division_1(&arreglo,clnt);
        printf("Resultado: %.2f\n",*resultado);
      }
    }break;
  }
  return 0;
}
