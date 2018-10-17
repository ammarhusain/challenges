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
#include <algorithm>

using namespace std;

/** ----------------------------------------------------------------------
 * Division 2: 950 points
 * 
 --------------------------------------------------------------------- */

class ConundrumReloaded {
  public:
    int minimumLiars(string answers) {
        string contiguous = findLongestContiguous(answers);

        /// have we split the answers string?
        bool split;
        if (contiguous.size() < answers.size())
            split = true;
        

        /// fill out the possible trails considering the 2 possibilities:
        /// first person is: liar, honest

        int liars_0 = followBreadCrumbs(contiguous, 0, split);

        int liars_1 = followBreadCrumbs(contiguous, 1, split);


        /// return the smaller of the 2
        if (liars_0 < liars_1)
            return liars_0;

        else
            return liars_1;
        
    }


    int followBreadCrumbs(string answers, bool start, bool split) {
        /// how many liars on this trail
        int liars = 0;
        
        vector<bool> followTrail(answers.size() + 1);

        /// lets say the first person is a liar
        followTrail[0] = start;

        uint i = 0;
        while (i < answers.size()) {
            if ((followTrail[i] == 0) && (answers[i] == 'L'))
                followTrail[i+1] = 1;
            else if ((followTrail[i] == 1) && (answers[i] == 'L'))
                followTrail[i+1] = 0;
            else if ((followTrail[i] == 0) && (answers[i] == 'H'))
                followTrail[i+1] = 0;
            else if ((followTrail[i] == 1) && (answers[i] == 'H'))
                followTrail[i+1] = 1;

            i++;
        }

        /// if there is split we dont roll over for to check
        if (!split) {
            /// are the first and last elements of follow trail equal
            if (followTrail[0] == followTrail[followTrail.size()-1])
                liars = countLiars(followTrail);
            else  /// it doesn't add up
                liars = -1;

        } else {
            liars = countLiars(followTrail);
        }

        return liars;
    }
    
    

    
    int countLiars(vector<bool> trail) {
        int liars = 0;
        for (uint i = 0; i < trail.size(); i++) {
            if (!trail[i])
                liars += 1;
            /// std::cout << trail[i];
        }
        /// std::cout << std::endl;
        
        return liars;    
    }
    
    string findLongestContiguous(string answers) {
        uint start = 0;
        uint length = 0;
        uint l_start = 0;

        uint i = 0;
        while (i < answers.size()) {
            if (answers[i] == '?') {
                if (i-start > length) {
                    length = i - start;
                    l_start = start;
                }
                /// reset the start index
                start = i+1;
            }
            /// move forward
            i++;
        }

        /// check at the end of the string
        if (i-start > length) {
            length = i - start;
            l_start = start;
        }

        /// pull the region [l_start, l_start+length)
        string cont(answers, l_start, length);
        return cont;
        
    }
};

    



/** ----------------------------------------------------------------------
 * Division 2: 500 points
 * 
 --------------------------------------------------------------------- */

class IncrementingSequence {
  public:
    string canItBeDone(int k, vector<int> A) {
        uint N = A.size();
        
        /// start by sorting the vector so we can line it up
        std::sort(A.begin(), A.end());

        /// now iterate through and set the corresponding values
        for (uint i = 0; i < N; i++) {
            /// keep adding k until it equals or becomes greater
            while (A[i] <= i)
                A[i] += k;
            
            /// did we reach the intended value
            if (A[i] != i+1)
                return "IMPOSSIBLE";
            
            /// else we are all good
        }
        return "POSSIBLE";
    }
};


/** ----------------------------------------------------------------------
 * Division 1: 250 points
 * 
 --------------------------------------------------------------------- */

class PalindromePermutations {
  public:
    double palindromeProbability(string word) 
    {
        /// create a hash array to store count for each character in the string
        vector<uint> hash(('z'-'a') + 1, 0);
        
        /// iterate through and count the instance of each character
        for (uint i = 0; i < word.size(); i++)
            hash[word[i] - 'a'] += 1;

        /// now compute all possible anagrams
        /// not the most efficient computation
        /// but who cares at the moment
        double allAnagrams = factorial(word.size());

        /// now iterate through and divide
        for (uint j = 0; j < hash.size(); j++)
            allAnagrams = allAnagrams/factorial(hash[j]);

        /// std::cout << allAnagrams << std::endl;

        /// is this an even or odd numbered string
        bool even = (word.size()%2 == 0);

        vector<uint> halfHash(hash.size(), 0);
        /// keeps track of how many odd numbered characters are there
        uint numOdd = 0;
        for (uint j = 0; j < hash.size(); j++) {
            if (hash[j]%2 != 0)
                numOdd += 1;
            halfHash[j] = hash[j]/2;
        }

                
        /// thereshould never be more than one odd number of character
        if (numOdd > 1)
            return 0.0;
        
        /// if this string has even length there should be no odd number of characters
        if (even && (numOdd > 0))
            return 0.0;


        /// now count the number of palindromes
        double allPalindromes = factorial(word.size()/2);

        /// now iterate through and divide
        for (uint j = 0; j < halfHash.size(); j++)
            allPalindromes = allPalindromes/factorial(halfHash[j]);

        
        return allPalindromes/allAnagrams;
        
    }


    double factorial(int n) {
        double facto = 1;
        
        while (n >1) {
            facto = facto*n;
            n--;
        }
        return facto;
        
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


    ConundrumReloaded cr;

    int answer = cr.minimumLiars("??????");

    
    
    PalindromePermutations pp;

    /// double answer = pp.palindromeProbability("xxxyx");
    
    std::cout << answer << std::endl;
    
    
    
    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

