#ifndef _TRELLIS
#define _TRELLIS
#include "operations_vectors.h"
#include "operations_vectors.c"
typedef struct{
    Info_Vector * sal;
    Info_Vector * edoSig;
} Salida;

Salida *** generarTrellis();
void imprimeTrellis(Salida ** trellis, int estados, int alfabeto);

#include "trellis.h"
#endif