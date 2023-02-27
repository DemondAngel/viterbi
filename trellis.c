
#include "trellis.h"
int sal = 0;
Trellis * generarTrellis(){

    char * alfabet = (char* ) malloc(sizeof(char));
    
    int en = 0;
    int i = 0;
    int k = 0;
    printf("\nIntroduce el alfabeto\n");
    gets(alfabet);
    Info_Vector * vAlfabet = parseInput(alfabet, 0);
    //printVector(vAlfabet->v, vAlfabet->len, "Alfabeto");
    printf("\nIntroduce la cantidad de salidas que se van a tener\n");
    fflush(stdin);
    scanf("%i", &sal);
    printf("\nIntroduce la cantidad de entradas que se van a tener\n");
    fflush(stdin);
    scanf("%i", &en);
    Info_Vector * pols[en][sal];
    Info_Vector * retros[en][sal];
    int states = 0;
    int stateAux = 0;
    
    for(k = 0; k < en; k++){
        for(i = 0; i < sal; i++){
            char * v = (char *) malloc(sizeof(char));
            printf("\nIntroduce el polinomio para la salida %i, entrada %i\n", (i+1), (k+1));
            fflush(stdin);
            gets(v);
            pols[k][i] = parseInput(v,0);
            if(stateAux <= pols[k][i]->len-1){
                stateAux = pols[k][i]->len-1;
            }
            printf("\nIntroduce la retroalimentación: (Si no ocupa solo coloque un 0)\n");
            fflush(stdin);
            char * r = (char * ) malloc(sizeof(char));
            gets(r);
            retros[k][i] = parseInput(r,0);
        }
    }

    
    states = pow(vAlfabet->len,stateAux);
    Salida *** trellis = (Salida ***) calloc(en, sizeof(Salida **));

    for(k = 0; k < en; k++){
        trellis[k] = (Salida ** ) calloc(en,sizeof(Salida *)) ;
        //Cambiar por estado
        for(i = 0; i < states; i++){
            
            int j = 0;
            Info_Vector * vS = NULL;
        printf("\nEstado %i\n", i);
            trellis[k][i] = (Salida *) calloc(vAlfabet->len,sizeof(Salida));
            for(j = 0; j < vAlfabet->len; j++){ //Cambiar por entradas
                int * salV = (int * ) calloc(sal, sizeof(int));
                printf("\nDato %i\n", vAlfabet->v[j]);
                int data = vAlfabet->v[j];
                char * vsC = (char*) calloc(states-1, sizeof(char));
                Info_Vector * oneVector = (Info_Vector * ) malloc(sizeof(Info_Vector));
                oneVector->len = 1;
                oneVector->v = (int * ) calloc(1, sizeof(int));
                oneVector->v[0] = 1;
                
                itoa(i, vsC, vAlfabet->len);
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
                        free(vS->v);
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
                    Info_Vector * multiRes = multiByElem(vSCC, pols[k][z], vSCC->len);
                    int * alfaNum = (int *) calloc(stateAux+1,sizeof(int));

                    alfaNum[stateAux] = data;
                    Info_Vector *alfaNumV = (Info_Vector *) malloc(sizeof(Info_Vector));
                    fillDataRange(alfaNum, 0, stateAux, 1);
                    alfaNumV->v = alfaNum;
                    alfaNumV->len = stateAux+1;
                    //printVector(alfaNumV->v,alfaNumV->len, "AlfaNumV");

                    if(retros[k][z]->v[0] != 0 && retros[k][z]->len != 1){
                        Info_Vector * multiRetroState = multiByElem(vSCC, retros[k][z], vSCC->len);
                        //printVector(multiRetroState->v, multiRetroState->len, "MultiRetroState");
                        Info_Vector * alfaNumData = multiByElem(alfaNumV, multiRetroState, multiRetroState->len);
                        //printVector(alfaNumData->v, alfaNumData->len, "AlfaNumData");
                        int newResData = sumElements(alfaNumData, vAlfabet->len);
                        alfaNumV->v[stateAux] = newResData;
                        data = newResData;
                    }
                    
                    Info_Vector * multi2Res = multiByElem(alfaNumV,multiRes, alfaNumV->len);
                    int addRes = sumElements(multi2Res, vAlfabet->len);
                    //printVector(pols[z]->v, pols[z]->len, "Polinomio");
                    //printVector(multiRes->v, multiRes->len, "Multipolicacion por Elemento");
                    //printVector(multi2Res->v, multi2Res->len, "Multiplicacion por Elemento 2");
                    salV[z]= addRes;

                }
                insertInit(vS,data);

                printVector(vS->v, vS->len, "Estado siguiente");
                trellis[k][i][j].edoSig = vS;
                printVector(salV, sal, "Salida");
                Info_Vector * salVI = (Info_Vector * ) malloc(sizeof(Info_Vector));
                salVI->len = sal;
                salVI->v = salV;
                trellis[k][i][j].sal = salVI;
                trellis[k][i][j].sal->len = sal;
                printf("\n-----------------------------------------------------------------\n");
            }

            

        }
    }

    Trellis * trellisInfo = (Trellis *) malloc(sizeof(Trellis));

    trellisInfo->info = trellis;
    trellisInfo->estados = states;
    trellisInfo->entradas = vAlfabet->len;
    trellisInfo->len = en;
    
    return trellisInfo;
}

void imprimeTrellis(Salida ** trellis, int estados, int alfabeto){

    int i = 0, j = 0;

    for(i = 0; i < estados; i++){
        printf("\nEstado %i\n", i);
        for(j = 0; j < alfabeto; j++){
            printf("\nEntrada %i\n", j);
            printVector(trellis[i][j].edoSig->v, trellis[i][j].edoSig->len, "Estado siguiente");
            printVector(trellis[i][j].sal->v, trellis[i][j].sal->len, "Salida");
            

        }
    }

}

Trellis * combinaTrellis(Trellis * trellis){
    int i = 0;
    int * counterStates = (int *)calloc(trellis->len, sizeof(int));
    int counterS = 0;
    int totalStates = pow(trellis->estados, trellis->len);
    int * counterIn = (int *) calloc(trellis->len, sizeof(int));
    int totalIn = pow(trellis->entradas, trellis->len);
    int counterI = 0;

    for(i = 0; i < trellis->len; i++){
        counterStates[i] = 0;
        counterIn[i] = 0;
    }

    for(counterI = 0; counterI < totalIn; counterI++){
        printf("\nDato: ");
        for(i = 0; i < trellis->len; i++) printf("%i", counterIn[i]);
        printf("\n");

        for(counterS = 0; counterS < totalStates; counterS++){
            printf("\nEstados: ");
            for(i = 0; i < trellis->len; i++) printf("%i", counterStates[i]);
            printf("\n");
            incrementaContador(counterStates, trellis->estados, trellis->len);
        }

        incrementaContador(counterIn, trellis->entradas, trellis->len);   
    }

    free(counterStates);
    free(counterIn);  
    
    return NULL;
}

void incrementaContador(int * contador, int numMax, int len){
    int i = 0;
    for(i = 0; i < len; i++){
            if(contador[i] < numMax){
                contador[i]++;
                if(contador[i] == numMax){
                    contador[i] = 0;
                }
                else{
                    break;
                }      
            }
        }
}