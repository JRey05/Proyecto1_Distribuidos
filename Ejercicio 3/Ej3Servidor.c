#include "SumaArreglos.h"
#include <rpc/rpc.h>
#include <stdio.h>
nametype * cadena_1_svc(nametype *entrada, struct svc_req *cliente){
  printf("Texto recibido: \"%s\"\n",*entrada);
  int arrA[100];
  int arrB[100];
  int arrC[100];
  int i;
  static nametype resultado;
  for (i=0;i<100;i++) {
    arrA[i]=rand();
    arrB[i]=rand();
    arrC[i]=arrA[i]+arrB[i];
  }
  resultado = "a";
  return (&resultado);
}
