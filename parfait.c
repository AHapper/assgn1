// Aneka Happer
// June 14, 2018
// parfait.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bv.h"
#include "sieve.h"

// zerocheck function defined below, credited to J. Happer
int zerocheck(int alpha[], int b); // checks value of alpha array
// sumfactors function defined below, credited to J. Happer
int sumfactors(int p[], int alphamax[], int alpha[], int b); // sums all factors of a number (i) by multipling all unqiue combinations of prime factors 


int main(void){
        
    // creates new vector wiht 100,000 bits
    bitV *vector1 = newVec(100000);

    // matches vector with integers so all prime numbers are "1" and all composite are "0"
    sieve(vector1);

    // an array used to print prime factors of composite numbers
   int *factor;
   factor = (int *) malloc(sizeof(int)*100000);

    // used in "sumfactors" 
    int p[10];
    int alpha[10];
    int alphamax[10];
    int b;

   factor[0] = 1;
   factor[1] = 1;

   // creates "factor" array
   for(int i = 2; i < 500; i++){
        
       if(valBit(vector1, i) == 1){
           factor[i] = 1;
       }
       else{
           int t = 1;
           int k = 2; 
           for(;;){
               if(valBit(vector1, k) == 1){
                   if(i%k == 0){
                        factor[i] = i/k;
                        t = 0;
                    }
                }
                k++;
                if(t == 0) break;
           }
       }
    }

    // prints results
    for(int i = 2; i < 500; i++){
        if(valBit(vector1, i) == 1){
            printf("%d P", i);
        }
        else{
            printf("%d C: ", i);
            int a = i;
            int primef = 0;
            int count = 0;

            b = 0; 

            p[0] = a/factor[a];
            alphamax[0] = 1;
            alpha[0] = 1;
            for(;;){
                count++;
                primef = a/factor[a];
                printf("%d ", primef);
                
                // creates "p", "alphamax", and "alpha" arrays 
                // p array holds unique prime factors, alpha/alphamax holds the number of a specified factor
                if(p[b] == primef){
                    if(count != 1){
                        alphamax[b]++;
                        alpha[b]++;
                    }
                }
                else{
                    b++;
                    p[b] = primef;
                    alphamax[b] = 1;
                    alpha[b] = 1;
                }

                if(factor[a] == 1) break;

                a = a/primef;
            }
        }
        printf("\n");

        // checks to see if number is perfect
        if(valBit(vector1, i) == 0){
            int sum = sumfactors(p, alphamax, alpha, b) - i;
            // prints factors of found perfect number
            if(sum == i){
                printf("%d E:", i);
                for(int n = 0; n <= b; n++){
                    alpha[n] = alphamax[n];
                }
                int array[100];
                int count2 = 0; 
                for(;;){
                    int afactor = 1;
                    for(int n = 0; n <= b; n++){  
                        afactor *= pow(p[n], alpha[n]);
                    }
                    
                    // creates "array" which stores factors
                    if(afactor != i){
                        array[count2] = afactor;
                    }

                    if(alpha[b] != 0){
                        alpha[b]--;
                    }
                    else{
                        int place = zerocheck(alpha, b);
                        if(place == -1){
                            break;
                        }
                        else{
                            alpha[place]--;
                            for(int n = place + 1; n <= b; n++){
                                alpha[n] = alphamax[n];
                            }
                        }
                    }
                    count2++;
                }

                // organizes "array" in ascending order, creditied to thenewboston (Bucky Roberts)
                for(;;){
                    int swap = 0;
                    for(int c = 1; c < count2; c++){
                        if(array[c]>array[c+1]){
                            int temp = array[c];
                            array[c] = array[c+1];
                            array[c+1] = temp;
                            swap = 1;
                        }
                    }
                    if(swap == 0) break;
                }
                for(int c = 1; c <= count2; c++){
                    printf(" %d", array[c]);
                }
                printf("\n");
            }
        }
    }
    return 0;
 
};

// "zerocheck". creditied to J. Happer
int zerocheck(int alpha[], int b){
    for(int i = b - 1; i >= 0; i--){
        if(alpha[i] != 0){
            return i;
        }
    } 
    return -1;
}

// "sumfactors", credited to J. Happer
int sumfactors(int p[], int alphamax[], int alpha[], int b){
    int sum = 0;
    for(;;){
        int afactor = 1;
        for(int n = 0; n <= b; n++){  
            afactor *= pow(p[n], alpha[n]);
        }
        sum += afactor;

        if(alpha[b] != 0){
            alpha[b]--;
        }
        else{
            int place = zerocheck(alpha, b);
            if(place == -1){
                return sum;
            }
            else{
                alpha[place]--;
                for(int n = place + 1; n <= b; n++){
                    alpha[n] = alphamax[n];
                }
            }
        }
    }
}
