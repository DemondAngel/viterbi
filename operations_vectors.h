#ifndef _OPERATIONS_VECTORS
#define _OPERATIONS_VECTORS

typedef struct{
    int * result;
    int * res;
} Divi_Result;

typedef struct{
    int len;
    int * v;
} Info_Vector;

int * fillZeros(int * v, int lenV);
int * copyVector(int * o, int * d, int len);
void printVector(int * v, int lenV, char * label);
Info_Vector * joinVectors(Info_Vector * a, Info_Vector *b);
int sumElements(Info_Vector * v, int GF);
int checkFirsNonZeroIndex(int * v, int lenV);
Info_Vector * cleanLeftZeros(int * v, int lenV);
Info_Vector * parseInput(char * input, int cleanZerosLeft);
void fillDataRange(int * v, int begin, int end, int data);
int * add(int * a, int lenA, int * b, int lenB, int GF);
void * insertInit(Info_Vector * a, int data);
Info_Vector * multi(int * a, int lenA, int * b, int lenB, int GF);
Info_Vector * multiByElem(Info_Vector * a, Info_Vector * b, int GF);
Divi_Result * divi(int * a, int lenA, int * b, int lenB, int GF);

#include "operations_vectors.h"
#endif