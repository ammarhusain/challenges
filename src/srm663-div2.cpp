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
#include <string>

class Target {
    public:
        std::vector<std::string> draw(int n) {

            // instantiate a vector of size
            std::vector<std::string> target(n);

            // sanity check
            if (n%4 != 1)
                return target;

            int i = 0;

            while (i < n/2) {
                std::string elem;

                // create prefix
                elem += '#';

                int step = i/2;
                for (int j = 0; j < step; j++)
                    elem += " #";

                int fill_length = n - 2*(1 + (2*step));
                // for even i - fill #
                if (i%2 == 0)
                    fill(elem, '#', fill_length);
                else        
                    fill(elem, ' ', fill_length);
                
                // suffix the end
                for (int j = 0; j < step; j++)
                    elem += "# ";

                elem += '#';

                // add into vector
                target[i] = elem;
                i++;
            }

            // handle the middle line
            std::string mid;
            for (int k = 0; k < n; k++) {
                if (k%2 == 0)
                    mid += '#';
                else
                    mid += ' ';
            }

            target[i] = mid;
            i++;

            int sym = (n/2) - 1;
            // target is symmetric
            // iterate and copy over
            while (i < n) {
                target[i] = target[sym];
                i++; sym--;
            }
            return target;
    }

    void fill(std::string& line, char f, int n) {
        for(int i = 0; i < n; i++)
            line += f;
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
    std::cout << "Google SRM" << std::endl;
    

    /// keep a timer
    std::clock_t start;
    double duration;

        start = std::clock_t();
        /// do work here

    Target tr;
    std::vector<std::string> target = tr.draw(33);

    std::cout << target.size() << std::endl;
    // print the target
    for (uint i = 0; i < target.size(); i++)
        std::cout << target[i] << std::endl;

        duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
        std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

