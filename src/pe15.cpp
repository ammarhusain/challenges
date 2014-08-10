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
#include <queue>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <ctime>


uint64_t getNumPaths(uint N, uint M) {
    std::vector< std::vector< std::pair<bool, uint64_t> > > matrix;
    
    /// instantiate the matrix
    matrix.resize(N+1);
    for (uint k = 0; k <= N; k++) {
        matrix[k].resize(M+1, std::make_pair(false, 0));
    }
    
    /// instantiate a queue of cells to explore
    std::queue< std::pair<int, int> > cells;
    
    /// add the left element
    matrix[N-1][M] = std::make_pair(true, 1);
    cells.push(std::make_pair(N-1, M));

    /// add the top element
    matrix[N][M-1] = std::make_pair(true, 1);
    cells.push(std::make_pair(N, M-1));

    /// keep iterating until there is nothing left on queue
    while (cells.size() > 0) {
        /// get the elements from the front of the queue
        std::pair<int, int> currentCell = cells.front();

        /// remove the head of the queue
        cells.pop();

        int x = currentCell.first;
        int y = currentCell.second;
        
        /// std:: cout << x << "  " << y
        ///           << " val: " << matrix[x][y].second << std::endl;
        
        /// can we go left?
        if (x-1 >= 0) {
            matrix[x-1][y].second += matrix[x][y].second;
            /// if not already visited -add this to the queue
            if (!matrix[x-1][y].first) {
                cells.push(std::make_pair(x-1, y));
                matrix[x-1][y].first = true;

                /// std:: cout << "added --> " << x-1 << "  " << y
                /// << " val: " << matrix[x-1][y].second << std::endl;
            }
        }
        /// can we go up?
        if (y-1 >= 0) {
            matrix[x][y-1].second += matrix[x][y].second;
            /// if not already visited -add this to the queue
            if (!matrix[x][y-1].first) {
                cells.push(std::make_pair(x, y-1));
                matrix[x][y-1].first = true;
                /// std:: cout << "added --> " << x << "  " << y-1
                /// << " val: " << matrix[x][y-1].second << std::endl;
            }
        }
        

    }

    return matrix[0][0].second;

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


    /// keep a timer
    std::clock_t start;
    double duration;

    uint N, M;
    
    for (uint i = 0; i < numTests; i++) {
        start = std::clock_t();
        /// do work here

        std::cin >> N >> M;

        uint64_t answer = getNumPaths(N, M);

        std::cout << answer%static_cast<uint64_t>(pow(10, 9) + 7)<< std::endl;
        std::cout << answer << std::endl;

        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

