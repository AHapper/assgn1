// assign1 main file
// parfait.c
#include <stdint.h>
#include <stdio.h>
#include "bv.h"

int main(void){
    
    bitV *myvector1 = newVec(800);

    printVector(myvector1); 
  
    printf("Size of bitV: %lu\n", sizeof(bitV)); // check to see if on the right track   
 
    printf("Size of vector1: %lu\n", sizeof(myvector1)); // check to see if on the right track

    return 0;
 
};
