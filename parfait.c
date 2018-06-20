// Aneka Happer
// June 14, 2018
// parfait.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bv.h"
#include "sieve.h"

int()

int zerocheck(int alpha[], int b); // checks value of alpha array

int sumfactors(int p[], int alphamax[], int alpha[], int b); // sums all factors of a number (i) by multipling all unqiue combinations of prime factors 


int main(void){
        
    // creates new vector with 100,000 bits
    bitV *vector1 = newVec(100000);

    // matches vector with integers and filters so all prime numbers are "1" and all composite are "0"
    sieve(vector1);

    // an array used to print prime factors of composite numbers
   int *factor;
   factor = (int *) malloc(sizeof(int)*100000);
   
   factor[0] = 1;
   factor[1] = 1;

    // used in "sumfactors" 
    int p[10]; // array of all unique prime factors of a number i 
    int alpha[10]; // array stores the number of each unique prime, changed later
    int alphamax[10]; // array stores the number of each unique prime, does not change
    int b; // constant 
 
    // creates "factor" array, goes through bits in "vector1", if bit = 0, a number, i, is composite, factor[i] = i/k 
    // where k is the smallest prime factor of i. used later to print prime factors of i.
    for(int i = 2; i < 500; i++){
        
       if(valBit(vector1, i) == 1){
           factor[i] = 1;
       }

       else{
           
           int t = 1; // t used to break loop 
           int k = 2; // initializes k as first prime number, 2, so loop can find smallest prime factor, k, by incrimenting k

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

    // determines if integer is prime using bitvector and prints, if composite, uses "factor" array to print 
    // prime factors: a/factor[a] = "primef" (prime factor), where a = i and repeats to find all prime factors
    // there are a few additions to this loop aside from the print statements that will help when finding perfect 
    // numbers and printing their factors
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
            p[0] = a/factor[a]; // sets first element of array "p" equal to first prime factor, array "p" stores all unique prime 
                                // factors of i so they can be used to find all factors of a number, i 
            alphamax[0] = 1; // "alpha" and "alphamax" store how many of each unique prime i has (eg. if i = 4 or 2^2, p[0] = 2, alpha[0] = 2)
            alpha[0] = 1; // same as "alphamax" but is subject to change during function "sumfactors"

            // infinite loop to find all prime factors of a number, i. The "factor" array stores the factor pair of the smallest prime factor of i
            // so it can be used to keep finding prime factors until the factor pair is prime (factor[a] = 1 where a is prime) 
            for(;;){
                count++;

                primef = a/factor[a];

                printf("%d ", primef);
                
                // creates "p", "alphamax", and "alpha" arrays 
                // p array holds unique prime factors, alpha/alphamax holds the number of a specified factor, if the first element of "p" is a prime
                // factor, "alpha" and "alphamax" are incrimented, if not, "p" is incrimented to the next element to store the next unique prime
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

        // checks to see if number is perfect by using the function "sumfactors" and comparing the result to the number, i. 

        // only checks composite numbers 
        if(valBit(vector1, i) == 0){

            int sum = sumfactors(p, alphamax, alpha, b) - i; // sumfactors sums all factors of a nubmer including itself, so i must be subtracted to see if it is perfect 

            // prints factors of found perfect number if "sumfactors" determines the sum and it is equal to i  
            if(sum == i){

                printf("%d E:", i); 
                
                // finds all factors of a number, i, by multipling all unique combination of the prime factors of i 
                // and stores them, this is only after the number is determined perfect so the program does not unnecessarily
                // store the factors of every composite number i. 
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
// sums all factors of a number, i, by multiplying all unqiue combinations of it's prime factors
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
