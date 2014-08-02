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


bool isPrime(uint64_t number) {
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


uint64_t getNthPrime(uint64_t n) {

        uint64_t number(3);
        uint k = 1;
        
        /// do work here
        while (k < n) {

            while (!isPrime(number))
                number++;
            /// found a prime number - increment tracker
            k++;
            number++;
        }

        return number-1;
        
}

uint64_t getNthPrimeSieve(uint64_t n) {
    uint64_t lowerBound = (n*log(1.0*n)) + (n*(log(log(1.0*(n-1))) - 1));
    uint64_t upperBound = (n*log(1.0*n)) + (n*(log(log(1.0*n))));

    for (uint64_t i = lowerBound; i < upperBound; i++) {
        if (isPrime(i))
            return i;
    }
    
    return 0;    

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


        //std::cout << "k: " << k << " num: " << number-1 << std::endl;
        std::cout << getNthPrimeSieve(input) << std::endl;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        //std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

