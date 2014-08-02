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



uint64_t DiffSumSquares(uint64_t N) {
    ///
    uint64_t multiplier(0);
    for (uint64_t i = 0; i <= N; i++) {
        /// multiply this index with all the upcoming ones
        for (uint64_t j = i+1; j <= N; j++) {
            multiplier += i*j;
        }
    }

    return 2*multiplier;
}


uint64_t DiffSumSquaresLinear(uint64_t N) {
    ///
    uint64_t multiplier(0), addendum(0);
    for (uint64_t i = N-1; i >= 1; i--) {
        addendum += i+1;
        multiplier += (i*addendum);
    }

    return 2*multiplier;
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
        std::cout << DiffSumSquaresLinear(input) << std::endl;

        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

