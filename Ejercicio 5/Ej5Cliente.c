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
  double tiempo;
  double promedio=0;
  struct timeval inicio,final;
  int i;
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

      for (i=0;i<100;i++){
        //inicio el temporizador
        gettimeofday(&inicio,NULL);
        salida = *dectobin_1(&entrada,clnt);
        //finalizo el temporizador
        gettimeofday(&final,NULL);
        tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
        promedio=promedio+tiempo;
      }
      promedio=promedio/100;
      printf("\nTiempo que demoro: %.2f μs\n", promedio);
      printf("Su numero en binario es:\n\t%s.\n", salida);
    }break;
    case 2:{
      printf("Ingrese el numero:\n");
      scanf("%s",entrada);
      char *salida=(char*)malloc(32);
      for (i=0;i<100;i++){
        //inicio el temporizador
        gettimeofday(&inicio,NULL);
        salida = *bintohex_1(&entrada,clnt);
        //finalizo el temporizador
        gettimeofday(&final,NULL);
        tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
        promedio=promedio+tiempo;
      }
      promedio=promedio/100;
      printf("Tiempo que demoro: %.2f μs\n", promedio);
      printf("\nSu numero en hexadecimal es:\n\t%s.\n", salida);
    }break;
    case 3:{
      printf("Ingrese la cantidad de pesos:\n");
      float pesos=0;
      scanf("%f",&pesos);
      float *salida;
      for (i=0;i<100;i++){
        //inicio el temporizador
        gettimeofday(&inicio,NULL);
        salida = pesoadolar_1(&pesos,clnt);
        //finalizo el temporizador
        gettimeofday(&final,NULL);
        tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
        promedio=promedio+tiempo;
      }
      promedio=promedio/100;
      printf("Tiempo que demoro: %.2f μs\n", promedio);
      printf("\nRepresentan %.2f dolares.\n", *salida);
    }break;
    case 4:{
      printf("Ingrese la cantidad de pesos:\n");
      float pesos=0;
      scanf("%f",&pesos);
      float *salida;
      for (i=0;i<100;i++){
        //inicio el temporizador
        gettimeofday(&inicio,NULL);
        salida = pesoaeuro_1(&pesos,clnt);
        //finalizo el temporizador
        gettimeofday(&final,NULL);
        tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
        promedio=promedio+tiempo;
      }
      promedio=promedio/100;
      printf("Tiempo que demoro: %.2f μs\n", promedio);
      printf("\nRepresentan %.2f euros.\n", *salida);
    }break;
    case 5:{
      st_hora *hora;
      void * vacio;
      for (i=0;i<100;i++){
        //inicio el temporizador
        gettimeofday(&inicio,NULL);
        hora = f_hora_1(vacio,clnt);
        //finalizo el temporizador
        gettimeofday(&final,NULL);
        tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
        promedio=promedio+tiempo;
      }
      promedio=promedio/100;
      printf("Tiempo que demoro: %.2f μs\n", promedio);
      printf("La hora es: %i:%i:%i\n",hora->hora,hora->minuto,hora->segundo);
    }break;
    case 6:{
      st_dia *dia;
      void * vacio;
      for (i=0;i<100;i++){
        //inicio el temporizador
        gettimeofday(&inicio,NULL);
        dia = f_dia_1(vacio,clnt);
        //finalizo el temporizador
        gettimeofday(&final,NULL);
        tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
        promedio=promedio+tiempo;
      }
      promedio=promedio/100;
      printf("Tiempo que demoro: %.2f μs\n", promedio);
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
      for (i=0;i<100;i++){
        //inicio el temporizador
        gettimeofday(&inicio,NULL);
        resultado = suma_1(&arreglo,clnt);
        //finalizo el temporizador
        gettimeofday(&final,NULL);
        tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
        promedio=promedio+tiempo;
      }
      promedio=promedio/100;
      printf("Tiempo que demoro: %.2f μs\n", promedio);
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
      for (i=0;i<100;i++){
        //inicio el temporizador
        gettimeofday(&inicio,NULL);
        resultado = resta_1(&arreglo,clnt);
        //finalizo el temporizador
        gettimeofday(&final,NULL);
        tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
        promedio=promedio+tiempo;
      }
      promedio=promedio/100;
      printf("Tiempo que demoro: %.2f μs\n", promedio);
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
      for (i=0;i<100;i++){
        //inicio el temporizador
        gettimeofday(&inicio,NULL);
        resultado = multiplicacion_1(&arreglo,clnt);
        //finalizo el temporizador
        gettimeofday(&final,NULL);
        tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
        promedio=promedio+tiempo;
      }
      promedio=promedio/100;
      printf("Tiempo que demoro: %.2f μs\n", promedio);
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
        for (i=0;i<100;i++){
          //inicio el temporizador
          gettimeofday(&inicio,NULL);
          //finalizo el temporizador
          resultado = division_1(&arreglo,clnt);
          gettimeofday(&final,NULL);
          tiempo=(double)((final.tv_sec*1000000+final.tv_usec)-(inicio.tv_sec*1000000+inicio.tv_usec));
          promedio=promedio+tiempo;
        }
        promedio=promedio/100;
        printf("Tiempo que demoro: %.2f μs\n", promedio);
        printf("Resultado: %.2f\n",*resultado);
      }
    }break;
  }
  return 0;
}
