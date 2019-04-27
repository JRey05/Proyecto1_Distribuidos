struct st_hora {
  int segundo;
  int minuto;
  int hora;
};
struct st_dia {
  int dia;
  int mes;
  int anho;
};
typedef struct parametros arregloFloats;
struct parametros{
  int cant;
  float arr[4];
};
program MINIOPS{
  version VERSION1{
    string dectobin(string) = 1;
    string bintohex(string) = 2;
    float pesoadolar(float) = 3;
    float pesoaeuro(float) = 4;
    st_hora f_hora() = 5;
    st_dia f_dia() = 6;
    float suma(arregloFloats) = 7;
    float resta(arregloFloats) = 8;
    float multiplicacion(arregloFloats) = 9;
    float division(arregloFloats) = 10;
  } = 1;
} = 0x200F0003;
