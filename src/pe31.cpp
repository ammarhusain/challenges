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


uint64_t dpChange(const std::vector<int>& currency, int m , int n) {
    /// instantiate a table for meoization
    std::vector< std::vector<uint64_t> > tab(n+1);
    tab[0].resize(m, 1);
    
    /// store zero values
    for (uint i = 1; i < tab.size(); i++)
        tab[i].resize(m, 0);

    /// two possible substructures
    /// i) it contains the mth coin .. the value n goes down by curr[m]
    /// ii) mth coin is not an option to use

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {

            /// std::cout << i << "\t" << j << std::endl;
            /// std::cout << i - currency[j] << std::endl;
            
            int subOne(0), subTwo(0);
            if (i - currency[j] >= 0)
                subOne = tab[i-currency[j]][j];
            if (j > 0)
                subTwo = tab[i][j-1];
            tab[i][j] = subOne + subTwo;
        }
    }
    
    return (tab[n][m-1])%static_cast<int>(pow(10,9)+7);
    

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

    std::vector<int> currency(8);
    currency[0] = 1;
    currency[1] = 2;
    currency[2] = 5;
    currency[3] = 10;
    currency[4] = 20;
    currency[5] = 50;
    currency[6] = 100;
    currency[7] = 200;
    
    /// keep a timer
    std::clock_t start;
    double duration;


    for (uint i = 0; i < numTests; i++) {
        std::cin >> input;

        start = std::clock_t();
        /// do work here

        uint64_t answer = dpChange(currency, 8, input);
        std::cout << answer << std::endl;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

