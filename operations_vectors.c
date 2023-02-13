#include "operations_vectors.h"
#include <stdio.h>

int * fillZeros(int * v, int lenV){
    int i = 0;
    for(i = 0; i < lenV; i++) v[i] = 0;
    return v;
}

int * copyVector(int * o, int * d, int len){
    int i = 0;

    for(i = 0; i < len; i++) d[i] = o[i];

    return d;
}

int checkFirsNonZeroIndex(int * v, int lenV){
    int i = 0;
    int index = -1;
    for(i = 0; i < lenV; i++){
        if(v[i] != 0){
            index = i;
            break;
        }
    }

    return index;
}

Info_Vector * cleanLeftZeros(int * v, int lenV){
    int i = 0;
    int j = 0;
    for(i = 0; i < lenV; i++){
        if(v[i] != 0){
            break;
        }
    }
    int newLen = lenV-i;

    int * newVector = (int *) calloc(newLen, sizeof(int));

    for(j = 0; j < newLen; j++, i++) newVector[j] = v[i];

    Info_Vector * infoVector = (Info_Vector * ) malloc(sizeof(Info_Vector));
    infoVector->v = newVector;
    infoVector->len = newLen;
    return infoVector;

}

void printVector(int * v, int lenV, char * label){
    int z = 0;
    printf("\nEste es el vector: %s\n", label);
    for(z = 0; z< lenV; z++) printf("%i", v[z]);
}

Info_Vector * joinVectors(Info_Vector * a, Info_Vector *b){
    Info_Vector * newVector = (Info_Vector *) malloc(sizeof(Info_Vector));
    newVector->len = a->len + b ->len;
    newVector->v = (int *) calloc(newVector->len, sizeof(int));
    int i = 0, j = 0;

    for(i = 0; i< a->len; i++, j++) newVector->v[j] = a->v[i];
    for(i = 0; i< b->len; i++, j++) newVector->v[j] = b->v[i];

    return newVector;
}

int sumElements(Info_Vector * v, int GF){
    int sum = 0, i = 0;

    for(i = 0; i < v->len; i++) sum += v->v[i];

    sum = sum%GF;

    return sum;
}

Info_Vector * parseInput(char * input, int cleanZerosLeft){
    int i = 0;
    int len = strlen(input);
    int * v = (int *) calloc(len, sizeof(int));
    int beg = 0;
    for(i = 0; i < len; i++){
        v[i] = input[i] - '0';
    }
    Info_Vector * infoVector = (Info_Vector * ) malloc(sizeof(Info_Vector));
     if(cleanZerosLeft == 1) infoVector = cleanLeftZeros(v, len);
    else{
        infoVector->v = v;
        infoVector->len = len;
    }
    return infoVector;
}

void fillDataRange(int * v, int begin, int end, int data){
   for(begin; begin < end; begin++) v[begin] = data;
}

int * add(int * a, int lenA, int * b, int lenB, int GF){

    int i = 0, lenC = 0, j = 0;
    int * aup = NULL;
    int * adder = NULL;
    if(lenA >= lenB){
        aup = a;
        adder = b;
        lenC = lenA;
    }
    else{
        aup = b;
        adder = a;
        lenC = lenB;
        int lenAux = lenA;
        lenA = lenC;
        lenB = lenAux;
        
    }

    int *  c = (int * )calloc(lenC, sizeof(int));

    for(i = lenC-1, j = lenB-1; i > -1; i--, j--){
        int data = 0;
        if(j > -1)
            data = aup[i] + adder[j];
        else 
            data = aup[i];

        c[i] = data%GF;
    }

    return c;
}

void * insertInit(Info_Vector * a, int data){
    int o = 0, k = 0;
    for(o = 0; o < a->len-1; o++){
        a->v[o] = a->v[o+1];
    }
    a->v[a->len-1] = data;
}

Info_Vector * multi(int * a, int lenA, int * b, int lenB, int GF){

    int i = 0, j = 0, z = 0;
    Info_Vector * infoVector = NULL;
    int lenMult = 0;
    int lenMulty = 0;
    int * multiplying = NULL;
    int * multiplcator = NULL;
    int * result = NULL; 

    if(lenA >= lenB){
        multiplying = a;
        multiplcator = b;
        lenMult = lenB;
        lenMulty = lenA;
        
    }
    else{
       multiplying = b;
        multiplcator = a; 
        lenMult = lenA;
        lenMulty = lenB;
    }
    
    result = (int * )calloc(lenMulty,sizeof(int));
    result = fillZeros(result, lenMulty);
    int k = 0;
       
    for(i = lenMult-1, j = 0; i > -1; i--, j++){
        int digitMultiplcator = multiplcator[i];
        int * resultAux = (int *) calloc(lenMulty+j,sizeof(int));
        resultAux = fillZeros(resultAux, lenMulty+j);
        for(z = lenMulty-1; z > -1; z--){
            resultAux[z] = digitMultiplcator*multiplying[z];
            
        }
        
        result = add(resultAux, lenMulty+j,result, lenMulty+(j>0 ? j-1:0),GF);
        
    }
    infoVector = (Info_Vector *) malloc(sizeof(Info_Vector));
    infoVector->len = lenMulty;
    infoVector->v = result;

    return infoVector;

}

Info_Vector * multiByElem(Info_Vector * a, Info_Vector * b, int GF){
    int i = 0;
    Info_Vector * newVector = (Info_Vector *) malloc(sizeof(Info_Vector));
    newVector->len = a->len;
    newVector->v = (int * ) calloc(newVector->len, sizeof(int));
    for(i = 0; i < a->len; i++) {
        newVector->v[i]= (a->v[i]* b->v[i])%GF;
    }

    return newVector;

}

Divi_Result * divi(int * a, int lenA, int * b, int lenB, int GF){

    int newLen = lenA-lenB+1;
    int * result = (int * )calloc(newLen, sizeof(int));
    result = fillZeros(result, newLen);
    
    int polDivn = newLen-1;
    int polDivsr = lenB-1;
    int i = 0, j = 0;
    int * divdn = (int * ) calloc(lenA, sizeof(int));
    divdn = copyVector(a, divdn, lenA);

    while(polDivn >= polDivsr){
        int multpy = divdn[i]/b[0];
        result[i] = multpy;
        int * res = (int * ) calloc(lenA, sizeof(int));
        res = fillZeros(res, lenA);
        for(j = 0; j < lenB; j++)
            res[j+i] = multpy*b[j];

        divdn = add(divdn, lenA, res, lenA, GF); 
        i = checkFirsNonZeroIndex(divdn, lenA);
        
        polDivn = lenA-i-1;
    }

    Divi_Result * diviResult = (Divi_Result * ) malloc(sizeof(Divi_Result));


    diviResult ->result=result;
    diviResult ->res = divdn;

    return diviResult;
    
}