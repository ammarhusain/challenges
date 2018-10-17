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
#include <ctime>





/** ----------------------------------------------------------------------
 * 
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 08/01/2014 
 * @param number 
 * @param N 
 * 
 * @return 
 ---------------------------------------------------------------------- */
bool checkDivisibility(uint64_t number, uint N) {
    /// iterate through and check divisibility by each number
    for (uint i = 2; i <= N; i++) {
        if (number%i != 0)
            return false;
    }
    /// checks out
    return true;
}


uint64_t recursivelyDivide(uint64_t number, uint N) {
    /// counter to incrementally divide with
    uint ctr = N;

    while (ctr > 1) {
        /// check if number can be divided by current ctr
        if (number%ctr == 0) {
            /// check if the divided number is divisible by all numbers
            if (checkDivisibility(number/ctr, N)) {
                number = recursivelyDivide(number/ctr, N);
            }
        }
        ctr--;
    }

    return number;
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

    /// initialize number
    uint64_t number = 1;
    for (uint i = 2; i <= input; i++) {
        number = number*i;
    }

    /// recursively divide
    uint64_t answer = recursivelyDivide(number, input);

    std::cout << answer << std::endl;

    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

