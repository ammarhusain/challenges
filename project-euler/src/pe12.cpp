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

uint getNumFactors(uint64_t number) {
    /// handle edge case
    if (number == 1)
        return 1;

    uint factors = 0;
    
    /// just for debugging keep track of the divisors you get
    std::vector<uint> divList;
    
    int divisor = 1;
    int quotient = number;

    while (divisor <= quotient) {
        if (number%divisor == 0) {
            quotient = number/divisor;
            divList.push_back(divisor);
            divList.push_back(quotient);
            if (divisor == quotient)
                factors+=1;
            else
                factors+=2;
        }
        divisor++;
        /// quotient = ceil((1.0*number)/divisor);
        
    }

    /*
    std::cout << "tri #: " << number
              << " factors: " << factors
              << std::endl;
    */
    return factors;
    
}

uint64_t smalledTriangleNumber(uint input) {
    uint ctr = 1;
    uint64_t triNum = ctr;
    /// increment counter
    ctr++;
    
    while (getNumFactors(triNum) <= input) {
        triNum += ctr;
        ctr++;
        /// std::cout << "#: " << ctr << std::endl;
        
    }

    return triNum;

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

    /// keep a timer
    std::clock_t start;
    double duration;


    for (uint i = 0; i < numTests; i++) {
        std::cin >> input;

        start = std::clock_t();
        
        /// do work here
        uint64_t answer = smalledTriangleNumber(input);

        std::cout << answer << std::endl;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

