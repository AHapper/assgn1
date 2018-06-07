// assign1
// bv.c
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"

bitV *newVec(uint32_t len){
    int len_b = len/8;
    bitV *myvector = malloc(sizeof(bitV) + len_b * sizeof(uint8_t));
    int sum = sizeof(bitV) + len_b * sizeof(uint8_t);
    printf("the sum is %d\n", sum); // check to make sure malloc is accurate
    myvector->length = len;
    for (int i = 0; i < len_b; i++){
    //    myvector->vector[i] = 0;
    };
    return myvector;
};

void printVector(bitV *myvector)
{
    printf("length : %d\n",myvector->length); // check 
    printf("vector : %s\n",myvector->vector); // check
}
 
// commented out for now 
/* void delVec(bitV *){ 

};

void oneVec(bitV *){

};

void setBit(bitV *, uint32_t){

};

void clrBit(bitV *, uint32_t){

};

uint8_t valBit(bitV *, uint32_t){
    return "0";
};

uint32_t lenVec(bitV *){
    return 0;
};

*/
