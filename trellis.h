#ifndef _TRELLIS
#define _TRELLIS
#include "operations_vectors.h"
#include "operations_vectors.c"
typedef struct{
    Info_Vector * sal;
    Info_Vector * edoSig;
} Salida;

Salida ** generarTrellis();


#include "trellis.h"
#endif