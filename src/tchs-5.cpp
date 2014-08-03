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
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

class SuperSort {
  private:
    struct Token {
        vector <string> fillers;
        vector <string> words;
    };
    
        
    Token tokenizeString(string sentence) {
        Token split;

        bool ongoingWord(false), ongoingSpace(false), ongoingPunc(false);

        string currentToken;
        
        /// iterate through the string
        for (uint i = 0; i < sentence.size(); i++) {
            /// check if it is a letter
            int lowerCase = sentence[i] - 'a';
            int upperCase = sentence[i] - 'A';

            if ((lowerCase >= 0 && lowerCase < 26) ||
                (upperCase >= 0 && upperCase < 26)) {
                ongoingWord = true;
                /// is this the first letter of the word
                if (ongoingSpace || ongoingPunc) {
                    split.fillers.push_back(currentToken);
                    currentToken.clear();
                    ongoingSpace = false;
                    ongoingPunc = false;
                }

                /// push the character into word
                currentToken.push_back(sentence[i]);
            } else if (sentence[i] == ' ') {
                ongoingSpace = true;
                /// is this the first space
                if (ongoingWord) {
                    split.words.push_back(currentToken);
                    split.fillers.push_back("word");
                    currentToken.clear();
                    ongoingWord = false;
                } else if (ongoingPunc) {
                    split.fillers.push_back(currentToken);
                    currentToken.clear();
                    ongoingPunc = false;
                }
                currentToken.push_back(sentence[i]);
            } else {
                ongoingPunc = true;
                /// is this the first punctuation
                if (ongoingWord) {
                    split.words.push_back(currentToken);
                    split.fillers.push_back("word");
                    currentToken.clear();
                    ongoingWord = false;
                } else if (ongoingSpace) {
                    split.fillers.push_back(currentToken);
                    currentToken.clear();
                    ongoingSpace = false;
                }
                currentToken.push_back(sentence[i]);
            }
        }
        /// fill in the last word
        if (ongoingWord) {
            split.words.push_back(currentToken);
            split.fillers.push_back("word");
        } else {
            split.fillers.push_back(currentToken);
        }
        
        return split;
    }

  public:
    string wordSort(string sentence) {
        Token split = tokenizeString(sentence);

        /// sort the words
        sort(split.words.begin(), split.words.end());

        string sorted;
        uint wi = 0;
        
        for (uint i = 0; i < split.fillers.size(); i++) {
            if (split.fillers[i].compare("word") == 0) {
                sorted += split.words[wi];
                wi++;
            } else {
                sorted += split.fillers[i];
            }
            
        }
        return sorted;
    }
};

    
    
class TVSize {
  public:
    vector<int> calcSize(int diagonal, int height, int width) {
        vector<int> size(2,0);
        double theta = atan2(height, width);
        size[0] = floor(diagonal*sin(theta));
        size[1] = floor(diagonal*cos(theta));
        return size;
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

    SuperSort abcd;

    string sentence = "t.d,a!f?g.b,q!i?p.h,s!u?m.l,e!v?y.c,j!w?k.n,x!o?r.";
    
    
    abcd.wordSort(sentence);
    
    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    std::cout<< "it took: "<< duration << "s" << std::endl;
        
    return 0;
}

