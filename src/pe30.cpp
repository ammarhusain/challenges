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


bool checkDigitPowers(uint64_t number, std::vector<int> powers) {

    uint64_t digits = number;
    uint64_t accumulator = 0;
    
    while (digits > 0) {
        int digit = digits % 10;
        accumulator += powers[digit];
        digits = digits/10;
    }

    return (accumulator == number);

}


uint64_t sumPowers(uint input) {
    /// largest numbers is (9^input)*(input+1)
    /// for example the power=5 can produce at most a 6 digit number
    /// by adding six 9^5.

    uint64_t largestNum = pow(9, input)*(input + 1);
    uint64_t answer = 0;

    /// instantiate a container for powers
    std::vector<int> powers(10);
    for (uint j = 0; j < 10; j++)
        powers[j] = pow(j, input);

    for (uint64_t i = 10; i < largestNum; i++) {
        if (checkDigitPowers(i, powers))
            answer += i;
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
    uint input;

    /// keep a timer
    std::clock_t start;
    double duration;

    std::cin >> input;

    start = std::clock_t();

    /// do work here
    uint64_t answer = sumPowers(input);

    std::cout << answer << std::endl;
    
    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    /// std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

