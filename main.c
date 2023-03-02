#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trellis.h"
#include "trellis.c"

int main(){
    
    Trellis * trellis;
    int en = 0;
    int base = 0;
    char * secC = (char *) malloc(sizeof(char));
    printf("\nIngresa la secuencia a codificar\n");
    gets(secC);

    Info_Vector * sec = parseInput(secC, 0);

   trellis = generarTrellis();
   en = trellis->len;
   base = trellis->entradas;
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
    
    sec = parseaSecuencia(sec, en, base);

    char * secCod = codifica(trellis, sec->v, sec->len, base);
    printf("Esta es la secuencia codificada: ");
    puts(secCod);

    
    return 0;
}