#ifndef ARRAYPUZZLE_H
#define ARRAYPUZZLE_H

#include "PuzzleBase.h"
#include <vector>
using namespace std;

// ArrayPuzzle handles puzzles that use an integer array.
// It inherits from PuzzleBase.
class ArrayPuzzle : public PuzzleBase {
private:
    // Stores the array of integers used by this puzzle
    vector<int> data;

public:
    // Constructor that sets the puzzle question and its associated array
    ArrayPuzzle(const string& q, const vector<int>& arr);

    // Returns the stored integer array
    vector<int> getData() const;

    // Checks if the user's answer is correct (override from PuzzleBase)
    bool checkAnswer(const string& userAnswer) override;
};

#endif
