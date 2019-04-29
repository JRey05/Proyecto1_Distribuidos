#include "Ej5.h"
#include <rpc/rpc.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char ** dectobin_1_svc(char ** entrada, struct svc_req *cliente){
  int a = atoi(*entrada);
  char resultado[32]="\0";
  static char * resultadoFinal;
  resultadoFinal = malloc(32);
  char aux[32];
  while (a>0) {
      sprintf(aux,"%i",a%2);
      strcat(aux,resultado);
      strcpy(resultado,aux);
      a/=2;
  }
  strcpy(resultadoFinal,resultado);
  return (&resultadoFinal);
}
char ** bintohex_1_svc(char ** entrada, struct svc_req *cliente){
  int i;
  int dec=0;
  char * numero = *entrada;
  static char * resultadoFinal;
  resultadoFinal = malloc(32);
  for(i=0;i<strlen(numero);i++){
    dec*=2;
    dec+= numero[i] - '0';
  }
  printf("decimal: %i hexa:%x\n",dec,dec);
  sprintf(resultadoFinal,"%x",dec);
  return &resultadoFinal;
}
float * pesoadolar_1_svc(float * pesos,struct svc_req *cliente){
  float valorPeso=0;
  valorPeso=0.023;
  static float dolares=0.0;
  dolares = valorPeso * *pesos;
  return &dolares;
}
float * pesoaeuro_1_svc(float * pesos, struct svc_req *cliente){
  float valorPeso=0;
  valorPeso=0.021;
  static float euros=0.0;
  euros = valorPeso * *pesos;
  return &euros;
}
struct st_hora * f_hora_1_svc(void *vacio,struct svc_req *cliente){
  struct tm *ahora;
  time_t t;
  static st_hora resultado;
  t = time(NULL);
  ahora=localtime(&t);
  resultado.hora=ahora->tm_hour;
  resultado.minuto=ahora->tm_min;
  resultado.segundo=ahora->tm_sec;
  return (&resultado);
}
st_dia * f_dia_1_svc(void *vacio,struct svc_req *cliente){
  struct tm *ahora;
  time_t t;
  static st_dia resultado;
  t = time(NULL);
  ahora=localtime(&t);
  resultado.dia=ahora->tm_mday;
  resultado.mes=ahora->tm_mon + 1;
  resultado.anho=ahora->tm_year + 1900;
  return (&resultado);
}
float * suma_1_svc(arregloFloats * arr, struct svc_req *cliente){
  int cant = arr->cant;
  static float resultado=0;
  resultado = 0;
  for(int i=0; i<cant;i++) {
    resultado+=arr->arr[i];
  }
  return (&resultado);
}
float * resta_1_svc(arregloFloats * arr, struct svc_req *cliente){
  int cant = arr->cant;
  static float resultado=0;
  resultado = 0;
  resultado = arr->arr[0];
  for(int i=1; i<cant;i++) {
    resultado-=arr->arr[i];
  }
  return (&resultado);
}

float * multiplicacion_1_svc(arregloFloats * arr, struct svc_req *cliente) {
  static float resultado;
  resultado = 0;
  resultado=arr->arr[0] * arr->arr[1];
  return (&resultado);
}

float * division_1_svc(arregloFloats * arr, struct svc_req *cliente) {
  static float resultado;
  resultado = 0;
  resultado=arr->arr[0] / arr->arr[1];
  return (&resultado);
}
