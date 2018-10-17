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
#include <utility>


std::pair< std::vector<uint>, uint >
computeFibonacci(const std::pair< std::vector<uint>, uint >& fib,
                 const std::pair< std::vector<uint>, uint >& prevFib) {

    uint i = 0;
    uint carry = 0;

    std::pair< std::vector<uint>, uint > newNum;
    newNum.first.resize(5000);
    
    while((i < fib.second) || (carry != 0)) {
        newNum.first[i] = (fib.first[i] + prevFib.first[i] + carry)%10;
        carry = (fib.first[i] + prevFib.first[i] + carry)/10;
        i++;
    }

    newNum.second = i;

    /*
    std::cout << "ns " << newNum.second << std::endl;
    for (int k = 10; k >= 0; k--)
        std::cout << newNum.first[k];
    std::cout << std::endl;
    */
    
    return newNum;

}


uint getFibonacci(uint input) {
    std::pair< std::vector<uint>, uint > fib;
    fib.first.resize(5000);
    /// initialize to 1
    fib.first[0] = 1;
    fib.second = 1;

    
    std::pair< std::vector<uint>, uint > prevFib;
    prevFib.first.resize(5000);
    /// initialize to 1
    prevFib.first[0] = 1;
    prevFib.second = 1;

    std::pair< std::vector<uint>, uint > newNum;
    
    uint number = 2;
    
    
    do {
        /// std::cout << number << " " << fib.second << std::endl;
        
        newNum = computeFibonacci(fib, prevFib);
        prevFib = fib;
        fib = newNum;
        number++;
    } while (fib.second < input);

    /*
    std::cout << fib.second << std::endl;
    
    for (int k = 10; k >= 0; k--)
        std::cout << fib.first[k];
    std::cout << std::endl;
    */
    
    return number;
    

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
        uint answer = getFibonacci(input);

        std::cout << answer << std::endl;
        
        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        /// std::cout<< "it took: "<< duration << "s" << std::endl;
    }

    return 0;
}

