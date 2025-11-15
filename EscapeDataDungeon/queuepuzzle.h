#ifndef QUEUEPUZZLE_H
#define QUEUEPUZZLE_H

#include "PuzzleBase.h"
#include <vector>
using namespace std;

class QueuePuzzle : public PuzzleBase {
private:
    vector<int> queueData;  // Stores the queue elements for the puzzle

public:
    // Constructor
    // Initializes the puzzle with a question and the initial queue data
    QueuePuzzle(const string& q, const vector<int>& qd);

    // Getter
    // Returns the queue data as a vector
    vector<int> getData() const;

    // Check Answer
    // Validates if the user's answer is correct
    bool checkAnswer(const string& userAnswer) override;
};

#endif
