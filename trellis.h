#ifndef _TRELLIS
#define _TRELLIS
#include "operations_vectors.h"
#include "operations_vectors.c"
typedef struct{
    int sal;
    int edoSig;
} Salida;

typedef struct {
    Salida *** info;
    int estados;
    int entradas;
    int sals;
    int len;
} Trellis;

Trellis * generarTrellis();
void imprimeTrellis(Salida ** trellis, int estados, int alfabeto);
Trellis * combinaTrellis(Trellis * trellis);
void incrementaContador(int * contador, int numMax, int len);
int convierteVectorNum(int * v, int len, int base);
int fusionaEstados(int * v, int len, int base);
int sumaSalidas(int * v, int len,int base);
char * codifica(Trellis * trellis, int * sec);

#include "trellis.h"
#endif