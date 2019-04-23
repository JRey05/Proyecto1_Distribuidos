#include "Ej5.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int * decToBin_1_svc(int * entrada, struct svc_req *cliente){
  int a = *entrada;
  static int resultado;
  while (a>0) {
    resultado*=10;
    resultado+=a%2;
    a/=2;
  }
  return (&resultado);
}
int * binToHex_1_svc(int * entrada, struct svc_req *cliente){
  int a = *entrada;
  static int resultado;
  while (a>0) {
    resultado*=8;
    resultado+=a%2;
    a/=2;
  }
};
/*
float pesoADolar(float) = 3;
float pesoAEuro(float) = 4;
*/
st_hora * f_hora_1_sv(void *vacio,struct svc_req *cliente){
  struct tm *ahora;
  time_t t;
  static st_hora resultado;
  t = time(NULL);
  ahora=gmtime(&t);
  resultado.hora=ahora->tm_hour;
  resultado.minuto=ahora->tm_min;
  resultado.segundo=ahora->tm_sec;
  return (&resultado);
}
st_dia * dia_1_sv(void *vacio,struct svc_req *cliente){
  struct tm *ahora;
  time_t t;
  static st_dia resultado;
  t = time(NULL);
  ahora=gmtime(&t);
  resultado.dia=ahora->tm_mday;
  resultado.mes=ahora->tm_mon;
  resultado.anho=ahora->tm_year;
  return (&resultado);
}
float * suma_1_sv(arregloFloats * arr, struct svc_req *cliente){
  int cant = arr->cant;
  static float resultado=0;
  for(int i=0; i<cant;i++) {
    resultado+=arr->arr[i];
  }
  return (&resultado);
}
float * multiplicacion_1_sv(arregloFloats * arr, struct svc_req *cliente) {
  static float resultado;
  resultado=arr->arr[0] * arr->arr[1];
  return (&resultado);
}
