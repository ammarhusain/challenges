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
uint sumMultiplesBrute(uint input) {
    uint sum(0);
    
    for (uint i = 0; i < input; i++) {
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
uint arithmeticProgressionSum(uint multiple, uint input) {
    /// compute the number of multiples
    uint n =
        uint(ceil(static_cast<double>(input)/static_cast<double>(multiple)) - 1.0);
    /// get the last number in sequence
    uint last = n*multiple;
    /// compute AP sum
    uint sum = n*(multiple+last)/2;

    std::cout << "m: " << multiple << " i: " << input << " s: " << sum << " n: " << n << std::endl;
    
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

    uint input;
    
    for (uint i = 0; i < numTests; i++) {
        std::cin >> input;
        /// compute the actual sum
        uint sum = arithmeticProgressionSum(3, input) + arithmeticProgressionSum(5, input) - arithmeticProgressionSum(15, input);
        std::cout << sum << std::endl;
        std::cout << "brute: " << sumMultiplesBrute(input) << std::endl;

    }

    return 0;
}

