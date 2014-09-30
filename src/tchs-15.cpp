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
    
/** ----------------------------------------------------------------------
 * Trie Implementation 
 * 
 --------------------------------------------------------------------- */
class SetOfBoxes {
  public:
    /// helper structs
    struct Vertex {
        int x;
        int y;
    };
    struct Triangle {
        Vertex vertices[3];
    };


    /// Herons Formula
    double getArea(Triangle t) {
        /// get length of all 3 sides
        double a = getLength(t.vertices[0], t.vertices[1]);
        double b = getLength(t.vertices[1], t.vertices[2]);
        double c = getLength(t.vertices[2], t.vertices[0]);
        double s = (a+b+c)/2.0;

        return sqrt(s*(s-a)*(s-b)*(s-c));
    }

    double getLength(Vertex v1, Vertex v2) {
        return sqrt(pow(v1.x-v2.x, 2) + pow(v1.y-v2.y, 2));
    }


    /** ----------------------------------------------------------------------
     * parses the string to extract triangles
     * 
     * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
     * @date 09/02/2014 
     * @param boxes 
     * 
     * @return 
     ---------------------------------------------------------------------- */
    std::vector< std::pair<Triangle, double> > parseBoxes(std::vector<std::string> boxes) {
        std::vector< std::pair<Triangle, double> > triangles(boxes.size());

        /// iterate through and parse the boxes
        for (uint k = 0; k < boxes.size(); k++) {
            std::string line = boxes[k];
            std::vector<int> vertices;

            std::vector<int> number;
            for (uint i = 0; i < line.size(); i++) {

                /// time to change number
                if ((line[i] == ' ') || (line[i] == '.')) {
                    int num = 0;
                    for (int j = number.size()-1; j >= 0; j--)
                        num += number[j] * pow(10, (number.size() - j) -1);
                    
                
                    /// if (num != 0)
                        std::cout << num << "\t";

                    /// push the number as a vertex
                    vertices.push_back(num);
                    number.clear();

                    } else {
                        number.push_back(line[i] - '0');
                    }
            }
            /// fetch the last number before end of line
            int num = 0;
            for (int j = number.size()-1; j >= 0; j--)
                num += number[j] * pow(10, (number.size() - j) -1);
            
            
            /// if (num != 0)
            std::cout << num << std::endl;
            
            /// push the number as a vertex
            vertices.push_back(num);
            

            /// add the vertices to a triangle
            triangles[k].first.vertices[0].x = vertices[0];
            triangles[k].first.vertices[0].y = vertices[1];
            triangles[k].first.vertices[1].x = vertices[2];
            triangles[k].first.vertices[1].y = vertices[3];
            triangles[k].first.vertices[2].x = vertices[4];
            triangles[k].first.vertices[2].y = vertices[5];

            /// compute the area of the triangle
            triangles[k].second = getArea(triangles[k].first);
            std::cout << "a: " << triangles[k].second << std::endl;
            
        }

        return triangles;
    }

    struct Node {
        std::vector<Node> children;
        std::pair<Triangle, double> data;
        /// keep track of parent
        Node* parent;
    };
    

    double sign(Vertex p1, Vertex p2, Vertex p3) {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x)*(p1.y - p3.y);
    }
    
    /** ----------------------------------------------------------------------
     * checks of triangle a contains triangle b
     * Uses the half plane convex hull method
     * @author Ammar Husain <ahusain@nrec.ri.cmu.edu>
     * @date 09/02/2014 
     * @param a 
     * @param b 
     * 
     * @return 
     ---------------------------------------------------------------------- */
    bool contains(Triangle a, Triangle b) {
        /// if one vertex is inside the triangle then all of them would be
        /// no overlapping triangles
        bool b1, b2, b3;
        b1 = sign(b.vertices[0], a.vertices[0], a.vertices[1]) < 0.0;
        b2 = sign(b.vertices[0], a.vertices[1], a.vertices[2]) < 0.0;
        b3 = sign(b.vertices[0], a.vertices[2], a.vertices[0]) < 0.0;

        return ((b1 == b2) && (b2 == b3));
    }
    
    
    
    double countThrow(std::vector<std::string> boxes, int inBox) {
        std::vector< std::pair<Triangle, double> > triangles
            = parseBoxes(boxes);

        Node trie;
        /// square is the root of the trie
        trie.parent = NULL;
        
        /// iterate through the triangles and build a tree
        std::cout << contains(triangles[0].first, triangles[2].first)
                  << "\t"
                  << contains(triangles[2].first, triangles[0].first)
                  << "\t"
                  << contains(triangles[1].first, triangles[2].first)
                  << "\t"
                  << contains(triangles[1].first, triangles[2].first)
                  << "\t"
                  << contains(triangles[1].first, triangles[0].first)
                  << "\t"
                  << contains(triangles[0].first, triangles[1].first)

                  << std::endl;
        
        
        return -1.0;
        
    }
    
};

    


class ShootingGallery {
  public:
    int profitableBet(int accuracy) {
        double prob = 0.0;
        double init = accuracy/100.0;
        uint ctr = 0;
        while (prob < 0.5) {
            ctr += 1;

            double product = init;
            
            for (uint j = 2; j <= ctr; j++)
                product = (1.0-init)*product;

            //if (product > init)
                prob = prob + product;
            
                /// std::cout << prob << "\t" << ctr << std::endl;
            
        }
        
        return (ctr-1);
        
    }
    

};

    

class NumbersLine {
  public:
    int getLeast(std::string line, int givenNumber) {
        std::vector<int> number;
        int soFar = 10000;
        /// iterate through the string
        for (uint i = 0; i < line.size(); i++) {
            /// time to change number
            if (line[i] == ' ') {
                int num = 0;
                for (int j = number.size()-1; j >= 0; j--) {
                    num += number[j] * pow(10, (number.size() - j) -1);
                }
                
                if (num != 0)
                    std::cout << num << std::endl;
                
                if ((num > givenNumber) && (num < soFar))
                    soFar = num;

                number.clear();

            } else {
                number.push_back(line[i] - '0');
            }
        }
        
        if (soFar > 1000)
            return -1;
        else
            return soFar;
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
    uint64_t input;

    /// keep a timer
    std::clock_t start;
    double duration;

    start = std::clock_t();
    /// do work here

    NumbersLine nl;
    //int answer = nl.getLeast("25 20  43 21 980 ", 5);


    ShootingGallery sg;
    //int answer = sg.profitableBet(40);

    SetOfBoxes sb;
    std::vector<std::string> boxes;
    boxes.push_back("0.0 5.0 0.5");
    boxes.push_back("1.1 6.1 1.5");
    boxes.push_back("1.1 3.1 1.3");
    
    double answer = sb.countThrow(boxes, 3);
    
    
    
    
    std::cout << answer << std::endl;
    
    
    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

