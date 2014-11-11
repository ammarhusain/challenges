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

using namespace std;


/* Write your custom/own functions here */
bool isSumPossible(vector< int > a , int N) {
    /// embedded for loop: starts from one element after the outer for loop
    for (int i = 0; i < a.size()-1; i++) {
        /// add to all elements following this element
        for (int j = i+1; j < a.size(); j++) {
            std::cout << i << "\t" << j << std::endl;
            
            if (a[i] + a[j] == N)
                return true;  
        }
    }
    
    return false;
    

    
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
    /// keep a timer
    std::clock_t start;
    double duration;

        start = std::clock_t();
        /// do work here

        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        std::cout<< "it took: "<< duration << "s" << std::endl;

        return 0;
}

