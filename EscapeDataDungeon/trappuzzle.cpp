#include "TrapPuzzle.h"

// Constructor
// Initializes the TrapPuzzle with a question
// Unlike other puzzles, it doesn't store a data structure (like stack or array)
// The correct answer is hardcoded as the secret code word
TrapPuzzle::TrapPuzzle(const string& q)
    : PuzzleBase(q) {}

// Check Answer
// Compares the user's input with the secret code word
// Returns true if the input matches exactly, false otherwise
bool TrapPuzzle::checkAnswer(const string& userAnswer) {
    return userAnswer == "SECRET";
}
