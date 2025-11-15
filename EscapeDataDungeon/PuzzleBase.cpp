#include "PuzzleBase.h"

// Constructor
// Initializes a puzzle with a given question string.
// 'q' is the question text for this puzzle.
PuzzleBase::PuzzleBase(const string& q)
    : question(q) {}

// Destructor
PuzzleBase::~PuzzleBase() {}

// Get Question
// Returns the question string associated with this puzzle.
// Const method because it does not modify the object.
string PuzzleBase::getQuestion() const {
    return question;
}
