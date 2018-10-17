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



int64_t pythagoreanTriplets(uint N) {
    /// a+b+c = N
    /// break it down into: (a+b)^2 - c^2 = 2ab
    /// and find c
    
    for (uint c = 1; c < N; c++) {
        uint K = N - c;
        /// 2ab has to be less than or equal to K^2/2
        /// since the max value is obtained when a and b ~ K/2
        if (pow(1.0*K, 2.0)/2 < pow(1.0*c, 2.0)) {
            /// get (a+b)^2 - c^2
            uint lhs = pow(K, 2.0) - pow(c, 2.0);
            
            /// initialize a & b by splitting halfway
            int a = floor((1.0*K)/2.0);
            int b = ceil((1.0*K)/2.0);
            while ((a > 0) && (b < K)) {
            if (lhs == 2*a*b)
                return a*b*c;
            /// if not then decrement a & increment b
            a--;
            b++;
            }
        }
        
    }
    
    /// nothing found
    return -1;
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

        int64_t soln = pythagoreanTriplets(input);

        std::cout << soln << std::endl;

        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

