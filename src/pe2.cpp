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

void recursiveFibonacci(uint64_t l1, uint64_t l2,
                            uint64_t& sum, const uint64_t& n) {

    uint64_t newNum = l1 + l2;

    if (newNum > n)
        return;

    if (newNum%2==0)
        sum += newNum;

    /// call recursively
    recursiveFibonacci(newNum, l1, sum, n);

    return;
    
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

        uint64_t sum;
        /// initialize to 2 (sum of evens between 1 & 2)
        sum = 2;
        
        /// do work here
        recursiveFibonacci(2, 1, sum, input);

        std::cout << sum << std::endl;
        
    }

    return 0;
}

