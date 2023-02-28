#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trellis.h"
#include "trellis.c"

int main(){
    
    Trellis * trellis;

    char * secC = (char *) malloc(sizeof(char));
    printf("\nIngresa la secuencia a codificar\n");
    gets(secC);

    int * sec = parseInput(secC, 0);

   trellis = generarTrellis();
   int k = 0;
    printf("\n------------------------------------------------------------------------------\n");
    for(k = 0; k < trellis->len; k++){
        printf("\nTrellis: %i\n", k);
        imprimeTrellis(trellis->info[k], trellis->estados,trellis->entradas);
    }
    printf("\n-----------5-------------------------------------------------------------------\n");

    trellis = combinaTrellis(trellis); 

    printf("\n------------------------------------------------------------------------------\n");
    printf("\nTrellis Nuevo");
    imprimeTrellis(trellis->info[0], trellis->estados,trellis->entradas);
    printf("\n------------------------------------------------------------------------------\n");
    
    return 0;
}