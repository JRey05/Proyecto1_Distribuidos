struct st_hora {
  int8_t segundo;
  int8_t minuto;
  int8_t hora;
};
struct st_dia {
  int8_t dia;
  int8_t mes;
  int16_t anho;
};
typedef struct parametros arregloFloats;
struct parametros{
  int cant;
  float arr[4];
};
program MINIOPS{
  version VERSION1{
    int decToBin(int) = 1;
    int binToHex(int) = 2;
    float pesoADolar(float) = 3;
    float pesoAEuro(float) = 4;
    st_hora f_hora() = 5;
    st_dia f_dia() = 6;
    float suma(arregloFloats) = 7;
    float multiplicacion(arregloFloats) = 10;
  } = 1;
} = 0x200F0003;
