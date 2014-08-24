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


uint computeAndAdd(uint power) {
    std::vector<uint64_t> largeNum(1500, 0);

    largeNum[0] = 1;

    for (uint i = 1; i <= power; i++) {
        uint remn = 0;
        uint multiple = 0;
        /// multiply the large num by 2
        for (uint j = 0; j < largeNum.size()-1; j++) {
            multiple = 2*largeNum[j];
            largeNum[j] = (multiple+remn)%10;
            remn = (multiple+remn)/10;
        }

        /// for the last element store the whole number
        multiple = 2*largeNum[largeNum.size()-1];
        largeNum[largeNum.size()-1] = multiple + remn;
    }

    uint answer = 0;
    uint64_t lastElem = largeNum[largeNum.size()-1];
    /// add the sum of digits of the last element
    while (lastElem > 0) {
        answer += lastElem%10;
        lastElem = lastElem/10;
    }
    
    /// iterate through and add the rest of the number
    for (int k = largeNum.size()-2; k >= 0; k--) {
        answer += largeNum[k];
    }

    /*
    for (int k = largeNum.size()-1; k >= 0; k--) {
        std::cout << largeNum[k];
    }
    std::cout << std::endl;
    */
    return answer;
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

        uint answer = computeAndAdd(input);
        
        std::cout << answer << std::endl;
        
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

