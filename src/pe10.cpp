/** ----------------------------------------------------------------------
 * Copyright 2014 < Ammar Husain (Carnegie Mellon University) > 
 * 
 * @file   pe1.cpp
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu> 
 * @date   Thu Jul 31 17:18:28 2014
 * 
 * @brief  Boiler Plate
 * 
 * 
 ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <ctime>


bool isPrimeFunc(uint64_t number) {
    /// add special cases
    if (number == 2)
        return true;
    else if (number == 1)
        return false;
    
    uint64_t i = 2;
    uint64_t checkLimit = number;  /// i;

    while (i < checkLimit) {
        if (number%i == 0)
            return false;

        /// update checkLimit
        checkLimit = number/i;

        /// increment i;
        i++;
    }

    /// number is only divisible by itself
    return true;
}


uint64_t inefficientSearch(uint64_t input) {
    uint64_t sumPrimes = 0;

    for (uint64_t i = 1; i <= input; i++) {
        if (isPrimeFunc(i))
            sumPrimes += i;
    }

    return sumPrimes;
}



/** ----------------------------------------------------------------------
 * Not working yet
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 08/03/2014 
 * @param N 
 * 
 * @return 
 ---------------------------------------------------------------------- */
uint64_t sieveOfAtkin(uint64_t N) {
    /// initialize a vector container to hold prime flags
    /// vector is one-indexed - makes it intuitive 
    std::vector<bool> isPrime(N+1, false);

    isPrime[2] = true;
    isPrime[3] = true;
    /// isPrime[5] = true;

    double sqrtN = sqrt(N);

    uint64_t n;
    
    for (uint x = 1; x <= sqrtN; x++) {
        for (uint y = 1; y <= sqrtN; y++) {
            n = (4*pow(x, 2)) + pow(y, 2);
            if ((n <= sqrtN) && ((n%12 == 1) || (n%12 == 5)))
                isPrime[n] = !isPrime[n];

            n = (3*pow(x, 2)) + pow(y, 2);
            if ((n <= sqrtN) && (n%12 == 7))
                isPrime[n] = !isPrime[n];

            n = (3*pow(x, 2)) - pow(y, 2);
            if ((x > y) && (n <= sqrtN) && (n%12 == 11))
                isPrime[n] = !isPrime[n];
        }
    }

    
    /// eliminate composites by sieving
    for (n = 5; n < sqrtN; n++) {
        uint64_t k = pow(n, 2);
        uint ctr = 2;
        while (k < N) {
            isPrime[k] = false;
            k = ctr*k;
        }
    }
    

    /// iterate through the vector and add up
    uint64_t sumPrimes = 0;

    for (uint64_t i = 1; i <= N; i++) {
        std::cout << i << " -> " << isPrime[i] << std::endl;
        
        if (isPrime[i])
            sumPrimes += i;
    }

    return sumPrimes;
}


/** ----------------------------------------------------------------------
 * Working solution: got it from wikipedia
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 08/03/2014 
 * @param N 
 * 
 * @return 
 ---------------------------------------------------------------------- */
uint64_t sieveOfEratosthenes(uint64_t N) {
        
    std::vector<bool> isPrime(N+1, true);

    /// handle 1
    isPrime[1] = false;
    
    double sqrtN = sqrt(N);

    for (uint64_t i = 2; i <= sqrtN; i++) {
        if (isPrime[i]) {
            uint64_t j = pow(i, 2);
            while (j <= N) {
                isPrime[j] = false;
                j = j + i;
            }
        }
    }

    /// iterate through the vector and add up
    uint64_t sumPrimes = 0;

    for (uint64_t i = 1; i <= N; i++) {
        /// std::cout << i << " -> " << isPrime[i] << std::endl;
        if (isPrime[i])
            sumPrimes += i;
    }

    return sumPrimes;
    
}



/** ----------------------------------------------------------------
 * Main Routine
 * 
 * @param argc 
 * @param argv 
 * 
 * @return 
 ---------------------------------------------------------------- */
int main(int argc, char *argv[]) {
    uint numTests;
    std::cin >> numTests;

    uint64_t input;

    /// keep a timer
    std::clock_t start;
    double duration;


    for (uint i = 0; i < numTests; i++) {
        std::cin >> input;

        start = std::clock_t();
        /// do work here

        /// uint64_t sumPrimes = inefficientSearch(input);
        uint64_t sumPrimes = sieveOfEratosthenes(input);
        
        std::cout << sumPrimes << std::endl;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

