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
#include <unordered_set>

#include <unordered_map>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <ctime>

using namespace std;


/** ----------------------------------------------------------------------
 *  Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6. 
 * 
 --------------------------------------------------------------------- */

class MaxProductSubArray {
  public:
    

    int maxProduct(int A[], int n) {
        if (n < 1)
            return 0;

        /// the largest it can be
        int * subset = new int[n];
        int s = 0;

        /// first element in subset
        subset[s] = A[0];
        /// start with the first element
        int e = s+1;
        
        /// iterate while the end hasn't come
        while (e < n) {
            int elem = subset[s]*A[e];

            /// is this adding anything to the subset
            if (elem > subset[s]) {
                /// include it in the group
                subset[s] = elem;
            } else {
                /// nope start a new subset begining at e
                s +=1;
                subset[s] = A[e];
            }
            e++;
        }
        
        /// finalize the last element
        s += 1;
        

        /// now lets go back and see if we can merge subsets for the greater good
        return maxProduct_N2(subset, s);
        
    }
        
    /// O(n^2) solution
    int maxProduct_N2(int A[], int n) {
        if (n < 1)
            return 0;
        
        int alltime = A[0];
        
        for (uint i = 1; i < n; i++) {
            int largest = A[i];
            /// start subset at this index and see if we can merge backwards
            int sofar = A[i];
            int j = i-1;
            /// iterate backwards
            while (j >= 0) {
                sofar = sofar*A[j];
                if (sofar > largest)
                    largest = sofar;
                /// reduce j
                j--;
            }

            if (largest > alltime)
                alltime = largest;
        }

        return alltime;

    }
    
    int maxProductFlawed(int A[], int n) {
        if (n < 1)
            return 0;
        
        int s = 0;
        int e = 1;
        int prod = A[0];
        int currProd = prod;
        
        /// iterate while the end hasn't come
        while (e < n) {
            if ( (currProd >= currProd*A[e]) && (A[e] != 1) ) {
                /// if its a 1 don't worry about it
                
                
                /// time to reset brother
                /// has this been the largest prod so far
                if (currProd > prod)
                    prod = currProd;
                /// reset stuff
                s = e;
                e = s+1;
                currProd = A[s];
            } else {
                /// all good keep going
                currProd = currProd*A[e];
                e += 1;
            }
        }

        
        /// final check if last element is greatest of all
        if (currProd > prod)
            prod = currProd;
        

        return prod;
    }
};



/** ----------------------------------------------------------------------
 *  Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:

  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

 * 
 --------------------------------------------------------------------- */
class ReversePolishNotation {
  public:
    int evalRPN(vector<string> &tokens) {
        /// use a vector stack to store numbers
        /// could potentially make the stack smaller
        int * stack = new int[tokens.size()];
        int ctr = 0;

        for (int i = 0; i < tokens.size(); i++) {
            /// check for operators
            if (tokens[i].compare("*") == 0) {
                /// multiply the last two number
                int num = stack[ctr-2]*stack[ctr-1];
                /// insert this operated element at ctr-2
                stack[ctr-2] = num;

                /// reduce ctr
                ctr -= 1;
                
            } else if (tokens[i].compare("/") == 0) {
                int num = stack[ctr-2]/stack[ctr-1];
                /// insert this operated element at ctr-2
                stack[ctr-2] = num;

                /// reduce ctr
                ctr -= 1;
            } else if (tokens[i].compare("+") == 0) {
                int num = stack[ctr-2] + stack[ctr-1];
                /// insert this operated element at ctr-2
                stack[ctr-2] = num;

                /// reduce ctr
                ctr -= 1;
            } else if (tokens[i].compare("-") == 0) {
                int num = stack[ctr-2]-stack[ctr-1];
                /// insert this operated element at ctr-2
                stack[ctr-2] = num;

                /// reduce ctr
                ctr -= 1;
            } else {
                stack[ctr] = convertToInt(tokens[i]);
                /// std::cout << convertToInt(tokens[i]) << std::endl;
                
                
                /// go to next element
                ctr += 1;
            }

        }

        /// pull first element from stack
        /// std::cout << "rpn: " << stack[0] << std::endl;
        
        return stack[0];
        
        
    }


    int convertToInt(string token) {
        if (token.size() < 1)
            return 0;

        int s = 0;
        int size = token.size();
        
        bool negative = false;
        /// check for sign
        if (token[0] == '-') {
            negative = true;
            s = 1;
            /// size = size -1;
        }
        else if (token[0] == '-') {
            s = 1;
            /// size = size - 1;
        }
        
        int number = 0;

        for (int i = s; i < size; i ++) {
            int digit = token[i] - '0';
            int exp = (size-1) - i;
            
            number += digit*pow(10, exp);
        }

        if (negative)
            number = -1*number;
        
        return number;
    }
    

};


/** ----------------------------------------------------------------------
 * Sort List: Sort a linked list in O(n log n) time using constant space complexity.
 * 
 --------------------------------------------------------------------- */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class InplaceListSort {
public:
    ListNode *sortList(ListNode *head) {
        /// sanity check
        if (head == NULL)
            return head;
        
        /// get the size of the list
        int size = 1;
        ListNode* node = head;
        while (node->next != NULL) {
            size += 1;
            node = node->next;
        }

        return mergeSortRecursive(head, size);
        
    }

    ListNode* mergeSortRecursive(ListNode* start, int size) {
        std::cout << "sz: " << size << std::endl;
        
        /// base condition
        if (size <= 1)
            return start;


        /// divide the list into 2
        int leftHalf = ceil(size/2.0);
        int rightHalf = size - leftHalf;
        
        std::cout << "l: " << leftHalf << " r: " << rightHalf << std::endl;

        ListNode* rightList = start;
        /// iterate and get to the right half
        int ctr = 1;
        while (ctr <= leftHalf) {
            rightList = rightList->next;
            ctr += 1;
        }


        ListNode* printer = start;

        while(printer != NULL) {
            std::cout << printer->val << "\t"  << std::endl;
            printer = printer->next;
            
        }
        
        
        std::cout << "rs: " << rightList->val;
        


        
        /// sort the left side
        ListNode* left = mergeSortRecursive(start, leftHalf);

        
        /// sort the right side
        ListNode* right = mergeSortRecursive(rightList, rightHalf);

        std::cout << "merging: " << leftHalf << " \t" << rightHalf << std::endl;
        

        
        
        /// main portion: merge
        ListNode* sortedTracker;
        ListNode* sorted = sortedTracker;
        
        
        while ((left != NULL) || (right != NULL)) {
            if (left == NULL) {
                sortedTracker = right;
                break;
            } else if (right == NULL) {
                sortedTracker = left;
                break;
            }

            std::cout << "l " << left << " r " << right << std::endl;

            std::cout << "lv " << left->val << " rv " << right->val << std::endl;
            
            /// check the values
            if (left->val <= right->val) {
                sortedTracker = left;
                left = left->next;
            } else {
                sortedTracker = right;
                right = right->next;
            }

            std:: cout << "srt " << sortedTracker << std::endl;
            
            sortedTracker = sortedTracker->next;
            
        }
    
        std::cout << "merged: " << size << std::endl;

        
        return sorted;
        
    }
    
};


/** ----------------------------------------------------------------------
 * Given a binary tree, return the preorder traversal of its nodes' values.
 * Iterative Solution
 * 
 --------------------------------------------------------------------- */
#include <stack>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class PreorderTaversal {
  public:    
    vector<int> preorderTraversal(TreeNode *root) {
        /// return container
        vector<int> traversal;        

        if (root == NULL)
            return traversal;

        /// container to store the tree nodes
        stack<TreeNode*> stack;

        
        /// push the root to get started
        stack.push(root);
        
        
        while (stack.size() > 0) {
            /// get the top most element from the stack
            TreeNode* top = stack.top();
            stack.pop();
            
            /// add the element
            traversal.push_back(top->val);
            
            
            /// does this have a right child
            if (top->right != NULL)
                stack.push(top->right);
            /// does this have a left child
            if (top->left != NULL)
                stack.push(top->left);
            
        }
        return traversal;
    }
    
};


/** ----------------------------------------------------------------------
 * Given a binary tree, return the postorder traversal of its nodes' values.
 * Iterative Solution
 * 
 --------------------------------------------------------------------- */

class PostOrderTraversal {

    struct Tracker {
        TreeNode* node;
        bool touched;
        Tracker(TreeNode* ptr) : node(ptr), touched(false) {}
        
    };

  public:
    vector<int> postorderTraversal(TreeNode *root) {
        /// return container
        vector<int> traversal;

        if (root == NULL)
            return traversal;

        /// container to store the tree nodes
        stack<Tracker> stack;

        
        /// push the root to get started
        stack.push(Tracker(root));

        while (stack.size() > 0) {
            /// get the top element
            Tracker top = stack.top();

            /// have we been here already?
            if (top.touched == true) {
                /// traverse and remove
                traversal.push_back(top.node->val);
                stack.pop();
                continue;
            }

            
            /// is this a leaf
            if ((top.node->right == NULL) && (top.node->left == NULL)) {
                /// traverse and remove
                traversal.push_back(top.node->val);
                stack.pop();
                continue;
            }
            

            /// mark this node as touched
            stack.top().touched = true;

            
            /// push the right element
            if (top.node->right != NULL)
                stack.push(Tracker(top.node->right));
            /// push the left element
            if (top.node->left != NULL)
                stack.push(Tracker(top.node->left));


        }
        
        return traversal;
    }
};


/** ----------------------------------------------------------------------
 *  Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome
 * 
 --------------------------------------------------------------------- */

class AlphaNumericPalindrome {
public:
    bool isPalindrome(string s) {
        /// for empty string
        if (s.size() < 1)
            return true;

        vector<char> chars;
        
        /// iterate through the entire string and collect characters
        /// will have to be O(2n)
        /// cannot do it in O(n) because the spaces and punctuation must be ignored
        /// think "He, is ..... aasieh"
        for (int i = 0; i < s.size(); i++) {

            int charNum = tolower(s[i]) - 'a';
            int digitNum = s[i] - '0';
            
            if ((charNum < 26) && (charNum >=0))
                chars.push_back(tolower(s[i]));
            else if ((digitNum < 10) && (digitNum >= 0))
                chars.push_back(s[i]);
        }
        
        /// iterate through chars and check for palindrome
        int i = 0;
        int j = chars.size() - 1;

        while (i < j) {
            if (chars[i] - chars[j] != 0)
                return false;
            i++;
            j--;
        }
        /// it checks out
        return true;
    }
};

#include <climits>

#include <algorithm>

/** ----------------------------------------------------------------------
 *  Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3

Return 6. 
 * 
 --------------------------------------------------------------------- */

class MaxPathTree {
  public:
    struct PathCombo {
        int path;
        int crossed;
        bool filled;
        
        PathCombo() : path(0), crossed(0), filled(false) 
        {}
        
        
            
        
    };
    
        
    int maxPathSum(TreeNode *root) {

        /// container to get max paths
        PathCombo rootMax;
        maxSubTreePaths(root, rootMax);

        return max(rootMax.path, rootMax.crossed);
        
    }

    void maxSubTreePaths(TreeNode* root, PathCombo& maxes) 
    {
        /// base condition
        if (root == NULL)
            return;

        /// check left
        PathCombo left;
        maxSubTreePaths(root->left, left);
        /// check right
        PathCombo right;
        maxSubTreePaths(root->right, right);

        /// figure out the path maximum
        int path1 = 0;
        /// have both been filled
        if (left.filled && right.filled)
            path1 = max(left.path, right.path);
        else if (left.filled)
            path1 = left.path;
        else if (right.filled)
            path1 = right.path;
        /// or am i better by myself
        maxes.path = max(path1 + root->val, root->val);
        
        /// figure out the crossover max
        /// this is a little trickier
        int opt1 = INT_MIN;
        /// cross over through current node only if both have been filled
        if (left.filled && right.filled)
            opt1 = left.path + right.path + root->val;

        /// or pick the better of the 2 subtree crosses
        int opt2 = INT_MIN;
        /// am I letting things down
        int opt3 = INT_MIN;        

        if (left.filled && right.filled) {
            opt2 = max(left.crossed, right.crossed);
            opt3 = max(left.path, right.path);
        } else if (left.filled) {
            opt2 = left.crossed;
            opt3 = left.path;
        } else if (right.filled) {
            opt2 = right.crossed;
            opt3 = right.path;
        }

        /// pick the largest of the 3 options
        maxes.crossed = max(max(opt1, opt2), opt3);
        
        maxes.filled = true;
        
        return;
        
    }
    
};

/** ----------------------------------------------------------------------
 *  Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
 * 
 --------------------------------------------------------------------- */

class Board {
  public:
    struct Coordinate {
        int x;
        int y;
        Coordinate() : x(-1), y(-1) {}
        
        Coordinate(int x_val, int y_val) : x(x_val), y(y_val) 
        {}
        
    };
    

    bool charMatches(vector<vector<char> > &board,
                     char letter, Coordinate grid) {
        
        /// limits
        int x_max = board.size();
        int y_max = board[0].size();

        if ((grid.x < x_max) && (grid.x >= 0) &&
            (grid.y < y_max) && (grid.y >= 0)) {
            if (board[grid.x][grid.y] - letter == 0)
                return true;
        }

        return false;
    }

    bool exist(vector<vector<char> > &board, string word) {
        /// sanity checks on input
        if (word.size() < 1)
            return true;
        if (board.size() < 1)
            return true;

        /// limits
        int x_max = board.size();
        int y_max = board[0].size();

        /// instantiate a matrix to keep track of where youve been
        vector<vector<bool> > visited(x_max);
        for (int i = 0; i < x_max; i++)
            visited[i].resize(y_max, false);

        /// position yourself in the matrix first
        for (int i = 0; i < x_max; i++) {
            for (int j = 0; j < y_max; j++) {
                if (board[i][j] - word[0] == 0) {
                    /// std::cout << "found: " << word[0] << "\t" << i << "\t" << j << std::endl;
                    
                    /// start traversing here
                    Coordinate origin;
                    origin.x = i;
                    origin.y = j;
                    if (canConstruct(board, word, origin, visited))
                        return true;
                    /// else keep searching
                }
                
                    
            }
        }
        /// couldn't find anything in the board
        return false;
    }

    bool canConstruct(vector<vector<char> > &board,
                      string word, Coordinate origin,
                      vector<vector<bool> > visited) {

        int w_ctr = 1;
        stack<Coordinate> togo;

        /// mark the start as visited
        /// visited[origin.x][origin.y] = true;
        
        /// add the origin to the stack to get started
        togo.push(origin);
        
        /// iterate till either the word is complete
        /// or the stack has been exhausted
        while ((togo.size() > 0) && (w_ctr < word.size())) {
            /// get the first element in the stack
            Coordinate top = togo.top();


            /// if (w_ctr == 
            /// std::cout << "w_ctr " << w_ctr << std::endl;
            
            std::cout << "searching for: " << word[w_ctr] << " at: " << top.x << "\t" << top.y << std::endl;
            /// std::cout << "logbook: " << visited[top.x][top.y] << std::endl;
            
            
            /// have you already been here?
            if (visited[top.x][top.y] == true) {
                /// sorry you didnt get what you were looking  for
                w_ctr -= 1;

                /// i will remove you from the logbook if you wish to visit again
                visited[top.x][top.y] = false;

                togo.pop();
                continue;
            }

            /// this is where the stack has started
            int preSize = togo.size();
            
            /// welcome to the grid -> look around
            Coordinate next;
            /// vertically
            if (charMatches(board, word[w_ctr], Coordinate(top.x+1, top.y))) {
                /// std::cout << "foundered: " << word[w_ctr] << " at: " << top.x+1 << "\t" << top.y << std::endl;
                /// only add if never visited
                if (visited[top.x+1][top.y] == false)
                    togo.push(Coordinate(top.x+1, top.y));
            }
            
            if (charMatches(board, word[w_ctr], Coordinate(top.x-1, top.y))) {
                if (visited[top.x-1][top.y] == false)
                    togo.push(Coordinate(top.x-1, top.y));
            }
            
            /// horizontally
            if (charMatches(board, word[w_ctr], Coordinate(top.x, top.y+1))) {
                if (visited[top.x][top.y+1] == false)
                    togo.push(Coordinate(top.x, top.y+1));
            }
            
            if (charMatches(board, word[w_ctr], Coordinate(top.x, top.y-1))) {
                if (visited[top.x][top.y-1] == false)
                    togo.push(Coordinate(top.x, top.y-1));
            }

            /// std::cout << "w: " << word[w_ctr] << std::endl;
            
            
            /// has anything been added?
            if (togo.size() - preSize > 0)
                /// increment word counter
                w_ctr++;
            else
                /// pop this node: it was useless
                togo.pop();
            
            
            /// mark yourself as visited
            visited[top.x][top.y] = true;

            /// if nothing was added, the grid will be popped out in the next iteration
            
        }
        
        /// if all letters in wird satisfied
        if (w_ctr == word.size())
            return true;
        else
            return false;
        
    }

     
    
};



/** ----------------------------------------------------------------------
 *  Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Follow up:
Can you solve it without using extra space? 
 * 
 --------------------------------------------------------------------- */

class LinkedListCycle2 {
  public:
    ListNode *detectCycle(ListNode *head) {

        if (head == NULL)
            return NULL;
        
        
        ListNode* slow = head;
        ListNode* fast = head;
        /// do while so it also the first iteration
        do {
            /// shift slow by one
            if (slow->next == NULL)
                return NULL;
            slow = slow->next;


            /// hop fast by 2
            /// check next node
            if (fast->next == NULL)
                return NULL;
            /// check node after that
            if (fast->next->next == NULL)
                return NULL;

            fast = fast->next->next;
            

        } while (slow != fast);

        /// slow and fast have collided: there is a cycle
        /// set slow to head again and start iterating
        slow = head;

        while (slow != fast) {
            fast = fast->next;
            slow = slow->next;
        }

        return fast;
        
    }
};

/** ----------------------------------------------------------------------
 * Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory? 
 * 
 --------------------------------------------------------------------- */

/// we need to xor all elements in the array
/// xor of 2 equal numbers is 0: therefore left with the only single number
class SingleNumber {
public:
    int singleNumber(int A[], int n) {
        if (n < 1)
            return 0;
        
        int result = A[0];
        for (int i = 1; i < n; i++) {
            result = result^A[i];
        }
        return result;
        
    }
};


/** ----------------------------------------------------------------------
 *  Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL

 * 
 --------------------------------------------------------------------- */


/**
 * Definition for binary tree with next pointer.
 */
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class ConnectNextPointers {
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL)
            return;

        /// go in and recursively connect
        recursiveConnect(root);
        
    }
    
    /// fills the left most and right most pointer in that subtree
    void recursiveConnect(TreeLinkNode* node) {
        /// sanity check: should never happen
        if (node == NULL)
            return;

        /// is this a leaf? : also should never happen
        if ((node->left == NULL) && (node->right == NULL))
            return;

        /// base condition
        /// am i the parent of 2 leaves?
        /// this is a perfect binary tree: so only need to check one child (left here)
        if ((node->left->left == NULL) && (node->right->left == NULL)) {
            /// connect my 2 children
            node->left->next = node->right;
            return;            
        }
        /// recursive cases
        recursiveConnect(node->left);
        recursiveConnect(node->right);

        /// keep going down the left subtree until ties are broken
        TreeLinkNode* ptr_1 = node->left;
        TreeLinkNode* ptr_2 = node->right;

        while (ptr_1->next != ptr_2) {
            ptr_1->next = ptr_2;

            /// go right
            ptr_1 = ptr_1->right;
            /// go left
            ptr_2 = ptr_2->left;

            if ((ptr_1 == NULL) || (ptr_2 == NULL))
                break;
            
        }
        
        return;
    }
    
};


/** ----------------------------------------------------------------------
 * Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node
 * 
 --------------------------------------------------------------------- */
class BinaryTreeDepth {
public:
    int maxDepth(TreeNode *root) {
        if (root == NULL)
            return 0;

        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        /// take the maximum between the 2 and add 1
        int height = max(left, right) + 1;

        return height; 
    }
};


/** ----------------------------------------------------------------------
 * Given two sorted integer arrays A and B, merge B into A as one sorted array.

Note:
You may assume that A has enough space (size that is greater or equal to m + n) to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.
 * 
 --------------------------------------------------------------------- */

class MergeArrays {
public:
    void merge(int A[], int m, int B[], int n) {
        
        /// go backwards
        int i = m-1;
        int j = n-1;
        int ctr = (m+n)-1;

        while (ctr >= 0) {
            std::cout << i << "\t"
                      << j << "\t"
                      << B[j] << std::endl;
            
            /// has all of A been added
            if (i < 0) {
                A[ctr] = B[j];
                j--;
            } else if (j < 0) {
                A[ctr] = A[i];
                i--;
            } else if (A[i] >= B[j]) {
                A[ctr] = A[i];
                i--;
            } else if (A[i] < B[j]) {
                A[ctr] = B[j];
                j--;
            }

            /// reduce counter
            ctr--;    
                
        }
        

        /// print A
        for (int k = 0; k <= (m+n)-1; k++)
            std::cout << A[k] << "\t";
        
    }
};



/** ----------------------------------------------------------------------
 * Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]

 * 
 --------------------------------------------------------------------- */

class LevelOrderTraversal {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        /// instantiate container for it to fill out
        vector<vector<int> > data;

        /// go recursively filling it out
        recursiveTraversal(root, data, 0);

        return data;
    }

    void recursiveTraversal(TreeNode* node, vector<vector<int> >& data, int level) 
    {
        /// base condition
        if (node == NULL)
            return;
                
        /// does a level exist for me to go to
        if (data.size() <= level) {
            /// make place to add myself and my neighbors
            vector<int> myLevel;
            data.push_back(myLevel);
        }

        /// add myself to this level
        data[level].push_back(node->val);

        /// now call my left child first
        recursiveTraversal(node->left, data, level+1);
        /// right child
        recursiveTraversal(node->right, data, level+1);
        
        return;
    }
    
};


/** ----------------------------------------------------------------------
 * Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

 * 
 --------------------------------------------------------------------- */
/** ----------------------------------------------------------------------
 * This problem is essentially computing the Catalan numbers
 * 
 --------------------------------------------------------------------- */

class CatalanNumbers {
  public:
    int numTrees(int n) {
        if (n < 1)
            return 1;

        vector<int> cont(n+1, -1);
        /// fill the zeroth element as 1
        cont[0] = 1;
        cont[1] = 1;
        
        recursiveCatalan(n, cont);
        
        return cont[n];
        
    }

    void recursiveCatalan(int n, vector<int>& cont) {
        int result = 0;
        /// iterate and split the number at different positions
        for (int j = 1; j <= n; j++) {
            /// check if I have the necessary subblocks
            
            if (cont[j-1] == -1)
                recursiveCatalan(j, cont);
            if (cont[n-j] == -1)
                recursiveCatalan(n-j, cont);
            
            result = result + (cont[j-1]*cont[n-j]);
        }
        
        cont[n] = result;
    }
    
};

/** ----------------------------------------------------------------------
 *  Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
 * 
 --------------------------------------------------------------------- */

class HasPath {
  public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == NULL)
            return false;
        
        
        /// assume I am on this path
        int rem = sum - root->val;

        /// is this too small already?
        /// if (rem < 0)
        /// return false;
        
        /// am I a leaf?
        if ((root->left == NULL) && (root->right == NULL)) {
            /// if nothing remains then there is a path
            if (rem == 0)
                return true;
            else
                return false;
        }

        bool left = false;
        bool right = false;;
        /// if I have a left subtree call it
        if (root->left != NULL)
            left = hasPathSum(root->left, rem);
        if (root->right != NULL)
            right = hasPathSum(root->right, rem);
        

        return (left || right);
        
        
    }

    
};




/** ----------------------------------------------------------------------
 *  Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value. 
 * 
 --------------------------------------------------------------------- */

class SameTree {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if ((p == NULL) && (q == NULL))
            return true;

        /// not same if one of them happens to be NULL
        if ((p == NULL) || (q == NULL))
            return false;

        /// now check their values here
        if (p->val != q->val)
            return false;
        
        /// go left on both
        bool left = isSameTree(p->left, q->left);
        /// go right
        bool right = isSameTree(p->right, q->right);

        return (left && right);
        
    }
};


/** ----------------------------------------------------------------------
 * Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321 
 * 
 --------------------------------------------------------------------- */
class ReverseDigits {
public:
    int reverse(int x) {
        vector<int> digits;
        int result = 0;
        
        /// use the absolute value
        int absval = abs(x);

        while (absval > 0) {
            digits.push_back(absval%10);
            /// reduce the number
            absval = floor(absval/10);
        }

        int power = digits.size() - 1;

        for (int i = 0; i < digits.size(); i++) {
            result += digits[i]*pow(10,power);
            /// reduce the power
            power -= 1;
        }

        /// if the number was negative change sign
        if (x < 0)
            result = -1*result;

        return result;
        
        
        
    }
};


/** ----------------------------------------------------------------------
 * Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
 * 
 --------------------------------------------------------------------- */

class MaxProfit {
  public:
    int maxProfit(vector<int> &prices) {
        /// compute the deltas
        int delta = 0;
        int result = 0;
        
        for (int i = 0; i < int(prices.size())-1; i++) {
            delta = prices[i+1] - prices[i];
            if (delta > 0)
                result += delta;
            
        }

        return result;
    }
};


/** ----------------------------------------------------------------------
 *  Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3. 
 * 
 --------------------------------------------------------------------- */

class RemoveDuplicates {
  public:
    ListNode *deleteDuplicates(ListNode *head) {
        /// sanity check
        if (head == NULL)
            return head;

        /// get the start node
        ListNode* current = head;

        while (current->next != NULL) {
            /// look forward one
            /// is it a duplicate?
            if (current->val == current->next->val) {
                /// remove the next one
                ListNode* duplicate = current->next;
                /// point yourself to its successor
                current->next = duplicate->next;
                /// delete the duplicate
                delete duplicate;
            } else {
                /// just go to the next node
                current = current->next;
            }
        }

        return head;
        
    }
};

/** ----------------------------------------------------------------------
 * Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0 
 * 
 --------------------------------------------------------------------- */

class InsertPosition {
  public:
    int searchInsert(int A[], int n, int target) {

        int idx = -1;
        
        /// iterate through the array and look for target
        for (int i = 0; i < n; i++) {
            /// is it the same as target?
            if (A[i] == target)
                return i;
            else if (A[i] < target)
                /// update the index if element is less than target
                idx = i;
        }
        return idx+1;
        
        
    }
};



/** ----------------------------------------------------------------------
 *  Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6. 
 * 
 --------------------------------------------------------------------- */

class MaxSubArray {
public:
    int maxSubArray(int A[], int n) {
        if (n < 1)
            return 0;
        
        /// linear O(n) run time
        /// sum should never go below 0 => else all elements are negative
        int sum = 0;
        
        int maxSoFar = INT_MIN;
        for (int i = 0; i < n; i++) {
            sum += A[i];
            maxSoFar = max(sum, maxSoFar);
            
            if (sum <= 0) {
                /// reset sum
                sum = 0;
            }
            
                
        }

        return maxSoFar;
        
        
    }
};


/** ----------------------------------------------------------------------
 * Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
 * 
 --------------------------------------------------------------------- */

class MergeList {
  public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        /// if one of the lists is blank return the other
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;

        ListNode* head = l1;
        /// get the first element
        if (l2->val < l1->val) {
            head = l2;
            l2 = l2->next;
        } else {
            head = l1;
            l1 = l1->next;
        }
        
        

        /// set a current pointer
        ListNode* current = head;

        while ((l1 != NULL) || (l2 != NULL)) {
            /// has l1 or l2 become null
            if (l1 == NULL) {
                current->next = l2;
                break;
            }
            if (l2 == NULL) {
                current->next = l1;
                break;
            }

            if (l1->val <= l2->val) {
                current->next = l1;
                /// step l1
                l1 = l1->next;
            } else {
                current->next = l2;
                /// step l2
                l2 = l2->next;
            }
            /// update current
            current = current->next;
        }

        return head;
        
    }
};

/** ----------------------------------------------------------------------
 * Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1. 
 * 
 --------------------------------------------------------------------- */

class CheckBalance {
  public:
    bool isBalanced(TreeNode *root) {
        int height;
        return recursiveHeight(root, height);
    }

    bool recursiveHeight(TreeNode* node, int& height) {
        if (node == NULL){
            height = 0;
            return true;
        }
        
        int leftH;
        /// is the left subtree balanced
        if (!recursiveHeight(node->left, leftH))
            return false;
        
        int rightH;
        if (!recursiveHeight(node->right, rightH))
            return false;

        /// if both subtrees are balanced: am I balanced?
        if (abs(leftH - rightH) > 1)
            return false;


        /// I am balanced: just update height
        height = max(leftH, rightH) + 1;

        return true;
        
    }
    
};


/** ----------------------------------------------------------------------
 * Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 * 
 --------------------------------------------------------------------- */

class CreateBST {
  public:
    TreeNode *sortedArrayToBST(vector<int> &num) {
        int n = num.size();
        return toBSTrecursive(num, 0, n-1);
    }
    
    /// (l, h)
    TreeNode* toBSTrecursive(vector<int>& num, int l, int h) {
        /// have we crossed over
        /// base case
        if (h < l)
            return NULL;

        int mid = l + floor((h-l)/2.0);

        /// create a TreeNode for this
        TreeNode* current = new TreeNode(num[mid]);
        
        /// get the left and right children for this
        current->left = toBSTrecursive(num, l, mid-1);

        current->right = toBSTrecursive(num, mid+1, h);
        
    }
    
};


/** ----------------------------------------------------------------------
 *  Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array A = [1,1,2],

Your function should return length = 2, and A is now [1,2]. 
 * 
 --------------------------------------------------------------------- */
/// !!!!---- TODO: Looked at solution

class RemoveDuplicatesArray {
  public:
    int removeDuplicates(int A[], int n) {
        if (n <= 1)
            return n;
        
        int ctr = 1;

        for (int i = 1; i < n; i++) {
            if (A[i] != A[i-1]) {
                A[ctr] = A[i];
                /// increment ctr
                ctr += 1;
            }
        }
        return ctr;
    }
};

/** ----------------------------------------------------------------------
 * Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.
 * 
 --------------------------------------------------------------------- */

class PlusOne {
public:
    vector<int> plusOne(vector<int> &digits) {

        vector<int> result;

        int rem = 1;
        
        /// iterate from the end of the array to the start
        for (int i = digits.size()-1; i >=0; i--) {
            int num = (digits[i]+rem)%10;
            result.push_back(num);
            rem = (digits[i]+rem)/10;
        }
        /// push the overflow digit
        if (rem > 0)
            result.push_back(rem);

        /// now reverse the results array
        int i = 0;
        int j = result.size()-1;

        while (i < j) {
            /// inplace swap
            result[i] = result[i] ^ result[j];
            result[j] = result[i] ^ result[j];
            result[i] = result[i] ^ result[j];
            /// update counters
            i += 1;
            j -=1;
        }
        return result;
        
    }
};

/** ----------------------------------------------------------------------
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
 * 
 --------------------------------------------------------------------- */
/// !!!!---- TODO: too slow; do a better implementation
#include <queue>
class MaxPaths {
  public:

    int uniquePaths(int m, int n) {
        /// instantiate a row vector the size of n
        vector<int> sweep(n, 0);

        /// initialize the last element in vector to 1
        sweep[n-1] = 1;
        
        for (int i = m-1; i >= 0; i--) {
            /// sweep through all grids for that row
            for (int j = n-2; j >=0; j--) {
                sweep[j] += sweep[j+1];
            }
        }

        return sweep[0];
        
        
    }
    
    
    struct Coordinate {
        int x;
        int y;
        
        Coordinate() {}

        Coordinate(int x, int y) : x(x), y(y) {}
    };
    
        
    int uniquePathsSlow(int m, int n) {
        if ((m < 1) || (n < 1))
            return 0;
        
        /// instantiate matrix of size mxn
        vector< vector<int> > matrix(m);
        /// initialize to zero
        for (int i = 0; i < m; i++)
            matrix[i].resize(n, 0);

        /// instantiate a queue to push possible paths
        queue<Coordinate> grids;

        grids.push(Coordinate(0,0));

        while(grids.size() > 0) {
            /// get the first element in queue
            Coordinate here = grids.front();
            grids.pop();

            std::cout << here.x << "\t" << here.y << std::endl;
            
            /// increment this grid counter
            matrix[here.x][here.y] += 1;
            
            /// can we go right?
            if (here.y+1 < n) 
                grids.push(Coordinate(here.x, here.y+1));
            /// can we go down?
            if (here.x+1 < m) 
                grids.push(Coordinate(here.x+1, here.y));

        }
        
        return matrix[m-1][n-1];
    }
    
};


/** ----------------------------------------------------------------------
 * Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]

 * 
 --------------------------------------------------------------------- */


class PascalsTriangle {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > pascal(numRows);
        
        if (numRows <= 0)
            return pascal;

        /// set the first 2 rows of pascals triangle
        /// first row
        pascal[0].push_back(1);

        if (numRows == 1)
            return pascal;

        /// second row
        pascal[1].resize(2);
        pascal[1][0] = 1;
        pascal[1][1] = 1;

        /// now start iterating through the rows
        for (int r = 3; r <=numRows; r++) {
            pascal[r-1].resize(r);
            /// set first element
            pascal[r-1][0] = 1;
            for (int k = 1; k < r-1; k++) {
                pascal[r-1][k] = pascal[r-2][k-1] + pascal[r-2][k];
            }
            
            /// set last element
            pascal[r-1][r-1] = 1;
        }
        
        return pascal;
        
    }
};


/** ----------------------------------------------------------------------
 * Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its bottom-up level order traversal as:

[
  [15,7],
  [9,20],
  [3]
]

 * 
 --------------------------------------------------------------------- */

class TraverseTree {
public:
    vector<vector<int> > levelOrderBottom(TreeNode *root) {

        /// first recursively traverse and find the height of tree
        int height = findHeight(root);

        /// instantiate a container of size height
        vector< vector<int> > traverse(height);
        
        traverseTree(root, traverse, height-1);

        return traverse;  
    }

    void traverseTree(TreeNode* node, vector< vector<int> >& traverse, int level) {
        /// base case
        if (node == NULL)
            return;
        
        /// push your data in the container
        traverse[level].push_back(node->val);

        /// go left
        traverseTree(node->left, traverse, level-1);
        /// go right
        traverseTree(node->right, traverse, level-1);
        
    }
    
    
    int findHeight(TreeNode* node) {
        /// base case
        if (node == NULL)
            return 0;

        return max(findHeight(node->left), findHeight(node->right)) + 1;
    }
    
};


/** ----------------------------------------------------------------------
 * Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
 * 
 --------------------------------------------------------------------- */

class MinPath {
  public:
    struct Coordinate {
        int x;
        int y;
        Coordinate() {}
        Coordinate(int x, int y) : x(x), y(y) {}
    };
    
    int minPathSum(vector<vector<int> > &grid) {
        vector<vector<int> > sumCosts(grid.size());
        vector<vector<bool> > visited(grid.size());

        int m = grid.size();
        int n;
        /// initialize with zeros
        for (int i = 0; i < grid.size(); i++) {
            sumCosts[i].resize(grid[i].size(), INT_MAX);
            visited[i].resize(grid[i].size(), false);
            n = grid[i].size();
        }

        /// initialize the start grid
        sumCosts[0][0] = grid[0][0];
        
        queue<Coordinate> nodes;
        nodes.push(Coordinate(0, 0));

        while (nodes.size() > 0) {
            Coordinate here = nodes.front();
            nodes.pop();

            /// go right
            if (here.x+1 < m) {
                /// update cost for the right grid
                sumCosts[here.x+1][here.y] =
                    min(sumCosts[here.x+1][here.y],
                        grid[here.x+1][here.y] + sumCosts[here.x][here.y]);
                /// only push if you havent been here before
                if (!visited[here.x][here.y])
                    nodes.push(Coordinate(here.x+1, here.y));
            }
            /// go down
            if (here.y+1 < n) {
                /// update cost for the right grid
                sumCosts[here.x][here.y+1] =
                    min(sumCosts[here.x][here.y+1],
                        grid[here.x][here.y+1] + sumCosts[here.x][here.y]);
                /// only push if you havent been here before
                if (!visited[here.x][here.y])
                    nodes.push(Coordinate(here.x, here.y+1));
            }

            /// mark youself as visited
            visited[here.x][here.y] = true;
        }
        
        return sumCosts[m-1][n-1];
                   
        
    }
};



/** ----------------------------------------------------------------------
 * You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?
 * 
 --------------------------------------------------------------------- */

class RotateImage {
public:
    void rotate(vector<vector<int> > &matrix) {
        /// get the size of matrix
        int n = matrix.size();

        for (int i = 0; i < n/2; i++) {
            for (int j = 0; j < n/2; j++) {
                /// rotate
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = tmp;
            }
        }

        /// if n is odd rotate the axis
        if (n%2 != 0) {
            int mid = n/2;
            /// go down the axis
            for (int k = 0; k < n/2; k++) {
                int tmp = matrix[k][mid];
                matrix[k][mid] = matrix[mid][k];
                matrix[mid][k] = matrix[n-1-k][mid];
                matrix[n-1-k][mid] = matrix[mid][n-1-k];
                matrix[mid][n-1-k] = tmp;
            }
        }
        
            
        
    }
    

    void mirror(vector<vector<int> > &matrix) {
        /// get the size of matrix
        int n = matrix.size();

        for (int i = 0; i < n; i++) {
            /// iterate one element less everytime
            for (int j = 0; j < n-i; j++) {
                int mirror_x = (n-1) - j;
                int mirror_y = (n-1) - i;

                int tmp = matrix[i][j];
                matrix[i][j] = matrix[mirror_x][mirror_y];
                matrix[mirror_x][mirror_y] = tmp;
            }
        }
        
        
    }
};


/** ----------------------------------------------------------------------
 *  Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1]. 
 * 
 --------------------------------------------------------------------- */

class Permutations {
  public:
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > cont(0);

        recursivePermute(num, 0, cont);

        return cont;
    }

    void recursivePermute(vector<int>& num, int idx, vector<vector<int> >& cont) {
        int n = num.size();
                
        /// base case
        if (idx == n-1) {
            vector<int> permute(num.size());
            permute[0] = num[idx];
            cont.push_back(permute);
            return;
        }

        /// recurse
        recursivePermute(num, idx+1, cont);

                
        int initSize = cont.size();
                
        /// iterate through the container and add yourself
        for (int i = 0; i < initSize; i++) {
            /// add yourself to the back of this
            cont[i][n-1-idx] = num[idx];
                        
            /// now iterate through and swap positions with all elements in permute
            for (int j = 0; j < n-1-idx; j++) {
                vector<int> permute = cont[i];
                permute[n-1-idx] = permute[j];
                permute[j] = num[idx];
                cont.push_back(permute);
            }
        }

        return;
            
    }
    
    
    vector<vector<int> > permuteWithLists(vector<int> &num) {
        vector<ListNode*> cont;
        recursivePermuteList(num, cont);

        /// create a vector container
        vector< vector<int> > permutations(cont.size());
        
        for (int i = 0; i < cont.size(); i++) {
            ListNode* node = cont[i];
            ListNode* prev = node;
            while(node != NULL) {
                std::cout << node->val << "\t";
                
                permutations[i].push_back(node->val);
                /// prev = node;
                node = node->next;
                /// delete prev;
            }
            std::cout << std::endl;
        }
        std::cout << "dont her" << std::endl;
        
        return permutations;
    }

    void recursivePermuteList(vector<int> num, vector< ListNode* >& cont) {
        /// base case
        if (num.size() == 1) {
            ListNode* node1 = new ListNode(num[0]);
            /// permutation 1
            node1->next = NULL;
            cont.push_back(node1);
            return;
        } else if (num.size() == 2) {
            {
            ListNode* node1 = new ListNode(num[0]);
            ListNode* node2 = new ListNode(num[1]);
            /// permutation 1
            node1->next = node2;
            node2->next = NULL;
            cont.push_back(node1);
            }
            {
                ListNode* node1 = new ListNode(num[0]);
                ListNode* node2 = new ListNode(num[1]);    
            /// permutation 2
            node1->next = NULL;
            node2->next = node1;
            cont.push_back(node2);
            return;
            }
            
        }

        /// call the recursive function with a shorted num
        vector<int> shorterNum(num.begin(), num.end()-1);
        
        recursivePermuteList(shorterNum, cont);

        std::cout << "cont: " << cont.size() << std::endl;

        
        /// number of elements that have being permuted
        int n = shorterNum.size();

        ListNode* me = new ListNode(num[num.size()-1]);
        
        /// iterate through the container and add yourself
        for (int i = 0; i < cont.size(); i++) {

            me->next = cont[i];
            /// update this list by adding youself upfront
            cont[i] = me;

            std::cout << "me upfront: " << i << std::endl;
            
            /// now iterate through list and add yourself everywhere
            for (int j = 1; j < n; j++) {
                std::cout << "j " << j << std::endl;
                ListNode* newList = cont[i];
                ListNode* spot = newList;
                /// move to spot
                int ctr = 0;
                while (ctr < j) {
                    spot = spot->next;
                    ctr++;
                }
                me->next = spot->next;
                spot->next = me;
                cont.push_back(newList);
            }
        }
        
        return;
    }
    
};


/** ----------------------------------------------------------------------
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

    Integers in each row are sorted from left to right.
    The first integer of each row is greater than the last integer of the previous row.

For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]

Given target = 3, return true
 * 
 --------------------------------------------------------------------- */

class MatrixSearch {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        /// get size
        int m = matrix.size();

        for (int i = 0; i < m; i++) {
            int n = matrix[i].size();
            
            /// is target in the range of this row
            if ((matrix[i][0] <= target) && (matrix[i][n-1] >= target)) {
                /// has to be in this row
                for (int j = 0; j < n; j++) {
                    if (matrix[i][j] == target)
                        return true;
                }
                /// did not find it in the row: doesn't exist
                return false;
            }
        }

        /// checked all rows and didn't find it
        return false;
        
        
    }
};



/** ----------------------------------------------------------------------
 * Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container
 * 
 --------------------------------------------------------------------- */


class MaxWaterContainer {
public:
    int maxArea(vector<int> &height) {
        /// initialize to indices at start and end
        int i = 0;
        int j = height.size()-1;
        int maxArea = 0;

        while (i < j) {
            maxArea = max(maxArea, (j-i)*min(height[j],height[i]));

            /// move the idx that is shorter
            if (height[i] < height[j])
                i++;
            else
                j--;
        }
        
        return maxArea;
    }
};



/** ----------------------------------------------------------------------
 * Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
 * 
 --------------------------------------------------------------------- */

class MaxProfitStock {
public:
    int maxProfit(vector<int> &prices) {
        if (prices.size() < 2)
            return 0;
        
        /// compute delta vector
        vector<int> delta(prices.size()-1);
        
        for (int i = 0; i < prices.size()-1; i++)
            delta[i] = prices[i+1] - prices[i];

        int maxSoFar = 0;
        int sum = 0;
        
        /// not simply compute the max sum in the delta vector
        for (int j = 0; j < delta.size(); j++) {
            sum += delta[j];
            /// get the better max
            maxSoFar = max(maxSoFar, sum);
            /// if sum has gone negative reset
            if (sum < 0)
                sum = 0;
        }
        
        return maxSoFar;
        
    }
};

/** ----------------------------------------------------------------------
 *  Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place. 
 * 
 --------------------------------------------------------------------- */

class MatrixZeros {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        /// get size
        int m = matrix.size();
        /// hashing container
        vector<bool> rows(m, false);
        
        if (m < 1)
            return;
        
        /// hashing container
        int n = matrix[0].size();

        vector<bool> cols(n, false);
        
        /// first pass: iterate through the matrix looking for zeros
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    rows[i] = true;
                    cols[j] = true;
                }
            }
        }

        /// second pass: hash in and zero out
        /// so cool
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rows[i] || cols[j])
                    matrix[i][j] = 0;
            }
        }
        
    }
};


/** ----------------------------------------------------------------------
 * Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space? 
 * 
 --------------------------------------------------------------------- */

class PascalsTriangle2 {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> pascal;
        /// manually setup the first 2 rows
        pascal.push_back(1);
        if (rowIndex == 0)
            return pascal;
        pascal.push_back(1);
        if (rowIndex == 1)
            return pascal;

        /// step through the rows
        for (int row = 2; row <= rowIndex; row++) {
            vector<int> newPascal(row+1);
            newPascal[0] = 1;
            
            /// iterate through and update the pascal vector
            for (int p = 1; p < pascal.size(); p++) {

                newPascal[p] = pascal[p-1] + pascal[p];
            }
            /// finally increase the vector size by pushing a one
            newPascal[newPascal.size()-1] = 1;
            
            pascal = newPascal;
            
        }

        return pascal;
        
    }
};

/** ----------------------------------------------------------------------
 *  Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

 * 
 --------------------------------------------------------------------- */
/// !!!!---- TODO: 
class NchooseK {
  public:
    bool has(const vector<int>& comb, int e) {
        for (int i = 0; i < comb.size(); i++) {
            if (comb[i] == e)
                return true; 
        }
        return false;
    }
    
    vector<vector<int> > combine(int n, int k) {

        /// problem is to return all n choose k
        vector<vector<int> > comb;

        /// for n choose 1 simply add all n to the container
        for (int j = 1; j <= n; j++) {
            vector<int> single;
            single.push_back(j);
            comb.push_back(single);
        }
        
        
        for (int i = 2; i <= k; i++) {
            /// iterate through container and for each vector
            /// add an element that is not already in it
            int initSize = comb.size();
            for (int s = 0; s < initSize; s++) {
                bool addHere = true;
                vector<int> orig = comb[s];
                for (int j = 1; j <= n; j++) {
                    /// if not present add it in
                    if (!has(orig, j)) {
                        if (addHere) {
                            comb[s].push_back(j);
                            addHere = false;
                        } else {
                            comb.push_back(orig);
                            comb[comb.size()-1].push_back(j);
                        }
                    }
                }

            }
        }
        
        return comb;
    }
};

/** ----------------------------------------------------------------------
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25. 
 * 
 --------------------------------------------------------------------- */


class RootToLeaf {
  public:
    /// need some form of a depth first search
    int sumNumbers(TreeNode *root) {
        vector<vector<int> > paths = recurseToLeaf(root);

        int sum = 0;
        
        /// iterate and add all the path nums
        for (int i = 0; i < paths.size(); i++) {
            /// create a num from vector
            int num = 0;
            for (int j = 0; j < paths[i].size(); j++) 
                num += paths[i][j]*pow(10,j);
            
            sum += num;
        }
        
        return sum;
    }

    vector<vector<int> > recurseToLeaf(TreeNode* node) {
        vector< vector<int> > paths;
        /// base case
        if (node == NULL)
            return paths;

        /// get paths from my children
        vector<vector<int> > children = recurseToLeaf(node->left);
        vector<vector<int> > right = recurseToLeaf(node->right);
        /// merge
        children.insert(children.end(), right.begin(), right.end());
        
        /// am I a leaf?
        if (children.size() < 1) {
            paths.push_back(vector<int>(1, node->val));
        } else {
            /// prefix myself to every path
            for (int i = 0; i < children.size(); i++)
                children[i].push_back(node->val);
            paths = children;
        }
        
        return paths;
        
    }

    int doprefix(int num, int prefix) {
        /// special case
        if (num == 0) {
            return 10*prefix;
        }
        
        /// compute # digits in num
        int digits = 0;
        int n = num;

        while (n > 0) {
            n = n/10;
            digits++;
        }

        /// multiply prefix by a power of 10 higher and add
        int result = (prefix*pow(10,digits)) + num;
        
        return result;
    }
    
};



/** ----------------------------------------------------------------------
 * Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Try to do this in one pass. 
 * 
 --------------------------------------------------------------------- */

class RemoveNthNode {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode* nForward = head;

        for (uint i = 1; i <= n; i++)
            nForward = nForward->next;

        /// has nForward reached the end
        /// we need to remove the head in this case
        if (nForward == NULL) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }
        
        
        ListNode* before = head;

        while (nForward->next != NULL) {
            before = before->next;
            nForward = nForward->next;
        }
        
        ListNode* toRemove = before->next;
        before->next = toRemove->next;
        delete toRemove;

        return head;
        
        
    }
};



/** ----------------------------------------------------------------------
 * Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
 * 
 --------------------------------------------------------------------- */

class MinimumDepth {
public:
    int minDepth(TreeNode *root) {
        /// base case
        if (root == NULL)
            return 0;

        int depth = 1;
        
        /// if both children exist
        if ((root->left != NULL) && (root->right != NULL))
            depth = min(minDepth(root->left), minDepth(root->right)) + 1;
        else if (root->left != NULL)
            depth = minDepth(root->left) + 1;
        else if (root->right != NULL)
            depth = minDepth(root->right) + 1;

        return depth;
        
    }
};


/** ----------------------------------------------------------------------
 * Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,
Given s = "Hello World",
return 5
 * 
 --------------------------------------------------------------------- */

class LengthWord {
public:
    int lengthOfLastWord(const char *s) {
        
        string str(s);

        int lastCharIdx = -1;
        int wordIdx = 0;
        bool spaceStarted;
        
        
        for (uint i = 0; i < str.size(); i++) {
            if (str[i] == ' ') {
                spaceStarted = true;
            } else {
                if (spaceStarted) {
                    spaceStarted = false;
                    wordIdx = i;
                }
                lastCharIdx = i;
            }
        }
        
        return (lastCharIdx - wordIdx) + 1;
        
    }
};



/** ----------------------------------------------------------------------
 * Determine whether an integer is a palindrome. Do this without extra space.
 * 
 --------------------------------------------------------------------- */

class Palindrome {
public:
    bool isPalindrome(int x) {

        if (x < 0)
            return false;
        
        
        /// in the first pass calculate number of digits in x
        int num = x;
        int digits = 0;
        while (num > 0) {
            digits += 1;
            num = num/10;
        }

        std::cout << digits << std::endl;
        
        /// second pass: compare opposing digits
        int i = 0;
        
        while (i < digits/2) {
            int dig1 = static_cast<int>((x/pow(10, i)))%10;
            int dig2 = static_cast<int>((x/pow(10, digits-(i+1))))%10;

            std::cout << dig1 << "\t" << dig2 << std::endl;
            
            if (dig1 != dig2)
                return false;

            i++;
            
        }

        return true;
    }
};


/** ----------------------------------------------------------------------
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 * 
 --------------------------------------------------------------------- */

class Parenthesis {
public:
    bool isValid(string s) {
        /// we will use a stack to do this
        stack<char> paren;

        for (uint i = 0; i < s.size(); i++) {
            /// check for opening brackets
            if ((s[i] == '(') || (s[i] == '{')  || (s[i] == '[')) {
                paren.push(s[i]);
            } else {
                /// is the stack empty?
                if (paren.size() < 1)
                    return false;

                char onTop = paren.top();
                
                /// match this character to whats on top of stack
                if ((s[i] == ')') && (onTop == '('))
                    paren.pop();
                else if  ((s[i] == '}') && (onTop == '{'))
                    paren.pop();
                else if  ((s[i] == ']') && (onTop == '['))
                    paren.pop();
                else
                    return false;    

            }       
        }

        /// make sure the stack is empty again
        if (paren.size() > 0)
            return false;
        else
            /// successfully completed string
            return true;
        
            

    }
};


/** ----------------------------------------------------------------------
 * Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'
 * 
 --------------------------------------------------------------------- */

class Sudoku {
public:
    bool isValidSudoku(vector<vector<char> > &board) {

        vector<uint> hash(10, 0);

        /// we need 9 hashes per constraint: row, column, square
        vector< vector<uint> > rowHash(9, hash);
        vector< vector<uint> > columnHash(9, hash);
        vector< vector<uint> > squareHash(9, hash);

        /// now iterate through the board and check hashes
        for (uint i = 0; i < 9; i++) {
            for (uint j = 0; j < 9; j++) {
            
                /// is it filled?
                uint digit = board[i][j] - '0';
                if (digit > 10)
                    continue;

  

                /// check the row hash
                if (rowHash[i][digit] > 0) {
                    return false;
                }
                
                /// update the row hash
                rowHash[i][digit] += 1;

                /// check the column hash
                if (columnHash[j][digit] > 0) {
                    return false;
                }
                
                /// update the column hash
                columnHash[j][digit] += 1;

                /// compute the square index
                uint sqrIdx = (i/3) + 3*(j/3);
                if (squareHash[sqrIdx][digit] > 0) {
                    return false;
                }
                
                squareHash[sqrIdx][digit] += 1;
                    
            }
        }

        return true;
        
    }
};


/** ----------------------------------------------------------------------
 * The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string. 
 * 
 --------------------------------------------------------------------- */

class CountAndSay {
public:
    string countAndSay(int n) {
        string seq;
        if (n < 1)
            return seq;

        int ctr = 1;
        seq.push_back('1');
        

        while (ctr < n) {
            /// std::cout << "s: " << seq << std::endl;
            
            int dig = seq[0] -  '0';
            int numDig = 1;

            vector<pair<int, int> > numbers;
            
            /// iterate through the string and isolate digits
            for (uint i = 1; i < seq.size(); i++) {
                if ((seq[i] - '0') != dig) {
                    numbers.push_back(make_pair(dig, numDig));
                    numDig = 0;
                    dig = seq[i] - '0';
                    /// std::cout << "d: " << dig << "\t" << seq[i] << std::endl;
                    
                }
                numDig += 1;
            }

            /// add the final digit
            numbers.push_back(make_pair(dig, numDig));

            /// start a new string to build up
            string newSeq;
            for (uint i = 0; i < numbers.size(); i++) {
                /// std::cout << numbers[i].first << "\t" << numbers[i].second << std::endl;
                
                newSeq.push_back('0' + numbers[i].second);
                newSeq.push_back('0' + numbers[i].first);
                /// newSeq.push_back('9');
            }

            seq = newSeq;

            ctr += 1;
            
        }
        
        return seq;
        
        
    }

};


/** ----------------------------------------------------------------------
 * Given an array and a value, remove all instances of that value in place and return the new length.

The order of elements can be changed. It doesn't matter what you leave beyond the new length. 
 * 
 --------------------------------------------------------------------- */

class RemoveElement {
public:
    int removeElement(int A[], int n, int elem) {
        if (n < 1)
            return n;
        
        int storeIdx = 0;

        for (uint i = 0; i < n; i++) {
            if (A[i] != elem) {
                A[storeIdx] = A[i];
                
                /// increment store idx
                storeIdx += 1;
                std::cout << A[i] << "\t" << A[storeIdx] << std::endl;
                
            }
        }
        return storeIdx;
        
        
    }
};


/** ----------------------------------------------------------------------
 *  Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100". 
 * 
 --------------------------------------------------------------------- */

class SumBinary {
public:
    string addBinary(string a, string b) {
        /// iterate both the strings backwards
        int i = a.size()-1;
        int j = b.size()-1;

        int rem = 0;
        int sum = 0;
        string sumStr;
        sumStr.resize(max(a.size(), b.size()) + 1);
        
        while ((i >= 0) || (j >= 0)) {
            /// check if one of the strings have completed
            if (i < 0) 
                sum = rem + (b[j] - '0');
            else if (j < 0)
                sum = rem + (a[i] - '0');
            else
                sum = rem + (a[i] - '0') + (b[j] - '0');

            rem = sum/2;
            sumStr.push_back('0' + sum%2);
            
            i--;
            j--;
        }

        /// add the left over bit if any
        if (rem > 0)
            sumStr.push_back('0' + rem);

        reverse(sumStr);
        
        /// finally reverse and return the string
        
        return sumStr;
        
    }

    void reverse(string& s) {
        int i = 0;
        int j = s.size()-1;

        while (i < j) {
            /// swap the ith and jth index
            s[i] = s[i] ^ s[j];
            s[j] = s[i] ^ s[j];
            s[i] = s[i] ^ s[j];
            i++;
            j--;
            
        }
    }
    
};


/** ----------------------------------------------------------------------
 * Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11). 
 * 
 --------------------------------------------------------------------- */

class MinPathTriangle {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int numRows = triangle.size();

        vector<int> minVals(numRows);

        /// initialize this array with the bottom row
        for (int i = 0; i < triangle[numRows-1].size(); i++)
            minVals[i] = triangle[numRows-1][i];
        
        
        /// iterate bottom up to the root
        for (int r = numRows-2; r >= 0; r--) {
            vector<int> newMinVals(r+1);

            /// iterate through and pick the min of 2 children
            for (int i = 0; i <= r; i++)
                newMinVals[i] =
                    min(minVals[i], minVals[i+1]) + triangle[r][i];

            /// update the minVals vector
            minVals.clear();
            minVals = newMinVals;        

        }

        return minVals[0];
        
    }
};


/** ----------------------------------------------------------------------
 *  Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

 * 
 --------------------------------------------------------------------- */

class Combinations {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<int> comb;

        vector< vector<int> > allCombs;
        recursiveCombine(n, k, 1, comb, allCombs);

        return allCombs;
    }

    void recursiveCombine(int n, int k, int start,
                          vector<int> comb, vector<vector<int> >& all) 
    {
        /// base case
        if (k == 0) {
            /// simply add whatever you got to the main one
            all.push_back(comb);
        }

        for (int i = start; i <=n; i++) {
            vector<int> passedIn(comb);
            passedIn.push_back(i);
            recursiveCombine(n, k-1, i+1, passedIn, all);
        }
        return;
    }
    
    
};


/** ----------------------------------------------------------------------
 *  Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false. 
 * 
 --------------------------------------------------------------------- */
/// Works but gives Time Limit exceeded error on Leetcode
class JumpDP {
public:
    bool canJumpBackwards(int A[], int n) {
        /// instantite a memoization container
        vector<bool> memCont(n, false);

        /// initialize the last element to true (goal)
        memCont[n-1] = true;

        
        /// iterate from the goal backwards
        for (int i = n-2; i>=0; i--) {
            /// cycle through the possible jump lengths
            /// break as soon as one takes you to goal
            int cyc = 1;
            while (cyc <= A[i]) {
                if (i + cyc >= n)
                    break;
                
                /// index in to check
                bool val = memCont[i+cyc];
                if (val) {
                    memCont[i] = true;
                    break;
                }
                cyc += 1;
                
            }
        }
        /// return the first element
        return memCont[0];
        
    }


    bool canJump(int A[], int n) {
        vector<int> memCont(n, -1);

        memCont[n-1] = 1;
        
        recursiveJumps(A, n, 0, memCont);

        
        return memCont[0];
        
    }
    
    void recursiveJumps(int A[], int n, int start, vector<int>& memCont) {
        /// sanity check
        if (start >= n)
            return;
        
        /// move forward from the start position
        int cyc = 1;

        while (cyc <= A[start]) {
            int jumpTo = start + cyc;
            /// reduce cycle 
            cyc += 1;
            
            /// recursively jump and check if there is a path from here
            /// is this jump within bounds?
            if (jumpTo >= n)                 
                break;
            
            /// do we have a value for this jump?
            if (memCont[jumpTo] == -1) {
                /// recurse to find value
                recursiveJumps(A, n, jumpTo, memCont);
            }

            /// now check are we good?
            if (memCont[jumpTo] == 1) {
                /// yes we can move forward from here
                memCont[start] = 1;
                /// lets head back
                return;
            } /// else keep going    
            

        }

        /// oops cycled through it all and no luck
        memCont[start] = 0;
        
    }
    
};

/** ----------------------------------------------------------------------
 * Implement int sqrt(int x).

Compute and return the square root of x.
 * 
 --------------------------------------------------------------------- */

class SquareRoot {
public:
    int sqrt(int x) {
        if (x <= 0)
            return 0;
        
        if (x <= 2)
            return 1;
        
        /// do a binary search for the square root
        int div = 2;
        int quot = x/div;

        /// iterate while the two dont match
        while (div != quot) {
            std::cout << "d: " << div << "\t q: " << quot << std::endl;

            /*
            if (div < quot)
                div = div + ceil((quot - div)/2.0);
            else if (quot < div)
                div = quot + ceil((div - quot)/2.0);
            */

            if (div == (div+quot)/2)
                break;
            /// update divisor
            div = (div+quot)/2;
            
            /// recompute quotient
            quot = round(x*1.0/div);
        }
        

        return div;
        
    }
};



/** ----------------------------------------------------------------------
 *  Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity. 
 * 
 --------------------------------------------------------------------- */

class LongestConsecutive {
public:
    int longestConsecutive(vector<int> &num) {
        std::unordered_map<int, int> mymap;
        int maxSoFar = 0;
        
        /// iterate through the vector and keep hashing
        for (int i = 0; i < num.size(); i++) {
            int nmb = num[i];

            /// make sure we ve never seen this before
            std::unordered_map<int, int>::const_iterator me = mymap.find(nmb);
            if (me != mymap.end())
                continue;
            
            /// check if this number has neighbors in the hash
            std::unordered_map<int, int>::const_iterator lower = mymap.find(nmb - 1);
            std::unordered_map<int, int>::const_iterator upper = mymap.find(nmb + 1);

            int newLen = 0;
            
            /// if both exist: i should update the ends for both
            if ((lower != mymap.end()) && (upper != mymap.end())) {
                int leftLen = mymap[nmb-1];
                int rightLen =mymap[nmb+1];
                newLen = leftLen + rightLen + 1;
                /// update the three points
                mymap[nmb - leftLen] = newLen;
                mymap[nmb + rightLen] = newLen;
                mymap[nmb] = newLen;
            } else if (lower != mymap.end()) {
                int leftLen = mymap[nmb-1];
                newLen = leftLen + 1;
                /// update the three points
                mymap[nmb - leftLen] = newLen;
                mymap[nmb] = newLen;
            } else if (upper != mymap.end()) {
                int rightLen =mymap[nmb+1];
                newLen = rightLen + 1;
                /// update the three points
                mymap[nmb + rightLen] = newLen;
                mymap[nmb] = newLen;
            } else {
                newLen = 1;
                mymap[nmb] = 1;
            }
            
            
            /// is this the largest you ve seen so far
            if (newLen > maxSoFar)
                maxSoFar = newLen;
            
        }
        
        return maxSoFar;
        
    }
};


/** ----------------------------------------------------------------------
 *  Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code"
 * 
 --------------------------------------------------------------------- */

class WordBreak {
  public:
    bool wordBreak(string s, unordered_set<string> &dict) {
        /// create a memoized container the size of the string
        vector<int> memCont(s.size() + 1, -1);
        memCont[s.size()] = 1;

        recursiveBreak(s, 0, dict, memCont);

        return memCont[0];
        
    }

    void recursiveBreak(string s, int start,
                        unordered_set<string> &dict, vector<int>& memCont) {


        /// iterate from start and check if a word is made
        for (int i = start; i < s.size(); i++) {
            string substr(s, start, (i-start)+1);
            /// does this substring exist in dictionary
            if (dict.count(substr) > 0) {
                /// it exists
                /// now can we make a word from the rest of it
                if (memCont[i+1] == 1) {
                    /// we're good with the rest of it
                    memCont[start] = 1;
                    return;
                } else if (memCont[i+1] == -1) {
                    /// dont know yet? well lets find out
                    recursiveBreak(s, i+1, dict, memCont);
                    /// now we know - so lets check
                    if (memCont[i+1] == 1) {
                    /// we're good with the rest of it
                    memCont[start] = 1;
                    return;
                    }
                } else {
                    /// keep going forward and look for more
                    continue; // unnnecessary
                }
            }
        }

        /// if we have looped through out - that means no luck
        memCont[start] = 0;
return;
        
    }
    
};


/** ----------------------------------------------------------------------
 *  Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,

X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

 * 
 --------------------------------------------------------------------- */


class SurrooundedRegion {
public:
    void solve(vector<vector<char>> &board) {
         /// m rows and n columns
        int m = board.size();
        if (m < 1)
            return;
        int n = board[0].size();
        
        /// iterate through the board and find 0s
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                /// is this a O
                if (board[i][j] == 'O') {
                    /// do a depth first and capture
                    capture(board, i, j);
                }
                
            }
        }
        std::cout << "Did something \n";
        
    }

    void capture(vector<vector<char>> &board, int s_i, int s_j) {
        /// m rows and n columns
        int m = board.size();
        if (m < 1)
            return;
        int n = board[0].size();

        /// instantiate a stack to keep track of search
        stack<pair<int, int> > points;

        vector<pair<int, int> > toCapture;

        bool captureIt = true;
        
        /// push yourself onto the stack
        points.push(make_pair(s_i, s_j));

        while(points.size() > 0) {

            int i = points.top().first;
            int j = points.top().second;

            
            
            /// add point to a separate vector to capture later
            toCapture.push_back(pair<int, int>(points.top()));

            /// remove from stack
            points.pop();
            
            /// have we reached the bounds of the board
            if ((i+1 >= m) || (i-1 < 0)) {
                captureIt = false;
                break;
            }
            
            
            if ((j+1 >= n) || (j-1 < 0)) {
                captureIt = false;
                break;
            }
            
            /// check around you
            if (board[i][j+1] == 'O')
                points.push(make_pair(i, j+1));    
            
            
            if (board[i][j-1] == 'O')
                points.push(make_pair(i, j-1));    
            
            
            if (board[i+1][j] == 'O')
                points.push(make_pair(i+1, j));    
            
            
            if (board[i-1][j] == 'O')
                points.push(make_pair(i-1, j));
        }

        /// now capture the points
        if (!captureIt)
            return;
        
        for (int i = 0; i < toCapture.size(); i++) 
            board[toCapture[i].first][toCapture[i].second] = 'X';

        return;
    }
};


/** ----------------------------------------------------------------------
 *  Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return

[
   [5,4,11,2],
   [5,8,4,5]
]

 * 
 --------------------------------------------------------------------- */

class PathSum2 {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int>> ret;
        if (root == NULL)
            return ret;

        recursivePath(root, sum, vector<int>(), ret);

        return ret;
        
        
    }


    void recursivePath(TreeNode* node, int sum, vector<int> path,
                       vector<vector<int>>& ret) {
        
        int newsum = sum - node->val;
        vector<int> newpath = path;
        newpath.push_back(node->val);
        
        /// is this a leaf
        if ((node->left == NULL) && (node->right == NULL)) {
            ///
            if (newsum == 0)
                ret.push_back(newpath);
        }
        
        /// if left exists - go left
        if (node->left != NULL) {
            recursivePath(node->left, newsum,
                          newpath, ret);
        }

        if (node->right != NULL) {
            recursivePath(node->right, newsum,
                          newpath, ret);
        }
        
        
    }
    
};


/** ----------------------------------------------------------------------
 *  Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.

 * 
 --------------------------------------------------------------------- */

class ValidateBST {
public:
    bool isValidBST(TreeNode *root) {

        int max = INT_MAX;
        int min = INT_MIN;

        return recursiveValidation(root, max, min);
        
    }

    bool recursiveValidation(TreeNode* node, int max, int min) {

        /// base case
        if (node == NULL)
            return true;

        /// is my value within range
        if ((node->val <= min) || (node->val >= max)) {
            return false;
        }

        /// go left
        /// max becomes you
        bool leftRes = recursiveValidation(node->left, node->val, min);

        /// go right
        /// min becomes you
        bool rightRes = recursiveValidation(node->right, max, node->val);

        return (leftRes && rightRes);
        
    }
    
};


/** ----------------------------------------------------------------------
 * Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

 * 
 --------------------------------------------------------------------- */

class BinaryTreeCombos {
public:
    vector<TreeNode *> generateTrees(int n) {
        vector<TreeNode *> ret;

        /// iterate through and pick every element
        
        
    }

    vector<TreeNode*> recursiveGeneration(int start, int end) {
        
    }
    

    TreeNode* generateBST(int start, int end) {
        if (start > end)
            return NULL;
        
        int mid = (start + end)/2;

        TreeNode*  node = new TreeNode(mid);

        /// generate a tree on the left
        node->left = generateBST(start, mid-1);
        node->right = generateBST(mid+1, end);

        return node;
    }
    
};




/** ----------------------------------------------------------------------
 * 
 * 
 --------------------------------------------------------------------- */

class SortColors {
public:
    void sortColors(int A[], int n) {
        /// initialize a colors array
        int col[3];
        col[0] = 0;
        col[1] = 0;
        col[2] = 0;

        /// iterate through the array A
        for (uint i = 0; i < n; i++)
            col[A[i]] += 1;

        /// now reorganize the colors
        int ctr = 0;
        for (uint c = 0; c < 3; c++) {
            int trk = 0;
            while (trk < col[c]) {
                A[ctr] = c;
                ctr += 1; trk += 1;
            }
            
        }
    }
    
};


/** ----------------------------------------------------------------------
 * You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
 * 
 --------------------------------------------------------------------- */

class AddTwoLists {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {

        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;        

        /// head of the sum of two lists
        ListNode* sum = new ListNode((l1->val + l2->val)%10);

        int rem = (l1->val + l2->val)/10;

        /// advance the pointers
        l1 = l1->next;
        l2 = l2->next;
        
        /// pointer to iterate over the list
        ListNode* trk = sum;

        int lSum = 0;
        
        /// iterate over both the lists simultaneously
        while ((l1 != NULL) || (l2 != NULL)) {
            
            lSum = rem;
            if (l1 != NULL) {
                lSum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                lSum += l2->val;
                l2 = l2->next;
            }
            
            /// set this value in trk
            /// it should already be instantiated
            trk->next = new ListNode(lSum%10);
            rem = lSum/10;
            
            /// move the pointer forward
            trk = trk->next;


        }

        if (rem > 0)
            trk->next = new ListNode(rem);
        
        return sum;
        
        
    }
};


/** ----------------------------------------------------------------------
 * Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3.
 For "bbbbb" the longest substring is "b", with the length of 1.
 * 
 --------------------------------------------------------------------- */

/// Answer seems right but fails in leetcode for somereason
class LongestSubstring {
public:
    int lengthOfLongestSubstring(string s) {

        unordered_set<char> hash;

        int maxSoFar = 0;
        int runMax = 0;
        
        for (uint i = 0; i < s.size(); i++) {
            if (hash.count(s[i]) > 0) {
                if (runMax > maxSoFar)
                    maxSoFar = runMax;
                std::cout << runMax << std::endl;
                
                /// erase the hash
                hash.clear();
                runMax = 0;
                
            }
            
            hash.insert(s[i]);
            runMax += 1;
            
        }

        /// do a final check again
        if (runMax > maxSoFar)
            maxSoFar = runMax;
                
        return maxSoFar;
        
        
    }
};


/** ----------------------------------------------------------------------
 * Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

 * 
 --------------------------------------------------------------------- */

class PhoneCombinations {
public:
    vector<string> letterCombinations(string digits) {
        /// manually enter the characters in a vector for now
        vector<string> digitMaps(10, "");
        digitMaps[2] = "abc";
        digitMaps[3] = "def";
        digitMaps[4] = "ghi";
        digitMaps[5] = "jkl";
        digitMaps[6] = "mno";
        digitMaps[7] = "pqrs";
        digitMaps[8] = "tuv";
        digitMaps[9] = "wxyz";

        vector<string> allMaps;
        string empty = "";

        recursiveMapping(digits, 0, empty, allMaps, digitMaps);

        return allMaps;
        
    }

    void recursiveMapping(string digits, int start, string& map, vector<string>& allMaps, vector<string> digitMaps) {
        /// base case
        /// iff all digits have been covered push this map
        if (start >= digits.size()) {
            allMaps.push_back(map);
            return;
        }
        

        int thisDig = digits[start] - '0';

        /// does this digit map to something?
        if (digitMaps[thisDig].size() <= 0) {
            recursiveMapping(digits, start+1, map, allMaps, digitMaps);
            return;
        }
        
            
        /// iterate through all elements that can be appended with this digit
        for (int i = 0; i < digitMaps[thisDig].size(); i++) {
            string inp = map;
            inp.push_back(digitMaps[thisDig][i]);
            recursiveMapping(digits, start+1, inp, allMaps, digitMaps);
        }
    }
    
};


/** ----------------------------------------------------------------------
 *  Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space? 
 * 
 --------------------------------------------------------------------- */

class ListCycle {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL)
            return false;
        
        /// initialize 2 pointers to traverse the list
        ListNode* slower = head;

        if (head->next == NULL)
            return false;
        
        ListNode* runner = head->next->next;

        /// traverse while the runner has not reached the end
        while (runner != NULL) {
            /// have the runner and slower collided
            if (runner == slower)
                return true;

            /// move slower by
            slower = slower->next;

            if (runner->next == NULL)
                break;
            runner = runner->next->next;
        }

        /// done traversing
        return false;
        
        
        
    }
};


/** ----------------------------------------------------------------------
 *  Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the". 
 * 
 --------------------------------------------------------------------- */

class ReverseString {
public:
    void reverseWords(string &s) {
        if (s == " ") {
            s = "";
            return;
        }
        
            
        /// reverse the whole string first
        reverseString(s, 0, s.size()-1);

        
        
        int w_start = 0;

        while (s[w_start] == ' ') {
            w_start += 1;
        }
        
        /// now iterate through and flip individual words
        for (uint i = w_start; i < s.size(); i++) {
            /// is this a space
            if (s[i] == ' ') {
                reverseString(s, w_start, i-1);
                /// reset the w_start
                w_start = i+1;
            }
        }
        /// reverse the last word if need be
        reverseString(s, w_start, s.size()-1);
        
        
    }

    void reverseString(string& s, int start, int end) {
        /// sanity check
        if ((start < 0) || (end >= s.size()))
            return;
        
        /// start and end are both inclusive

        int i = start;
        int j = end;

        while (i < j) {
            /// swap i and j
            s[i] = s[i] ^ s[j];
            s[j] = s[i] ^ s[j];
            s[i] = s[i] ^ s[j];

            /// update counter
            i += 1;
            j -= 1;
        }
    }
    
};



/** ----------------------------------------------------------------------
 *  Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution? 
 * 
 --------------------------------------------------------------------- */

class RecoverTree {
public:
    void recoverTree(TreeNode *root) {

        TreeNode* violator = findViolator(root, INT_MIN, INT_MAX);

        if (violator != NULL) {
            /// the root itself is in violation
            violator->val = violator->val ^ root->val;
            root->val = violator->val ^ root->val;
            violator->val = violator->val ^ root->val;

        }
        
    }

    TreeNode* findViolator(TreeNode* node, int min, int max) {
        /// base case
        if (node == NULL)
            return NULL;

        /// am I a violator?
        bool selfViolator = (node->val < min) || (node->val > max);
        
        
        /// do my children contain violators?
        TreeNode* leftViolator = findViolator(node->left, min, node->val);
        TreeNode* rightViolator = findViolator(node->right, node->val, max);

        /// do I have both violators to swap?
        if ((leftViolator != NULL) && (rightViolator != NULL)) {
            /// swap their values
            leftViolator->val = leftViolator->val ^ rightViolator->val;
            rightViolator->val = leftViolator->val ^ rightViolator->val;
            leftViolator->val = leftViolator->val ^ rightViolator->val;

            return NULL;
            
        } else if (selfViolator && (leftViolator != NULL)) {

            leftViolator->val = leftViolator->val ^ node->val;
            node->val = leftViolator->val ^ node->val;
            leftViolator->val = leftViolator->val ^ node->val;

            return NULL;
            
        } else if (selfViolator && (rightViolator != NULL)) {

            rightViolator->val = rightViolator->val ^ node->val;
            node->val = rightViolator->val ^ node->val;
            rightViolator->val = rightViolator->val ^ node->val;

            return NULL;
            
        } else if (selfViolator) {
            return node;
        }
        

        /// finally check if a child is a violator
        if (leftViolator != NULL)
            return leftViolator;
        if (rightViolator != NULL)
            return rightViolator;
        
        
        
        /// swapping has been taken care of- just return null
        return NULL;
        
    }
    
};



/** ----------------------------------------------------------------------
 * Write a function to find the longest common prefix string amongst an array of strings. 
 * 
 --------------------------------------------------------------------- */

class LongestStringPrefix {
public:
    string longestCommonPrefix(vector<string> &strs) {
        string pre;

        if (strs.size() < 1)
            return pre;

        /// pick the first element to iterate over
        string first = strs[0];

        for (uint i = 0; i < first.size(); i++) {
            char preChar = first[i];
            
            /// iterate over all the other strings to compare
            for (uint j = 1; j < strs.size(); j++) {
                if (strs[j][i] != preChar)
                    return pre;
            }

            pre.push_back(preChar);
        }

        return pre;
        
    }
};



/** ----------------------------------------------------------------------
 *  Divide two integers without using multiplication, division and mod operator. 
 * 
 --------------------------------------------------------------------- */

class Divide {
public:
    int divide(int dividend, int divisor) {

        /// check if the result is negative
        bool isNegative = (dividend < 0) != (divisor < 0);

        dividend = abs(dividend);
        divisor = abs(divisor);
        
        
        int container = 0;
        int ctr = 0;

        while (container <= dividend) {
            container += divisor;
            ctr += 1;
        }

        int ret = ctr - 1;
        
        if (isNegative)
            ret = -1*ret;
        
        return ret;
        
    }
};


/** ----------------------------------------------------------------------
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following is not:

    1
   / \
  2   2
   \   \
   3    3

 * 
 --------------------------------------------------------------------- */

class TreeSymmetry {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == NULL)
            return true;
        
        return recursiveSymmetry(root->left, root->right);
    }
    
    bool recursiveSymmetry(TreeNode* left, TreeNode* right) {
        /// if both are null - its symmetric
        if (left == NULL && right == NULL)
            return true;

        /// if one of them is null - it broke symmetry
        if (left != NULL && right != NULL) {
            /// their values should be same as well
            bool sameVal = left->val == right->val;
            
            bool right_left = recursiveSymmetry(left->right, right->left);

            bool left_right = recursiveSymmetry(left->left, right->right);

            return sameVal && right_left && left_right;
            
        } else {
            return false;
        }
        
        

    }
    
};


/** ----------------------------------------------------------------------
 * Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

    Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
    The solution set must not contain duplicate triplets.

    For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)

 * 
 --------------------------------------------------------------------- */

class ThreeSum {
public:
    vector<vector<int> > threeSum(vector<int> &num) {

        vector< vector<int> > ret;

        if (num.size() < 3)
            return ret;
        
        /// sort the set of numbers first
        sort(num.begin(), num.end());

        /// convert this into a 2 sum problem with a pivot
        for (uint i = 0; i < num.size()-2; i++) {

            /// make sure this element is different from previous one
            if (i > 0) {
                if (num[i] == num[i-1])
                    continue;
            }
            
                
            
            int p = i+1;
            int q = num.size() - 1;

            int target = -num[i];

            while (p < q) {
                if(p!=i+1 && num[p]==num[p-1] ){        //num 2：only reserve first of all same values 
                    p++;
                    continue;
                }
                if (num[p] + num[q] == target) {
                    /// we have found a triplet
                    vector<int> triplet(3);
                    triplet[0] = num[i];
                    triplet[1] = num[p];
                    triplet[2] = num[q];
                    ret.push_back(triplet);
                    /// move both p and q
                    p++;
                    q--;
                } else if (num[p] + num[q] < target) {
                    p += 1;
                } else {
                    q -= 1;
                }
                
            }
        }
        
        return ret;
        
    }
};


/** ----------------------------------------------------------------------
 *  Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array A = [1,1,1,2,2,3],

Your function should return length = 5, and A is now [1,1,2,2,3]
 * 
 --------------------------------------------------------------------- */

class RemoveDuplicates2 {
public:
    int removeDuplicates(int A[], int n) {
        if (n <= 2)
            return n;
        
        int storeIdx = 1;

        int elem = A[0];
        int ctr = 1;
        
        /// iterate through array
        for (uint i = 1; i < n; i++) {
            if (A[i-1] == A[i]) {
                ctr += 1;
            } else {
                ctr = 1;
            }

            /// have we crossed limit?
            if (ctr > 2) {
                /// skip this element
            } else {
                /// place this element at storeIdx
                A[storeIdx] = A[i];
                storeIdx += 1;
            }
        }

        return storeIdx;
        
        
    }
};


/** ----------------------------------------------------------------------
 * Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
 * 
 --------------------------------------------------------------------- */

/**
 * Definition for a point.
 */
struct Point {
      int x;
      int y;
      Point() : x(0), y(0) {}
      Point(int a, int b) : x(a), y(b) {}
};

struct Coefficient {
    double m;
    double c;
    Coefficient(double a, double b) : m(a), c(b) 
    {
    }
    
};

    
class Solution {
public:
    int maxPoints(vector<Point> &points) {
        if (points.size() <= 0)
            return 0;
        
        /// instantiate a hash map to store line coefficients
        unordered_map< string, int > coefficients;

        int maxSoFar = 0;

        /// run a double loop through the points
        for (uint i = 0; i < points.size()-1; i++) {
            for (uint j = i+1; j < points.size(); j++) {
                /// get the coefficients for this line
                /// make sure the slope is not infinite
                string m;
                string c;
                
                if (points[j].x - points[i].x == 0) {
                    m = "inf";
                    c = to_string(points[j].y - points[i].y);
                } else {
                    double slope = (points[j].y - points[i].y)/(points[j].x - points[i].x);
                    m = to_string(slope);
                    c = to_string(points[j].y - (slope*points[j].x));
                }
                
                string coeff = "m " + m + " c " + c;
                
                int count = 2;
                
                /// check if this value exists in hash map
                if (coefficients.count(coeff) > 0) {
                    coefficients[coeff] += 1;
                    count = coefficients[coeff];
                    
                } else {
                    coefficients.insert(make_pair(coeff, count));
                }

                if (count > maxSoFar)
                    maxSoFar = count;
                
            }
        }
        return maxSoFar;
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


    Solution sln;

    vector<Point> pts(2);
    pts[0] = Point(0,0);
    pts[0] = Point(0,0);
    cout << sln.maxPoints(pts) << endl;
    
    
    /*
    vector<int> set(6);
    set[0] = -1;
    set[1] = 0;
    set[2] = 1;
    set[3] = 2;
    set[4] = -1;
    set[5] = -4;

    vector<vector<int> > ret = sln.threeSum(set);
    for (uint i = 0; i < ret.size(); i++) {
        for (uint j = 0; j < ret[i].size(); j++) {
            cout << ret[i][j] << "\t";
        }
        cout << endl;
    }
    
       std::cout << sln.divide(-6,-2) << std::endl;
      string inp = " ";

    std::cout << inp << std::endl;
    
    sln.reverseWords(inp);

    std::cout << inp << std::endl;
    
    string inp = "2178";
    
    vector<string> maps = sln.letterCombinations(inp);

    for (int i = 0; i < maps.size(); i++)
        std::cout << maps[i] << std::endl;
    
   /// ans should be 12 for this
      string s = "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco";

    std::cout << sln.lengthOfLongestSubstring(s) << std::endl;
    
      
    ListNode* l1 = new ListNode(5);
    ListNode* l2 = new ListNode(5);

    ListNode* sum = sln.addTwoNumbers(l1,l2);
    std::cout << "printing sum\n";
    
    while (sum != NULL) {
        std::cout << sum->val << "\t";
        sum = sum->next;
    }
    

    TreeNode*  root = new TreeNode(1);
    root->left = new TreeNode(5);
    std::cout << sln.isValidBST(root) << std::endl;
    

    sln.pathSum(root, 1);
    
    vector<vector<char> > board(3);

    for (int i = 0; i < board.size(); i ++) {
        board[i] = vector<char>(3, 'X');
    }

    board[1][1] = 'O';
    board[1][2] = 'O';

        for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            std::cout << board[i][j] << "\t";
        }
        std::cout << "\n";
    }

        
    sln.solve(board);

        for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            std::cout << board[i][j] << "\t";
        }
        std::cout << "\n";
    }

    vector<int> A(4);

    A[0] = 1;
    A[1] = 2;
    A[2] = 0;
    A[3] = 1;

    vector<int> B(1);

    B[0] =1;
    
    std::cout << sln.longestConsecutive(A) << std::endl;

    std::cout << sln.sqrt(1579205274) << std::endl;

    int A[4];

    A[0] = 0;
    A[1] = 4;
    A[2] = 0;
    A[3] = 2;
    
    std::cout << sln.canJump(A, 4) << std::endl;
    
        

    vector<vector<int> > combs =  sln.combine(5,2);

    for (int i = 0; i < combs.size(); i++) {
        for (int j = 0; j < combs[i].size(); j++)
            std::cout << combs[i][j] << ",";
        
                std::cout<<std::endl;   
    }
    
    string a = "11";
    string b = "1";

    std::cout << sln.addBinary(a, b) << std::endl;

    ;
    std::cout << sln.removeElement(A, 1, 3);
    

    std::cout << sln.trap(A, 4) << std::endl;    

    std::cout << sln.countAndSay(5) << std::endl;

    TreeNode* head = new TreeNode(2);
    head->right = new TreeNode(3);
     head->right->left = new TreeNode(9);
     head->right->right = new TreeNode(7);
     /// head->left = new TreeNode(4);
     /// head->left->left = new TreeNode(12);
    
    sln.flatten(head);

    TreeNode* ptr = head;
    
    while(ptr != NULL) {
        std::cout << ptr->val << "\t";
        ptr = ptr->right;
    }
    
    string s = "(())}";
    
    std::cout << sln.isValid(s) << std::endl;    
    std::cout << sln.isPalindrome(0) << std::endl;
    
    string h = "    ";
    std::cout << sln.lengthOfLastWord(h.c_str()) << std::endl;
    
    TreeNode* head = new TreeNode(2);
    head->right = new TreeNode(3);
    /// head->right->left = new TreeNode(9);
    /// head->right->right = new TreeNode(7);
    /// head->left = new TreeNode(4);
    std::cout << sln.minDepth(head) << std::endl;
    
    ListNode* list = new ListNode(1);

    sln.removeNthFromEnd(list,1);
   
    TreeNode* head = new TreeNode(2);
    head->right = new TreeNode(3);
    /// head->right->left = new TreeNode(9);
    /// head->right->right = new TreeNode(7);
    head->left = new TreeNode(4);
    /// std::cout << sln.sumNumbers(head) << std::endl;
    
    
    vector<vector<int> > comb = sln.combine(4, 2);
    for (int i = 0; i < comb.size(); i++) {
        for (int j = 0; j < comb[i].size(); j++) {
            std::cout << comb[i][j] << "\t";
        }
        std::cout << std::endl;
        
    }
    */
        
    
    /*
        /// print pascal triangle
        for (int k = 0; k < pascal.size(); k++)
            std::cout << pascal[k] << "\t";
        std::cout << std::endl;
   
    vector< vector<int> > nums;

    vector<int> per(3);
    per[0] = 1;
    per[1] = 2;
    per[2] = 3;

    /// nums = sln.permute(per);
    
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums[i].size(); j++)
            std::cout << nums[i][j] << "\t";
        
        std::cout << std::endl;
    }
    8/
    
    /// std::cout << sln.uniquePaths(23,12) << std::endl;
    
    
    vector<int> digits(1);

    digits[0] = 0;

    /// vector<int> res = sln.plusOne(digits);
    
    
    /// std::cout << sln.numTrees(4) << std::endl;
    



    /*
    int* A = new int[3];
    A[0] = 1;
    A[1] = 2;
    A[2] = 3;
    
    int* B = new int [3];
    B[0] = 2;
    B[1] = 5;
    B[2] = 6;

    int* C = new int[0];

    int* D = new int[1];
    D[0] = 1;
    
    /// sln.merge(C,0,D,1);
    /// sln.merge(A,3,B,3);
    
    */
    
    
    
    /*
    ListNode* head = new ListNode(5);
    ListNode* goon = head->next;
    goon = new ListNode(6);

    goon = goon->next;
    ListNode* cycle = goon;
    goon = new ListNode(7);
    goon = goon->next;
    goon = new ListNode(8);
    goon = goon->next;
    goon = new ListNode(9);
    /// cycle back
    goon->next = cycle;

    std::cout << sln.detectCycle(head) << std::endl;
    std::cout << cycle << std::endl;
    
   
    
    
    vector< vector<char> > board(3);
    for (int i = 0; i < board.size(); i++)
        board[i].resize(4);
    board[0][0] = 'A';
    board[0][1] = 'B';
    board[0][2] = 'C';
    board[0][3] = 'E';

    board[1][0] = 'S';
    board[1][1] = 'F';
    board[1][2] = 'E';
    board[1][3] = 'S';

    board[2][0] = 'A';
    board[2][1] = 'D';
    board[2][2] = 'E';
    board[2][3] = 'E';

    string word = "ABCESEEEFS";

    Board brd;
    
    /// std::cout << brd.exist(board, word) << std::endl;
    
    
    
    TreeNode* head = new TreeNode(2);
    head->right = new TreeNode(3);
    head->right->left = new TreeNode(9);
    head->right->right = new TreeNode(7);
    head->left = new TreeNode(21);
    
    std::cout << sln.maxPathSum(head) << std::endl;    

    string pal = "A man, a plan, a canal: Panama";
    string pal2 = " apG0i4maAs::sA0m4i0Gp0";
    
    std::cout << sln.isPalindrome(pal2) << std::endl;
    


    sln.postorderTraversal(head);

    
    ListNode* list = new ListNode(30);
    ListNode* head = list;
    
    for (int i = 0; i < 6; i++) {
        ListNode* node = new ListNode(6-i);
        list->next = node;
        list = node;
    }

    ListNode* sort = sln.sortList(head);

    /// ListNode* sort = head;
    
    while (sort != NULL) {
        std::cout << sort->val << std::endl;
        sort = sort->next;
    }
    */
    
    duration = (std::clock() - start)/static_cast<double>(CLOCKS_PER_SEC);
    std::cout<< "it took: "<< duration << "s" << std::endl;

    return 0;
}

