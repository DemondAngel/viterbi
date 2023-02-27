#ifndef _TRELLIS
#define _TRELLIS
#include "operations_vectors.h"
#include "operations_vectors.c"
typedef struct{
    Info_Vector * sal;
    Info_Vector * edoSig;
} Salida;

typedef struct {
    Salida *** info;
    int estados;
    int entradas;
    int len;
} Trellis;

Trellis * generarTrellis();
void imprimeTrellis(Salida ** trellis, int estados, int alfabeto);
Trellis * combinaTrellis(Trellis * trellis);
void incrementaContador(int * contador, int numMax, int len);

#include "trellis.h"
#endif