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


void addNumbers(std::vector< std::vector<uint> > numbers, std::vector<uint>& sum) {
    sum.resize(50, 0);
    /// return;
    
    uint adder = 0;
    uint remn = 0;
    /// iterate through the digits
    for (uint j = 0; j < 50; j++) {
        /// iterate and add the numbers
        for (uint i = 0; i < numbers.size(); i++) {
            adder+= numbers[i][j];
        }
        sum[j] = adder%10;
        remn = adder/10;
        adder = remn;
    }

    
    /// push the remn over sum
    /// iterate while a single digit is remn
    while (remn != 0) {
        sum.push_back(remn%10);
        remn = remn/10;
    }
    
}


/** ----------------------------------------------------------------------
 * Expects a 50 character string
 * 
 * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
 * @date 08/09/2014 
 * @param input 
 * 
 * @return 
 ---------------------------------------------------------------------- */
void convertToNumber(std::string input, std::vector<uint>& number) {
    number.resize(50);
    
    /// the 50th character should be the zeroth index
    /// do a roll over
    for (uint i = 0; i < 50; i++) {
        uint idx = abs(i-(50-1));
        number[idx] = input[i] - '0';
        /// number[idx] = atoi(&input[i]);
    }
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
    
    uint numNumbers;
    std::cin >> numNumbers;

    /// use a matrix to store the numbers
    std::vector< std::vector<uint> > allNumbers(numNumbers);    

    for (uint i = 0; i < numNumbers; i++) {
        /// read the line as a string
        std::string input;
        std::cin >> input;
        convertToNumber(input, allNumbers[i]);

        /*
        /// debug print
        for (uint j = 0; j < 50; j++) 
            std::cout << allNumbers[i][j];
        std::cout << std::endl;
        */
    }

    std::vector<uint> sum(50,0);
    addNumbers(allNumbers, sum);

    
    /// print the first 10 numbers
    for (uint i = sum.size()-1; i > sum.size()-11; i--)
            std::cout << sum[i];
    /*
    /// print the first 10 numbers
    /// for (uint i = sum.size()-1; i > sum.size()-11; i--)
    for (int i = (sum.size()-1); i >= 0; i--) {
        std::cout << sum[i];
        /// sleep(1);
        
    }
    std::cout << std::endl;
    */

    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    /// std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

