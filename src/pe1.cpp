/** ----------------------------------------------------------------------
 * Copyright 2014 < Ammar Husain (Carnegie Mellon University) > 
 * 
 * @file   pe1.cpp
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu> 
 * @date   Thu Jul 31 17:18:28 2014
 * 
 * @brief  Project Euler #1
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
 * Computes the sum of all multiples of 3 and 5 smaller than input
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 07/31/2014 
 * @param input 
 * 
 * @return 
 ---------------------------------------------------------------------- */
uint64_t sumMultiplesBrute(uint input) {
    uint64_t sum(0);
    
    for (uint i = 1; i < input; i++) {
        if ((i%3 == 0)||(i%5 == 0))
            sum+=i;
    }

    return sum;
}


/** ----------------------------------------------------------------------
 * Uses arithmetic progression to compute the sum of multiples
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 07/31/2014 
 * @param multiple 
 * @param input 
 * 
 * @return 
 ---------------------------------------------------------------------- */
uint64_t arithmeticProgressionSum(uint multiple, uint input) {
    /// compute the number of multiples
    uint64_t n =
        uint(ceil(static_cast<double>(input)/static_cast<double>(multiple)) - 1.0);
    /// get the last number in sequence
    uint64_t last = n*multiple;
    /// compute AP sum
    uint64_t sum = n*(multiple+last)/2;
    
    return sum;
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
        /// compute the actual sum
        uint64_t sum =
            arithmeticProgressionSum(3, input)
            + arithmeticProgressionSum(5, input)
            - arithmeticProgressionSum(15, input);

        std::cout << sum << std::endl;
    }

    return 0;
}

