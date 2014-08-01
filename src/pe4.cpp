/** ----------------------------------------------------------------------
 * Copyright 2014 < Ammar Husain (Carnegie Mellon University) > 
 * 
 * @file   pe1.cpp
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu> 
 * @date   Thu Jul 31 17:18:28 2014
 * 
 * @brief  
 * Project Euler #4: Largest palindrome product
 * 
 ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <ctime>
#include <stdint.h>
#include <iostream>


/** ----------------------------------------------------------------------
 * 
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 08/01/2014 
 * @param array Assumed to be a 6 element array
 * 
 * @return 
 ---------------------------------------------------------------------- */
bool checkSymmetry(uint* array) {
    uint start(0), end(5);
    while (start < end) {
        /// check if they match
        if (array[start] != array[end])
            return false;

        /// update indices
        start++;
        end--;
    }

    /// checks out
    return true;
}

/** ----------------------------------------------------------------------
 * Checks to make sure that the input 6-digit number has 2 3-digit multiples
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 08/01/2014 
 * @param number 
 * 
 * @return 
 ---------------------------------------------------------------------- */
bool lookForMultiples(uint64_t number) {
    for (uint i = 100; i < 1000; i++) {
        if (number % i == 0) {
            /// check if the quotient is 3 digit
            if ((number/i >= 100) && (number/i <= 999))
                return true;
        }
    }

    return false;
}

/** ----------------------------------------------------------------------
 * 
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 08/01/2014 
 * @param input assumed to be a 6 digit number
 * 
 * @return 
 ---------------------------------------------------------------------- */
uint64_t closestPalindrome(uint64_t input) {
    uint numArray[6];
    
    uint64_t smallLimit = 101101;

    /// step through the number and check if it is a palindrome
    for (uint64_t i = input; i >= smallLimit; i--) {
    /// for (uint64_t i = input; i >= input; i--) {
        uint64_t num = i;
        for (uint k = 1; k <= 6; k++) {
            /// extract the kth digit
            numArray[k-1] = num % 10;
            /// std::cout << numArray[k-1] << "\t";
            num = num/10;
        }
        
        /// check symmetry
        if (checkSymmetry(numArray)) {
            /// look for 3-digit multiples
            if (lookForMultiples(i))
                return i;
        }
        
        
    }

    return smallLimit;
    
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

        /// find closest palindrome
        uint64_t cp =  closestPalindrome(input);

        std::cout << cp << std::endl;

        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

