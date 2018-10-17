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

#define SIZE 20

/** ----------------------------------------------------------------------
 * Takes in a 20x20 matrix
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 08/07/2014 
 * @param matrix 
 * 
 * @return 
 ---------------------------------------------------------------------- */
/// uint64_t getLargestNeighborhood(uint[][] matrix) {
uint64_t getLargestNeighborhood(std::vector< std::vector<uint> > matrix) {
    uint64_t largestSoFar = 0;

    uint64_t prod = 0;
    /// i: rows, j: columns
    
    /// check the horizontal neighbors
    /// iterate rows
    for (uint i = 0; i < SIZE; i++) {
        /// slide through columns
        for (uint j = 0; j <= SIZE-4; j++) {
            prod = matrix[i][j]*matrix[i][j+1]*matrix[i][j+2]*matrix[i][j+3];
            if (prod > largestSoFar)
                largestSoFar = prod;
        }
    }

    /// check the vertical neighbors
    /// iterate columns
    for (uint j = 0; j <= SIZE; j++) {
        /// slide through rows
        for (uint i = 0; i < SIZE-4; i++) {
            prod = matrix[i][j]*matrix[i+1][j]*matrix[i+2][j]*matrix[i+3][j];
            if (prod > largestSoFar)
                largestSoFar = prod;
        }
    }

    /// check the right diagonals
    for (uint i = 0; i < SIZE-4; i++) {
        for (uint j = 0; j <= SIZE-4; j++) {
            prod = matrix[i][j]*matrix[i+1][j+1]*matrix[i+2][j+2]*matrix[i+3][j+3];
            if (prod > largestSoFar)
                largestSoFar = prod;
        }
    }

    /// check the left diagonals
    for (uint i = 0; i < SIZE-4; i++) {
        for (uint j = 4; j <= SIZE; j++) {
            prod = matrix[i][j]*matrix[i+1][j-1]*matrix[i+2][j-2]*matrix[i+3][j-3];
            if (prod > largestSoFar)
                largestSoFar = prod;
        }
    }

    return largestSoFar;
    
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
    /// instantiate a SIZExSIZE matrix
    /// uint matrix[SIZE][SIZE];
    std::vector< std::vector<uint> > matrix(20);
    for (uint i = 0; i < SIZE; i++)
        matrix[i].resize(SIZE);

    /// keep a timer
    std::clock_t start;
    double duration;
    start = std::clock_t();
    /// do work here


    for (uint i = 0; i < SIZE; i++) {
            for (uint j = 0; j < SIZE; j++) {
                std::cin >> matrix[i][j];
                /// std::cin.ignore(1,' ');
            }
    }


    uint64_t answer = getLargestNeighborhood(matrix);


    std::cout << answer << std::endl;

    /*
    for (uint i = 0; i < SIZE; i++) {
        for (uint j = 0; j < SIZE; j++) {
            std::cout << matrix[i][j] << " , ";
        }
        std::cout << std::endl;
    }
    */
    

    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    /// std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

