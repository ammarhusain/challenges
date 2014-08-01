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


/** ----------------------------------------------------------------------
 * 
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 08/01/2014 
 * @param number 
 * 
 * @return 
 ---------------------------------------------------------------------- */
uint64_t largestPrime(uint64_t number) {
    uint64_t i = 2;
    uint64_t checkLimit = number/i;

    while (i < checkLimit) {
        if (number%i == 0)
            return largestPrime(number/i);

        /// update checkLimit
        checkLimit = number/i;

        /// increment i;
        i++;
    }

    /// number is only divisible by itself
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

    for (uint i = 0; i < numTests; i++) {
        std::cin >> input;
        /// do work here
        uint64_t lq = largestPrime(input);
        std::cout << lq << std::endl;
    }

    return 0;
}

