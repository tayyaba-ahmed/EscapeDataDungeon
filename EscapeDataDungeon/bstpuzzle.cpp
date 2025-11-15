#include "BSTPuzzle.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Insert a value into BST 
// Recursively inserts 'val' into the BST rooted at 'root'
// Returns the root of the BST after insertion
BSTNode* BSTPuzzle::insertBST(BSTNode* root, int val) {
    if (root == nullptr) {
        // If tree is empty at this position, create a new node
        BSTNode* newNode = new BSTNode(val);
        return newNode;
    }

    // If value is smaller, insert into left subtree
    if (val < root->val) {
        root->left = insertBST(root->left, val);
    } 
    // Otherwise insert into right subtree
    else {
        root->right = insertBST(root->right, val);
    }

    // Return unchanged root pointer
    return root;
}

// In-order traversal
// Appends values of nodes in sorted (in-order) order
// Traversal: Left -> Node -> Right
void BSTPuzzle::inorderTraversal(BSTNode* root, vector<int>& result) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left, result);   // Visit left subtree
    result.push_back(root->val);            // Add current node's value
    inorderTraversal(root->right, result);  // Visit right subtree
}

// Find in-order successor 
// Finds the smallest value greater than 'val' in the BST
// Returns a pointer to the successor node, or nullptr if none exists
BSTNode* BSTPuzzle::inorderSuccessor(BSTNode* root, int val) {
    BSTNode* successor = nullptr;
    BSTNode* current = root;

    while (current != nullptr) {
        if (val < current->val) {
            // Potential successor found, move left to find smaller candidate
            successor = current;
            current = current->left;
        } else {
            // Move right to search for larger values
            current = current->right;
        }
    }

    return successor;
}

// BSTPuzzle Constructor
// Stores question and builds a BST from the given vector of integers
BSTPuzzle::BSTPuzzle(const string& q, const vector<int>& bst)
    : PuzzleBase(q), bstData(bst), root(nullptr) {

    // Build BST from provided values
    for (size_t i = 0; i < bstData.size(); i++) {
        root = insertBST(root, bstData[i]);
    }
}

// Getter for BST data 
// Returns a copy of the original input vector
vector<int> BSTPuzzle::getData() const {
    vector<int> copy;
    for (size_t i = 0; i < bstData.size(); i++) {
        copy.push_back(bstData[i]);
    }
    return copy;
}

// Check Answer 
// Compares user's answer with the in-order successor of 5
bool BSTPuzzle::checkAnswer(const string& userAnswer) {
    BSTNode* succ = inorderSuccessor(root, 5);  // Get successor of 5
    string succValue = to_string(succ->val);    // Convert to string
    return userAnswer == succValue;             // Check match
}
