#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trellis.h"
#include "trellis.c"

int main(){
    
    Trellis * trellis;

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
   int k = 0;
    printf("\n------------------------------------------------------------------------------\n");
    for(k = 0; k < trellis->len; k++){
        printf("\nTrellis: %i\n", k);
        imprimeTrellis(trellis->info[k], trellis->estados,trellis->entradas);
    }
    printf("\n------------------------------------------------------------------------------\n");

    trellis = combinaTrellis(trellis); 

    printf("\n------------------------------------------------------------------------------\n");
    printf("\nTrellis Nuevo");
    imprimeTrellis(trellis->info[0], trellis->estados,trellis->entradas);
    printf("\n------------------------------------------------------------------------------\n");

    return 0;
}