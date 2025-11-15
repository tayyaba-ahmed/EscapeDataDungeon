#ifndef LINKEDLISTPUZZLE_H
#define LINKEDLISTPUZZLE_H

#include "PuzzleBase.h"
#include <vector>
#include <list>
using namespace std;

// LinkedListPuzzle represents a puzzle based on a linked list
class LinkedListPuzzle : public PuzzleBase {
private:
    vector<int> listData; // Stores original data in a vector for easy access
    list<int> llData;     // Stores data in a std::list for linked list operations

public:
    // Constructor initializes the puzzle question and list data
    LinkedListPuzzle(const string& q, const vector<int>& l);

    // Returns a copy of the original data vector
    vector<int> getData() const;

    // Checks if user's answer is correct (override from PuzzleBase)
    bool checkAnswer(const string& userAnswer) override;
};

#endif
