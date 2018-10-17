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

uint64_t sumMatrixDiagonals(uint input) {

    uint64_t sum = 1;
    uint64_t lastElem = 1;
    uint n = 2;    
    while (n < input) { 
        for (uint i = 1; i <=4; i++) {
            sum += lastElem + (i*n);
            /// std::cout << (lastElem + (i*n)) << std::endl;
        }
        lastElem = lastElem + (4*n);
        n += 2;
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

        uint64_t answer = sumMatrixDiagonals(input);

        std::cout << answer << std::endl;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

