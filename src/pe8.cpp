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
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int* splitNumber(const char* number, uint N) {
    int* numberArray = new int(N);
    /// const char* digits = number.c_str();
    const char* digits = number;

    for (uint i = 0; i < N; i++) {
        numberArray[i] = digits[i] - '0';
        /// std::cout << numberArray[i] << std::endl;
    }
    return numberArray;
}


uint64_t kLargestProduct(const int* numberArray, uint N, uint K) {
    /// initialize a max product
    uint64_t maxProd = 0;

    for (uint i = 0; i <= N-K; i++) {
        uint64_t prod = numberArray[i];
        /// start iterating the next K elements
        for (uint j = 1; j < K; j++) {
            prod = prod*numberArray[i+j];
        }

        if (prod > maxProd)
            maxProd = prod;
    }
    
    return maxProd;
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

    uint N, K;
    /// string number;
    /// char* number;
    
    /// keep a timer
    std::clock_t start;
    double duration;


    for (uint i = 0; i < numTests; i++) {
        std::cin >> N >> K;
        
        char* number = new char[N];
        
        std::cin >> number;
        
        start = std::clock_t();
        /// do work here
 
        int* numberArray = splitNumber(number, N);

        uint64_t largestProd = kLargestProduct(numberArray, N, K);

        std::cout << largestProd << std::endl;

        /// cleanup
        delete[] number;
        /// delete[] numberArray;
        
        //delete numberArray;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        //std::cout << "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

