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
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <ctime>



void getCollatzLength(uint64_t number, std::vector<int>& lookup) {
    /// do this recursively
    /// base condition
    if (lookup[number] != -1) {
        /// do nothing here
    } else if (number%2 == 0) {
        getCollatzLength(number/2, lookup);
        lookup[number] = lookup[number/2] + 1;
    } else {
        uint64_t newNum = (3*number)+1;
        if (newNum >= lookup.size()) {
            uint ctr = 1;
            /// reduce the number until it fits in the array
            while (newNum >= lookup.size()) {
                if (newNum%2 == 0)
                    newNum = newNum/2;
                else
                    newNum = (3*newNum)+1;
                ctr++;
            }
            /// do a lookup on smaller number and increment by ctr
            getCollatzLength(newNum, lookup);
            lookup[number] = lookup[newNum] + ctr;
        } else {
            getCollatzLength(newNum, lookup);
            lookup[number] = lookup[newNum] + 1;
        }
        
    }

    return;
}


int getMaxCollatzSequence(uint64_t number, std::vector<int>& lookup) {
    std::pair<uint64_t, int> maxSoFar(1, 0);
    
    for (uint64_t i = 2; i <= number; i++) {
        /// std::cout << "i: " << i << std::endl;
        
        if (lookup[i] == -1) {
            /// compute the collatz sequence length
            getCollatzLength(i, lookup);
        }
        /// can look this number up now
        if (lookup[i] >= maxSoFar.second)
            maxSoFar = std::make_pair(i, lookup[i]);

    }

    return maxSoFar.first;
    
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
    start = std::clock_t();
    /// do work here


    /// instantiate one vector for DP
    /// treat array as 1-indexed
    /// std::vector<int> lookup(4*5*pow(10, 6)+1, -1);
    std::vector<int> lookup(5*pow(10, 6)+1, -1);
        
    /// has to end with 1: unproven Collatz conjecture
    lookup[1] = 0;
    
    
    for (uint i = 0; i < numTests; i++) {
        std::cin >> input;


        getCollatzLength(input, lookup);
        int answer = getMaxCollatzSequence(input, lookup);
        
        std::cout << answer << std::endl;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

