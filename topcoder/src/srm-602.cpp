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
#include <iostream>
#include <vector>

#include <ctime>


using namespace std;


class TypoCoderDiv2 {
  public:
    int count(vector<int> rating) {
        int current = floor((double)rating[0]/1200.0);
        int change = 0;
        if (current > 0)
            change++;
        
        for (int i = 1; i < rating.size(); i++) {
            int newR = floor((double)rating[i]/1200.0);
            if (newR > 1)
                newR = 1;
            
            if (current != newR) {
                change++;
                current = newR;
            }
        }
        
        return change;

    }
    

};

    

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
    /// keep a timer
    std::clock_t start;
    double duration;

    start = std::clock_t();
    /// do work here

    vector<int> test(2);

    test[0] = 1330;
    test[1] = 1200;

    TypoCoderDiv2 tc;
    tc.count(test);
    
    
    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

