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

/// Project-Euler answer = 1704

int64_t getMaxPath(std::vector< std::vector<int> > triangle) {
    /// instantiate a memoization container for each level
    std::vector<int> maxAtLevel;

    /// initialize a previous level container
    std::vector<int> prevLevel(1);
    prevLevel[0] = triangle[0][0];
    
    for (uint l = 1; l < triangle.size(); l++) {
        /// instantiate a memoization container for this level
        maxAtLevel.resize(l+1);

        maxAtLevel[0] = prevLevel[0] + triangle[l][0];
        for (uint k = 1; k <= l-1; k++) {
            maxAtLevel[k] = std::max(prevLevel[k-1], prevLevel[k]) + triangle[l][k];
            /// std::cout << "lk p: " << l << " " << k << " "
            ///           << std::max(prevLevel[k-1], prevLevel[k])
            /// << std::endl;
        }
        maxAtLevel[l] = prevLevel[l-1] + triangle[l][l];


        /// print the level for debugging
        /// for (uint i = 0; i < maxAtLevel.size(); i++) 
            /// std::cout << maxAtLevel[i] << "\t";
        /// std::cout << std::endl;
        
        /// reassign the previous level container
        prevLevel.assign(maxAtLevel.begin(), maxAtLevel.end());
    }


    int64_t currentMax = maxAtLevel[0];
    /// iterate through the last level and find the greatest element
    /// could ideally be done in previous iteration itself
    /// just keeping the code clean by separating it out
    for (uint i = 1; i < maxAtLevel.size(); i++) {
        if (maxAtLevel[i] > currentMax)
            currentMax = maxAtLevel[i];
    }
    return currentMax;
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
        start = std::clock_t();
        /// do work here

        std::cin >> N;

        std::vector< std::vector<int> > triangle(N);
        
        for (uint j = 1; j <= N; j++) {
            /// resize vector to fit j elements
            triangle[j-1].resize(j);
            for (uint k = 0; k < j; k++) {
                std::cin >> triangle[j-1][k];
            }
        }


        int64_t answer = getMaxPath(triangle);
        

        std::cout << answer << std::endl;

        /*
        /// reprint the input for debugging
        for (uint l = 0; l < triangle.size(); l++) {
            for (uint k = 0; k < triangle[l].size(); k++) {
                std::cout << triangle[l][k] << "\t";
            }
            std::cout << std::endl;
        }
        */

        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

