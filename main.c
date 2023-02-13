#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operations_vectors.h"
#include "operations_vectors.c"

int main(){
    char * alfabet = (char* ) malloc(sizeof(char));
    int sal = 0;
    int i = 0;
    printf("\nIntroduce el alfabeto\n");
    gets(alfabet);
    Info_Vector * vAlfabet = parseInput(alfabet, 0);
    printVector(vAlfabet->v, vAlfabet->len, "Alfabeto");
    printf("\nIntroduce la cantidad de salidas que se van a tener\n");
    fflush(stdin);
    scanf("%i", &sal);
    Info_Vector * pols[sal];
    Info_Vector * retros[sal];
    int states = 0;
    int stateAux = 0;
    for(i = 0; i < sal; i++){
        char * v = (char *) malloc(sizeof(char));
        printf("\nIntroduce el polinomio para la salida %i\n", (i+1));
        fflush(stdin);
        gets(v);
        pols[i] = parseInput(v,0);
        if(stateAux <= pols[i]->len-1){
            stateAux = pols[i]->len-1;
        }
        printf("\nIntroduce la retroalimentación: (Si no ocupa solo coloque un 0)\n");
        fflush(stdin);
        char * r = (char * ) malloc(sizeof(char));
        gets(r);
        retros[i] = parseInput(r,0);
    }
    states = pow(vAlfabet->len,stateAux);
    for(i = 0; i < vAlfabet->len; i++){
        int salV[sal];
        int j = 0;
        Info_Vector * vS = NULL;
        printf("\nDato %i\n", vAlfabet->v[i]);
        
        for(j = 0; j < states; j++){
            printf("\nEstado %i\n", j);
            int data = vAlfabet->v[i];
            char * vsC = (char*) calloc(states-1, sizeof(char));
            Info_Vector * oneVector = (Info_Vector * ) malloc(sizeof(Info_Vector));
            oneVector->len = 1;
            oneVector->v = (int * ) calloc(1, sizeof(int));
            oneVector->v[0] = 1;
            
            itoa(j, vsC, vAlfabet->len);
            vS = parseInput(vsC, 0);
            if(strlen(vsC) < stateAux){
                int aux = checkFirsNonZeroIndex(vS->v, vS->len);
                if(aux == -1){
                    free(vS->v);
                    vS->v = (int *) calloc(stateAux, sizeof(int));
                    vS->v = fillZeros(vS->v, stateAux);
                    vS->len = stateAux;
                }
                else{
                    int * nV = (int*) calloc(stateAux, sizeof(int));
                    nV[stateAux-aux-1] = vS->v[aux];
                    fillDataRange(nV,0,stateAux-aux-1, 0);
                    vS->v = nV;
                    vS->len = stateAux;
                }
            }
            
            Info_Vector * vSCC = joinVectors(vS, oneVector);
            int z = 0;
            for(z = 0; z < sal; z++){
                Info_Vector * multiRes = multiByElem(vSCC, pols[z], vSCC->len);
                int * alfaNum = (int *) calloc(stateAux+1,sizeof(int));

                alfaNum[stateAux] = data;
                Info_Vector *alfaNumV = (Info_Vector *) malloc(sizeof(Info_Vector));
                fillDataRange(alfaNum, 0, stateAux, 1);
                alfaNumV->v = alfaNum;
                alfaNumV->len = stateAux+1;
                printVector(alfaNumV->v,alfaNumV->len, "AlfaNumV");

                if(retros[z]->v[0] != 0 && retros[z]->len != 1){
                    Info_Vector * multiRetroState = multiByElem(vSCC, retros[z], vSCC->len);
                    printVector(multiRetroState->v, multiRetroState->len, "MultiRetroState");
                    Info_Vector * alfaNumData = multiByElem(alfaNumV, multiRetroState, multiRetroState->len);
                    printVector(alfaNumData->v, alfaNumData->len, "AlfaNumData");
                    int newResData = sumElements(alfaNumData, vAlfabet->len);
                    alfaNumV->v[stateAux] = newResData;
                    data = newResData;
                }
                
                Info_Vector * multi2Res = multiByElem(alfaNumV,multiRes, alfaNumV->len);
                int addRes = sumElements(multi2Res, vAlfabet->len);
                printVector(pols[z]->v, pols[z]->len, "Polinomio");
                printVector(multiRes->v, multiRes->len, "Multipolicacion por Elemento");
                printVector(multi2Res->v, multi2Res->len, "Multiplicacion por Elemento 2");
                salV[z]= addRes;

            }
            insertInit(vS,data);
            printVector(vS->v, vS->len, "Estado siguiente");
            printVector(salV, sal, "Salida");
            printf("\n-----------------------------------------------------------------\n");
        }

        

    }

    return 0;
}