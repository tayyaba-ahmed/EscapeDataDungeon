#ifndef HEAPPUZZLE_H
#define HEAPPUZZLE_H

#include "PuzzleBase.h"
#include <vector>
#include <algorithm>
using namespace std;

// HeapPuzzle represents a puzzle based on a min-heap
class HeapPuzzle : public PuzzleBase {
private:
    vector<int> heapData;  // Stores the heap elements

public:
    // Constructor initializes the puzzle question and heap vector
    HeapPuzzle(const string& q, const vector<int>& h);

    // Returns a copy of the current heap data
    vector<int> getData() const;

    // Checks if user's answer is correct
    bool checkAnswer(const string& userAnswer) override;

    // Converts the stored vector into a valid min-heap
    void convertToMinHeap();

    // Heapify down from the given index to maintain min-heap property
    void heapifyDown(vector<int>& heap, int index, int n);
};

#endif
