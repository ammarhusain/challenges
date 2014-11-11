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




void fillFactorial(std::vector<uint64_t>* factorials,
                   int n) {
    factorials->at(n) = n*factorials->at(n-1);
}


uint64_t sumDigitFactorials(uint64_t num,
                            const std::vector<uint64_t>& factorials) {
    uint64_t sum = 0;
    while (num > 0) {
        int digit = num%10;
        sum += factorials[digit];
        num = num/10;
    }

    return sum;
}


uint64_t DigitFactorials()
{
    /// precompute factorials
    std::vector<uint64_t> factorials(10);
    factorials[0] = 1;
    for (uint n = 1; n < 10; n++)
        fillFactorial(&factorials, n);
    
    
    /// lowerbound: 2 digits for adding numbers
    /// upper bound: 7*9! = 2540160
    /// since 8*9! is also a 7 digit number
    uint64_t sum = 0;
    for (uint64_t i = 10; i <= 2540160; i++) {
        if (i == sumDigitFactorials(i, factorials)) {
            std::cout << i << std::endl;
            sum += i;
        }
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
    std::cout << "Boiler-Plate code!" << std::endl;
    
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
        uint64_t answer = DigitFactorials();
        std::cout << answer << std::endl;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

