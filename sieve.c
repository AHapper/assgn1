// Aneka Happer
// June 5, 2018
// sieve.c
// from assign1, credited to D. Long

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bv.h"
#include "sieve.h"

// Sieve of Eratosthenes
void sieve(bitV *v) 
{
    oneVec(v); // Assume all are prime
    clrBit(v, 0); // 0 is, well, zero
    clrBit(v, 1); // 1 is unity
    setBit(v, 2); // 2 is prime
    for (uint32_t i = 2; i <= sqrtl(lenVec(v)); i += 1)
    {
        if (valBit(v, i)) // It’s prime 
        {
            for (uint32_t k = 0; (k + i) * i <= lenVec(v); k += 1) 
            {
                clrBit(v, (k + i) * i); // Its multiple are composite
            }
        }
    }
return ;
}
