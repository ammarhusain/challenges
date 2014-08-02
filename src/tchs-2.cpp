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


/** ----------------------------------------------------------------------
 * Problem Statement
    
A Fountain of Life is a special fountain that produces the elixir of life at a constant speed of elixir liters per second. A dark mage managed to cast a Curse of Death on the Fountain so in addition to the elixir it now produces a deadly poison at a constant speed of poison liters per second. Both the poison and elixir are collected in an infinitely large pool around the Fountain and form a mixture. The mixture will become deadly once the percentage of poison in the mixture is at least 50%. Your task is to calculate the time at which the mixture will become deadly. At the beginning (0-th second) the pool contains pool liters of 100% elixir.  Your program must return a double, the time in seconds at which the mixture becomes deadly. If the mixture never becomes deadly, return -1.0.
Definition
    
Class:
FountainOfLife
Method:
elixirOfDeath
Parameters:
int, int, int
Returns:
double
Method signature:
double elixirOfDeath(int elixir, int poison, int pool)
(be sure your method is public)
Limits
    
Time limit (s):
2.000
Memory limit (MB):
64
Notes
-
The returned value must be accurate to within a relative or absolute value of 1E-9.
Constraints
-
elixir will be between 1 and 10000, inclusive.
-
poison will be between 1 and 10000, inclusive.
-
pool will be between 1 and 10000, inclusive.
Examples
0)

    
1
2
2
Returns: 2.0
At t = 0s there are 2 liters of 100% elixir. At t = 1s there are 3 liters of elixir and 2 liters of poison for a total volume of 5 liters. 2 liters of poison is 40% of 5 liters so the mixture is still not deadly. At t = 2s there are 4 liters of elixir and 4 liters of poison for a total volume of 8 liters. 4 liters of poison is exactly 50% of the mixture so it is now deadly. 
1)

    
200
100
1
Returns: -1.0
With 200 liters of elixir per second and only 100 liters of poison per second, the mixture never becomes deadly.
2)

    
9999
10000
10000
Returns: 10000.0
It might take a long time for the mixture to become deadly.
3)

    
1
10000
1
Returns: 1.0001000100010001E-4
On the other hand, it might take a short time for the mixture to become deadly.
4)

    
40
43
41
Returns: 13.666666666666666

 * 
 --------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <ctime>



class FountainOfLife {
    
  public:
    /** ----------------------------------------------------------------------
     * 
     * 
     * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
     * @date 08/01/2014 
     * @param elixir 
     * @param posion 
     * @param pool 
     * 
     * @return 
     ---------------------------------------------------------------------- */
    double elixirOfDeath(int elixir, int poison, int pool) {
        /// ratio between poison and elixir must be > 0.50
        /// (poision*t) = 0.50*(elixir*t + pool)
        double t = (1.0*pool)/(poison - elixir);
        if (t < 0.0)
            t = -1.0;
        
        
        return t;
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

    FountainOfLife var;
    std::cout << var.elixirOfDeath(1, 2, 2) << std::endl;

    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

