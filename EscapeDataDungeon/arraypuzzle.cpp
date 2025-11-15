#include "ArrayPuzzle.h"
#include <string>
#include <vector>
#include <algorithm>

// Constructor
// Initializes an ArrayPuzzle with a question and an integer array.
// 'q' is the question string for this puzzle.
// 'arr' is the array data associated with this puzzle.
ArrayPuzzle::ArrayPuzzle(const string& q, const vector<int>& arr)
    : PuzzleBase(q), data(arr) {}  // Calls base class constructor and initializes 'data'

// Returns the array associated with this puzzle.
// Const method ensures the array is not modified accidentally.
vector<int> ArrayPuzzle::getData() const {
    return data;
}

// Checks if the user's answer matches the correct solution.
// Returns true if the answer is correct, false otherwise.
bool ArrayPuzzle::checkAnswer(const string& userAnswer) {
    // Step 1: Make a copy of the array to manipulate
    vector<int> rotated = data;

    // Step 2: Rotate the array right by 2 positions
    if (rotated.size() > 1) {
        rotate(rotated.rbegin(), rotated.rbegin() + 2, rotated.rend());
    }

    // Step 3: Convert rotated array to a string (without commas)
    string rotatedStr;
    for (int num : rotated) {
        rotatedStr += to_string(num);
    }

    // Step 4: Compare the generated string with the user's answer
    // If they match, return true; otherwise, return false
    return userAnswer == rotatedStr;
}
