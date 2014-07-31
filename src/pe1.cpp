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
int sumMultiples(int input) {
    int sum(0);
    
    for (int i = 0; i < input; i++) {
        if ((i%3 == 0)||(i%5 == 0))
            sum+=i;
    }
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
    int numTests;
    std::cin >> numTests;

    int input, sum;
    
    for (int i = 0; i < numTests; i++) {
        std::cin >> input;
        /// compute the actual sum
        /// std::cout << sumMultiples(input) << std::endl;
        sum = 0;
        for (int i = 0; i < input; i++) {
            if ((i%3 == 0)||(i%5 == 0))
                sum+=i;
        }
        /// return sum;
        std::cout << sum << std::endl;
    }

    return 0;
}

