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
#include <utility>
#include <algorithm>    // std::sort


bool compareStrings(std::string a_str, std::string b_str) {
    bool val;
    uint ctr = 0;
    while (true) {
        if ((a_str[ctr] - 'A') < (b_str[ctr] - 'A')) {
            val = true;
            break;
        } else if ((a_str[ctr] - 'A') > (b_str[ctr] - 'A')) {
            val = false;
            break;
        }
        

        /// increment counter
        ctr++;

        /// if a has reched its size - it wins
        if (ctr >= a_str.size()) {
            val = true;
            break;
        }
        
        if (ctr >= b_str.size()) {
            val = false;
            break;
        }
        
        /// keep going
    }

    /// std::cout << "a: " << a_str << " b: " << b_str << " val: " << val << std::endl;
    return val;
}

bool compareFunc(std::pair<std::string, uint64_t> a,
                 std::pair<std::string, uint64_t> b) {
    
    std::string a_str = a.first;
    std::string b_str = b.first;

    return compareStrings(a_str, b_str);
    
}


void sortAndScore(std::vector< std::pair<std::string, uint64_t> >* names) {

    std::sort(names->begin(), names->end(), compareFunc);

    /// score the names
    for (uint i = 0; i < names->size(); i++) {
        std::string currName = names->at(i).first;
        uint64_t accum = 0;
        for (uint j = 0; j < currName.size(); j++)
            accum += ((currName[j]-'A') + 1);

        /// multiple by index
        accum = accum*(i+1);

        names->at(i).second = accum;

        /// debug print
        /// std::cout << names->at(i).first << " \t"  << names->at(i).second << std::endl;
        
    }
    
}


uint64_t binarySearch(
    std::string query,
    const std::vector< std::pair<std::string, uint64_t> >& names) {

    /// std::cout << "searching" << std::endl;
    
    uint median = floor(names.size()/2);
    uint lower = 0;
    uint upper = names.size();

    while (upper > lower) {
        bool q_n = compareStrings(query, names[median].first);
        bool n_q = compareStrings(names[median].first, query);

        /*
        std::cout << query << " "
                  << names[median].first << " "
                  << q_n << " "
                  << n_q << std::endl;
        */
        
        /// check if median is the element
        if ((q_n) && (n_q))
            return names[median].second;
        else if (q_n) {
            upper = median;
            median = floor((lower+upper)/2);
        } else {
            lower = median;
            median = floor((lower+upper)/2);
        }   
    }
    
     std::cout << "Not found!" << std::endl;
     return 0;
     
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
    uint N, Q;
    std::cin >> N;

    /// keep a timer
    std::clock_t start;
    double duration;

    /// do work here
    start = std::clock_t();

    /// use a pair container to store both names and score
    std::vector< std::pair<std::string, uint64_t> > names;
    /// instantiate string containers
    std::vector<std::string> queries;
    
    for (uint i = 0; i < N; i++) {
        std::string word;
        std::cin >> word;
        names.push_back(std::make_pair(word, 0));
    }

    /// sort and score the names
    sortAndScore(&names);

    /// std::cout << "sorted" << std::endl;

    
    std::cin >> Q;
    for (uint i = 0; i < Q; i++) {
        std::string word;
        std::cin >> word;

        uint64_t answer = binarySearch(word, names);

        std::cout << answer << std::endl;
    }


    


    
    
    
    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    /// std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

