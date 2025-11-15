#ifndef BSTPUZZLE_H
#define BSTPUZZLE_H

#include "PuzzleBase.h"
#include <vector>
#include <string>
using namespace std;

// Node structure for the Binary Search Tree
struct BSTNode {
    int val;              // Value stored in this node
    BSTNode* left;        // Pointer to left child
    BSTNode* right;       // Pointer to right child

    // Node constructor
    BSTNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// BSTPuzzle works with a Binary Search Tree puzzle
class BSTPuzzle : public PuzzleBase {
private:
    vector<int> bstData;   // Stores the original list of values
    BSTNode* root;         // Pointer to the root of the BST

    // Inserts a value into the BST
    BSTNode* insertBST(BSTNode* root, int val);

    // Performs in-order traversal and fills a vector
    void inorderTraversal(BSTNode* root, vector<int>& result);

    // Finds the in-order successor of a given value
    BSTNode* inorderSuccessor(BSTNode* root, int val);

public:
    // Constructor initializes question and builds the BST
    BSTPuzzle(const string& q, const vector<int>& bst);

    // Returns a copy of the original vector
    vector<int> getData() const;

    // Checks if the user's answer is correct
    bool checkAnswer(const string& userAnswer) override;
};

#endif
