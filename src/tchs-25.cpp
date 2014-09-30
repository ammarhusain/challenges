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



class Staircase {
  public:
    int minimalSteps(std::vector<int> stairs) {

        int current = stairs[0];
        int toGo;
        int steps = 1;

        std::cout << current << "->";
                    

        /// iterate through the steps
        for (int i = 1; i < stairs.size(); i++) {
            toGo = stairs[i];
            /// can we climb one
            if (toGo - current <=1) {
                /// climb
                current = toGo;

                std::cout << current << "->";    

                steps += 1;
            } else {
                /// start descending
                int j = i-1;
                int k = 0;
                /// current is at i-1
                while (j >= 0) {
                    current = stairs[j];

                    if (toGo - current <= pow(2, k)) {
                        /// can climb up
                        current = toGo;
                        break;
                    }
                    /// else
                    steps += 1;
                    k++;
                    j--;
                }

                std::cout << current << "->";    

                /// no way up
                if (j < 0)
                    return -1;
            }
            
        }

        return steps;
    }
};

    

class LuckyFives {
  public:

    double binomialCoefficient(int n, int r) {
        if (r == 0)
            return 1.0;
        double numerator(1.0), denominator(1.0);
        /// compute num
        for (int i = n; i > n-r; i--)
            numerator = numerator*i;
        /// compute den
        for (int i = 1; i <= r; i++)
            denominator = denominator*i;

        return numerator/denominator;
        
    }
    
    
    double probability(int dice, int sides) {
        double probRoll =
            static_cast<double>(1)/static_cast<double>(sides);

        double probNot =
            1.0 - probRoll;
        

        int rolls = 0;
        /// compute minimum number of fives required
        /// dividing ints will produce rounded down int so add 1
        rolls = (dice/5) + 1;

        double prob = 0;
        
        for (uint j = 0; j < rolls; j++) {
            prob +=
                binomialCoefficient(dice, j)
                *pow(probRoll, j)*pow(probNot, dice-j);
            double tmp =
                binomialCoefficient(dice, j)
                *pow(probRoll, j)*pow(probNot, dice-j);
            /*
            std::cout << binomialCoefficient(dice, j) << "\t"
                      << pow(probRoll, j) << "\t"
                      << pow(probNot, dice-j) << "\t"
                      << tmp << std::endl;
            */
        }

        return (1.0 - prob);
        
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
    /// keep a timer
    std::clock_t start;
    double duration;

    start = std::clock_t();
    /// do work here
    LuckyFives lf;
    /// double answer = lf.probability(20, 10);


    Staircase sc;
    std::vector<int> steps;
    steps.push_back(0);
    steps.push_back(1);
    steps.push_back(2);
    steps.push_back(3);
    steps.push_back(6);
    int ans = sc.minimalSteps(steps);

    std::cout << std::endl;
    std::cout << ans << std::endl;
    
    
    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    std::cout<< "it took: "<< duration << "s" << std::endl;
    
    return 0;
}

