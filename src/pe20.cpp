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


void multiply(std::vector<uint>& largeNumber, uint i) {
    uint prod = 0;
    uint quotient = 0;

    /// std::cout << "i: " << i << std::endl;
    /*
    uint ctr = 0;    
    do {
        prod = largeNumber[ctr] * i;
        largeNumber[ctr] = (quotient+prod)%10;
        std::cout << largeNumber[ctr] << "\t";
        quotient = (quotient+prod)/10;
        ctr++;
        
    } while (prod != 0);
    */

    for (uint ctr = 0; ctr < largeNumber.size(); ctr++) {
        prod = largeNumber[ctr] * i;
        largeNumber[ctr] = (quotient+prod)%10;
        /// std::cout << largeNumber[ctr] << "\t";
        quotient = (quotient+prod)/10;
    }


    /// for (uint i = 0; i < largeNumber.size(); i++)
    /// std::cout << largeNumber[i] << "\t";
    /// std::cout << std::endl;

}


uint64_t sumDigits(uint N) {
    /// instantiate a container to hold the factorial
    std::vector<uint> factorial(5000,0);

    factorial[0] = 1;

    for (uint i = 1; i <= N ; i++) {
        multiply(factorial, i);
    }


    uint64_t sum = 0;
    for (uint j = 0; j < factorial.size(); j++) {
        sum += factorial[j];
        /// std::cout << factorial[j] << " ";
    }

    /// std::cout << std::endl;
    
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

    uint64_t N;

    /// keep a timer
    std::clock_t start;
    double duration;


    for (uint i = 0; i < numTests; i++) {
        std::cin >> N;

        start = std::clock_t();
        /// do work here

        uint64_t answer = sumDigits(N);
        
        std::cout << answer << std::endl;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

