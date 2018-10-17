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
#include <algorithm>
#include <string>


class SwitchingBits {
  public:
    int minSwitches(std::vector <std::string> s) {
        std::string code;
        /// concatenate the string into one
        for (uint i = 0; i < s.size(); i++)
            code.append(s[i]);

        /// now iterate through the characters and count contiguous regions
        /// the size of each region does not matter
        int contig[2];
        contig[0] = 0;
        contig[1] = 0;        

        char region = code[0];
        for (uint i = 1; i < code.size(); i++) {
            if (region - code[i] != 0) {
                contig[region-'0'] += 1;
                region = code[i];
            }
        }
        /// add the region for last character
        contig[region-'0'] += 1;

        std::cout << contig[0] << "\t" << contig[1] << std::endl;

        if (contig[0] < contig[1])
            return contig[0];
        else
            return contig[1];
        
    }

};


class Cannons {
  public:
    std::string getDirections(std::vector<int> x, std::vector<int> y) {
        std::string direction;
        
        /// iterate through all the canons
        for (uint i = 0; i < x.size(); i++) {
            /// get an index
            uint j;

            /// check down direction
            for (j = 0; j < x.size(); j++) {
                /// check for self
                if (i == j)
                    continue;
                if (x[i] == x[j]) {
                    /// if y is less cannot go down
                    if (y[i] > y[j])
                        break;
                }
            }
            /// if all indices have been iteerated
            if (j == x.size()) {
                direction.append("D");
                continue;
            }
            
                
            /// check left direction
            for (j = 0; j < x.size(); j++) {
                /// check for self
                if (i == j)
                    continue;
                if (y[i] == y[j]) {
                    /// if y is less cannot go down
                    if (x[i] > x[j])
                        break;
                }
            }
            /// if all indices have been iteerated
            if (j == x.size()) {
                direction.append("L");
                continue;
            }
            
            /// check right direction
            for (j = 0; j < x.size(); j++) {
                /// check for self
                if (i == j)
                    continue;
                if (y[i] == y[j]) {
                    /// if y is less cannot go down
                    if (x[i] < x[j])
                        break;
                }
            }
            /// if all indices have been iteerated
            if (j == x.size()) {
                direction.append("R");
                continue;
            }

            /// check up direction
            for (j = 0; j < x.size(); j++) {
                /// check for self
                if (i == j)
                    continue;
                if (x[i] == x[j]) {
                    /// if y is less cannot go down
                    if (y[i] < y[j])
                        break;
                }
            }
            /// if all indices have been iteerated
            if (j == x.size()) {
                direction.append("U");
                continue;
            }

            /// if you ve reached here - no direction is possible
            break;
            
        }
        
        if (direction.size() != x.size())
            direction = "";
        
        return direction;

    }

};

    

class Fractile {
  public:
    int fractile(std::vector<int>& numbers, int p) {
        /// sort the numbers first
        std::sort(numbers.begin(), numbers.end());
        
        ///  now index in and access the pth element from 0
        uint index = ceil(numbers.size()*(p/100.0)) - 1;

        return numbers[index];
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
    
    uint64_t input;

    /// keep a timer
    std::clock_t start;
    double duration;

    start = std::clock_t();
    /// do work here
    int answer;
    
    std::vector<int> numbers(5);
    for (uint i = 0; i < numbers.size(); i++)
        numbers[i] = -i;
    Fractile frclass;

    /// answer = frclass.fractile(numbers, 50);

    SwitchingBits sw;
    std::vector<std::string> str;
    str.push_back("11001100110011000001");
    
    answer = sw.minSwitches(str);
    
    
    std::cout << answer << std::endl;

    
    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

