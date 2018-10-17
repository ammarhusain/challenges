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
#include <queue>

using namespace std;

struct coordinate {
    int x;
    int y;
    
};


int numberOfPaths(int a[][100],int M, int N) {
    
    /// instantiate a matrix the size of a
    /// using vector of vector because its just convenient
    vector< vector<int> > matrix(M);
    /// initialize all elements to 0
    for (int i = 0; i < M; i++)
        matrix[i].resize(N, 0);

    /// set the first element to 0
    /// matrix[0][0] = 0;
    
    
    /// use a queue to queue up possible grids to enter
    queue<coordinate> togo;

    /// put your position in togo
    /// just do that you are not adding stuff outside the loop
    coordinate current;
    current.x = 0;
    current.y = 0;
    togo.push(current);
    /// initial value for starting position
    matrix[0][0] = -1;
    
    /// keep going till we have nowhere to go
    while(togo.size() > 0) {
        /// get the first position on the queue
        coordinate next = togo.front();
        togo.pop();

        /// increment the counter of getting here by
        matrix[next.x][next.y] += 1;

        coordinate newGrid;
        /// where else can we go
        /// right?
        if (next.x+1 < M) {
            if (a[next.x+1][next.y]){
                newGrid.x = next.x+1;
                newGrid.y = next.y;
                togo.push(newGrid);
            }
        }
        
        /// down?
        if (next.y+1 < N) {    
            if (a[next.x][next.y+1]){
                newGrid.x = next.x;
                newGrid.y = next.y+1;
                togo.push(newGrid);
            }
        }
        
    }

    /// number of ways is the last element of the matrix
    return matrix[M-1][N-1];
    
        
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

        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

