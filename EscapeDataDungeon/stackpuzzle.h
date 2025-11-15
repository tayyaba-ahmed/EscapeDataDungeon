#ifndef STACKPUZZLE_H
#define STACKPUZZLE_H

#include "PuzzleBase.h"
#include <vector>
using namespace std;

class StackPuzzle : public PuzzleBase {
private:
    vector<int> data;  // Stores the stack elements for this puzzle

public:
    // Constructor
    // 'q' is the puzzle question
    // 'st' is the initial stack elements (bottom → top)
    StackPuzzle(const string& q, const vector<int>& st);

    // Getter
    // Returns the stack elements as a vector
    vector<int> getData() const;

    // Check Answer
    // Returns true if userAnswer matches the expected stack (top → bottom)
    bool checkAnswer(const string& userAnswer) override;
};

#endif 