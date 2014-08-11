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
    std::vector<uint> largeNum(5000, 0);

    largeNum[0] = 1;

    for (uint i = 1; i <= power; i++) {
        uint remn = 0;
        /// multiply the large num by 2
        for (uint j = 0; j < largeNum.size(); j++) {
            uint multiple = 2*largeNum[j];
            largeNum[j] = (multiple+remn)%10;
            remn = (multiple+remn)/10;
        }
    }

    uint answer = 0;
    /// iterate through and add the number
    for (int k = largeNum.size()-1; k >= 0; k--) {
        answer += largeNum[k];
    }

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

