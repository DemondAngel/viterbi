
#include "trellis.h"

Trellis * generarTrellis(){

    char * alfabet = (char* ) malloc(sizeof(char));

    if(alfabet == NULL){
        printf("\nNo se reservó la memoria correctamente para el alfabeto\n");
        exit(1);
    }

    int sal = 0;
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

            if(v == NULL){
                printf("\nNo se reservo la memoria para almacenar los polinomios\n");
                exit(1);
            }

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

            if(r == NULL){
                printf("\nNo se reservo memoria para la retroalimentación\n");
                exit(1);
            }

            gets(r);
            retros[k][i] = parseInput(r,0);
        }
    }

    
    states = pow(vAlfabet->len,stateAux);
    Salida *** trellis = (Salida ***) calloc(en, sizeof(Salida **));

    if(trellis == NULL){
        printf("\nNo se reservo memoria para el Trellis\n");
        exit(1);
    }

    for(k = 0; k < en; k++){
        trellis[k] = (Salida ** ) calloc(en,sizeof(Salida *)) ;
        
        if(trellis[k] == NULL){
            printf("\nNo se reservo memoria para trellis %i\n", k);
            exit(1);
        }

        //Cambiar por estado
        for(i = 0; i < states; i++){
            
            int j = 0;
            Info_Vector * vS = NULL;
        //printf("\nEstado %i\n", i);
            trellis[k][i] = (Salida *) calloc(vAlfabet->len,sizeof(Salida));

            if(trellis[k][i] == NULL){
                printf("\nNo se reservo memoria para trellis %i %i\n", k, i);
                exit(1);
            }

            for(j = 0; j < vAlfabet->len; j++){ //Cambiar por entradas
                int * salV = (int * ) calloc(sal, sizeof(int));

                if(salV == NULL){
                    printf("\nNo se reservo memoria para salV\n");
                    exit(1);
                }

                //printf("\nDato %i\n", vAlfabet->v[j]);
                int data = vAlfabet->v[j];
                char * vsC = (char*) calloc(states-1, sizeof(char));

                if(vsC == NULL){
                    printf("\nNo se reservo memoria para vsC\n");
                    exit(1);
                }

                Info_Vector * oneVector = (Info_Vector * ) malloc(sizeof(Info_Vector));

               if(oneVector == NULL){
                    printf("\nNo se reservo memoria para oneVector\n");
                    exit(1);
                }

                oneVector->len = 1;
                oneVector->v = (int * ) calloc(1, sizeof(int));

                if(oneVector->v == NULL){
                    printf("\nNo se reservo memoria para oneVector v\n");
                    exit(1);
                }

                oneVector->v[0] = 1;
                
                itoa(i, vsC, vAlfabet->len);
                vS = parseInput(vsC, 0);
                if(strlen(vsC) < stateAux){
                    int aux = checkFirsNonZeroIndex(vS->v, vS->len);
                    if(aux == -1){
                        free(vS->v);
                        vS->v = (int *) calloc(stateAux, sizeof(int));

                        if(vS->v == NULL){
                            printf("\nNo se reservo memoria para vS v\n");
                            exit(1);
                        }

                        vS->v = fillZeros(vS->v, stateAux);
                        vS->len = stateAux;
                    }
                    else{     
                        int * nV = (int*) calloc(stateAux, sizeof(int));

                        if(nV == NULL){
                            printf("\nNo se reservo memoria para nV\n");
                            exit(1);
                        }

                        nV[stateAux-aux-1] = vS->v[aux];
                        fillDataRange(nV,0,stateAux-aux-1, 0);
                        free(vS->v);
                        vS->v = nV;
                        vS->len = stateAux;
                    }
                }
                
                free(vsC);
                Info_Vector * vSCC = joinVectors(vS, oneVector);
                free(oneVector->v);
                free(oneVector);
                int z = 0;
                for(z = 0; z < sal; z++){
                    Info_Vector * multiRes = multiByElem(vSCC, pols[k][z], vSCC->len);

                    if(multiRes == NULL){
                        printf("\nNo se reservo memoria para multiRes\n");
                        exit(1);
                    }

                    int * alfaNum = (int *) calloc(stateAux+1,sizeof(int));

                    if(alfaNum == NULL){
                        printf("\nNo se reservo memoria para alfaNum\n");
                        exit(1);
                    }

                    alfaNum[stateAux] = data;
                    Info_Vector *alfaNumV = (Info_Vector *) malloc(sizeof(Info_Vector));

                    if(alfaNumV == NULL){
                        printf("\nNo se reservo memoria para alfaNumV\n");
                        exit(1);
                    }

                    fillDataRange(alfaNum, 0, stateAux, 1);
                    alfaNumV->v = alfaNum;
                    alfaNumV->len = stateAux+1;
                    //printVector(alfaNumV->v,alfaNumV->len, "AlfaNumV");

                    if(retros[k][z]->v[0] != 0 && retros[k][z]->len != 1){
                        Info_Vector * multiRetroState = multiByElem(vSCC, retros[k][z], vSCC->len);

                        if(multiRetroState == NULL){
                            printf("\nNo se reservo memoria para multiRetroState\n");
                            exit(1);
                        }

                        //printVector(multiRetroState->v, multiRetroState->len, "MultiRetroState");
                        Info_Vector * alfaNumData = multiByElem(alfaNumV, multiRetroState, multiRetroState->len);

                        if(alfaNumData == NULL){
                            printf("\nNo se reservo memoria para alfaNumData\n");
                            exit(1);
                        }

                        //printVector(alfaNumData->v, alfaNumData->len, "AlfaNumData");
                        int newResData = sumElements(alfaNumData, vAlfabet->len);
                        alfaNumV->v[stateAux] = newResData;
                        data = newResData;
                        free(multiRetroState->v);
                        free(multiRetroState);
                        free(alfaNumData->v);
                        free(alfaNumData);
                    }
                    
                    Info_Vector * multi2Res = multiByElem(alfaNumV,multiRes, alfaNumV->len);

                    if(multi2Res == NULL){
                        printf("\nNo se reservo memoria para multi2Res\n");
                        exit(1);
                    }

                    int addRes = sumElements(multi2Res, vAlfabet->len);
                    //printVector(pols[z]->v, pols[z]->len, "Polinomio");
                    //printVector(multiRes->v, multiRes->len, "Multipolicacion por Elemento");
                    //printVector(multi2Res->v, multi2Res->len, "Multiplicacion por Elemento 2");
                    salV[z]= addRes;
                    free(multi2Res->v);
                    free(multi2Res);
                    free(multiRes->v);
                    free(multiRes);
                    free(alfaNumV->v);
                    free(alfaNumV);

                }
                insertInit(vS,data);

                //printVector(vS->v, vS->len, "Estado siguiente");
                
                trellis[k][i][j].edoSig = convierteVectorNum(vS->v, vS->len, vAlfabet->len);
                //printVector(salV, sal, "Salida");
                Info_Vector * salVI = (Info_Vector * ) malloc(sizeof(Info_Vector));

                if(salVI == NULL){
                    printf("\nNo se reservo memoria para salVI\n");
                    exit(1);
                }

                salVI->len = sal;
                salVI->v = salV;

                trellis[k][i][j].sal = convierteVectorNum(salVI->v, sal, vAlfabet->len);
                free(vS->v);
                free(vS);
                free(salVI->v);
                free(salVI);
                //printf("\n-----------------------------------------------------------------\n");
            }

            

        }
    }

    Trellis * trellisInfo = (Trellis *) malloc(sizeof(Trellis));

    if(trellisInfo == NULL){
        printf("\nNo se reservo memoria para trellisInfo\n");
        exit(1);
    }

    trellisInfo->info = trellis;
    trellisInfo->estados = states;
    trellisInfo->entradas = vAlfabet->len;
    trellisInfo->sals = sal;
    trellisInfo->len = en;
    
    return trellisInfo;
}

void imprimeTrellis(Salida ** trellis, int estados, int alfabeto){

    int i = 0, j = 0;

    for(i = 0; i < estados; i++){
        printf("\nEstado %i\n", i);
        for(j = 0; j < alfabeto; j++){
            printf("\nEntrada %i\n", j);
            printf("\nEstado siguiente: %i\n",trellis[i][j].edoSig );
            printf("\nSalida: %i\n", trellis[i][j].sal);
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
    Salida *** t = NULL;
    for(i = 0; i < trellis->len; i++){
        counterStates[i] = 0;
        counterIn[i] = 0;
    }
    t = (Salida ***) calloc(1, sizeof(Salida**));
    t[0] = (Salida **) calloc(totalStates, sizeof(Salida *));
    for(counterS = 0; counterS < totalStates; counterS++){
        
         printf("\nEstados: ");
        for(i = 0; i < trellis->len; i++) printf("%i", counterStates[i]);
        printf("\n");
        t[0][counterS] = (Salida *) calloc(totalIn,sizeof(Salida));

        for(counterI = 0; counterI < totalIn; counterI++){
            printf("\nDato: ");
            for(i = 0; i < trellis->len; i++) printf("%i", counterIn[i]);
            printf("\n");

            int * states = (int * ) calloc(trellis->len,sizeof(int));
            int * sals = (int * ) calloc(trellis->len, sizeof(int));
            for(i = 0; i < trellis->len; i++){
                states[i] = trellis->info[i][counterStates[i]][counterIn[i]].edoSig;
                printf("\nEstados %i\n", states[i]);
                sals[i] = trellis->info[i][counterStates[i]][counterIn[i]].sal;
                printf("\nSals %i\n", sals[i]);
            }

            t[0][counterS][counterI].edoSig = fusionaEstados(states, trellis->len, trellis->entradas);
            t[0][counterS][counterI].sal = sumaSalidas(sals, trellis->len, trellis->entradas);
            incrementaContador(counterIn, trellis->entradas, trellis->len);
            //free(states);
            //free(sals); 
        }
        incrementaContador(counterStates, trellis->estados, trellis->len);
        
    }

    free(counterStates);
    free(counterIn);  
    
    Trellis * nTrellis = (Trellis *) malloc(sizeof(Trellis));

    nTrellis->entradas = totalIn;
    nTrellis->estados = totalStates;
    nTrellis->len = 1;
    nTrellis->info = t;

    return nTrellis;
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

int convierteVectorNum(int * v, int len, int base){

    int i = 0, j = 0;
    int value = 0;
    for(i = len-1; i >= 0; i--, j++){
        //printf("\nValor que se esta sumando: %i\n", v[i]);
        value += v[i]*pow(base, j);
    }

    return value;

}

int fusionaEstados(int * v, int len, int base){

    char cadena[1000] = "";
    char cadenaRes[1000] = "";
    int i = 0;
    int len2 = 0;
    
    for(i = 0; i < len; i++){
        itoa(v[i], cadena, base);

        strcat(cadenaRes, cadena);
        strcpy(cadena, "");
        
    }

    len2 = strlen(cadenaRes);
    int * nV = (int *) calloc(len2, sizeof(int));
    for(i = 0; i < len2; i++){
        nV[i] = cadenaRes[i] - '0';
    }
    int value = convierteVectorNum(nV, len2, base);
    free(nV);
    return value;
    
}

int sumaSalidas(int * v, int len,int base){
  //Convertir de entero a arreglo y hacer suma directa y reconvertir valor a decimal
    char cadena[1000];
    int i = 0;
    int j = 0;
    int * vR = (int *) calloc(0, sizeof(int));
    int lenVR = 0;
    printVector(v, len, "Vector con datos que entran");
    for(i = 0; i< len; i++){
        strcpy(cadena, "");
        itoa(v[i], cadena, base);
        int lenVector = strlen(cadena);
        int * vAux = (int *) calloc(lenVector, sizeof(int));
        for(j = 0; j < lenVector; j++){
            vAux[j] = cadena[j] - '0';
        }
        
        int * vRAux = add(vAux,lenVector, vR, lenVR, base);
        printVector(vRAux, lenVector, "VRAux");

        if(lenVector > lenVR) lenVR = lenVector;
        free(vAux);
        free(vR);
        vR = vRAux;


    }
    
    int value = convierteVectorNum(vR, lenVR, 2);
    free(vR);
    return value;

}

char * codifica(Trellis * trellis, int * sec){
     v v
}