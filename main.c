#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trellis.h"
#include "trellis.c"

int main(){
    
    Salida *** trellis;

    /*
    int *** tp;

    tp = (int ***) malloc(sizeof(int**));
    tp[0] = (int **) malloc(sizeof(int*));
    tp[0][0] = (int *) malloc(sizeof(int));
    tp[0][1] = (int *) malloc(sizeof(int));

    tp[0][0][0] = 5;
    tp[0][1][0] = 10;

    printf("\nValores del puntero: %i\n", tp[0][0][0]);
    printf("\nValores del puntero: %i\n", tp[0][1][0]);
    */
   trellis = generarTrellis();
   

    return 0;
}