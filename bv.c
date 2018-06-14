// Aneka Happer
// June 5, 2018
// bv.c

#include <stdio.h>
#include <stdlib.h>
#include "bv.h"

// definition of functions defined in bv.h
bitV *newVec(uint32_t len){
    bitV *myvector = (bitV *) malloc(sizeof(bitV));
    myvector->vector = (uint8_t*) malloc(len * sizeof(uint8_t) / 8 + 1);
    myvector->length = len;
    return myvector;
};

void oneVec(bitV *v){
    int arraylen = v->length / 8 + 1;
    for(int i = 0; i < arraylen; i++){
        v->vector[i] = 0b11111111;
    };
};

void setBit(bitV *v, uint32_t k){
    int i = k/8;
    int pos = k%8;

    uint8_t flag = 1; 

    flag = flag << pos;
    v->vector[i] = v->vector[i] | flag;
};


void clrBit(bitV *v, uint32_t k){
    int i = k/8;
    int pos = k%8;

    uint8_t flag = 1; 

    flag = flag << pos;
    flag = ~flag;

    v->vector[i] = v->vector[i] & flag;
};


uint8_t valBit(bitV *v, uint32_t k){
    int i = k/8;
    int pos = k%8;
    int temp = v->vector[i];

    uint8_t flag = 1;

    temp = temp >> pos;
    temp = temp & flag;

    return temp;
};

uint32_t lenVec(bitV *v){
    int len = v->length;

    return len;
};


uint8_t valBit(bitV *, uint32_t){
    return "0";
};

uint32_t lenVec(bitV *){
    return 0;
};
