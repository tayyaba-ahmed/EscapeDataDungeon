#ifndef PUZZLEBASE_H
#define PUZZLEBASE_H

#include <string>
using namespace std;

class PuzzleBase {
protected:
    string question; // Stores the puzzle question

public:
    // Constructor
    // Initializes the puzzle with the given question string
    PuzzleBase(const string& q);

    // Virtual destructor
    virtual ~PuzzleBase();

    // Returns the puzzle question
    string getQuestion() const;

    // Pure virtual function to check the user's answer
    // Must be implemented by derived classes
    virtual bool checkAnswer(const string& userAnswer) = 0;
};

#endif
