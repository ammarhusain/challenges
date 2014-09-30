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


class BinaryCode {
  public:
    std::vector<std::string> decode(std::string message) {
        std::string zeroStr(message.size());
        zeroStr[0] = '0';

        /// compute the first digit
        zeroStr[1] = (message[0]-'0') - (zeroStr[0]-'0');
        
        /// compute first string with '0'
        for (uint i = 2; i < message.size(); i++) {
            zeroStr[i] = (message[i-1]-'0') - ((zeroStr[i-2]-'0') + (zeroStr[i-1]-'0'));
            if (zeroStr[i] - '0' > 1) {
                /// decode not possible
                zeroStr.clear();
                zeroStr = "NONE";
                break;
            }
        }

        /// create the one string
        std::string oneStr(message.size());
        oneStr[0] = '1';

        /// compute the first digit
        oneStr[1] = (message[0]-'0') - (zeroStr[0]-'0');
        
        /// compute first string with '0'
        for (uint i = 2; i < message.size(); i++) {
            oneStr[i] = (message[i-1]-'0') - ((oneStr[i-2]-'0') + (oneStr[i-1]-'0'));
            if (oneStr[i] - '0' > 1) {
                /// decode not possible
                oneStr.clear();
                oneStr = "NONE";
                break;
            }
        }
        

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

