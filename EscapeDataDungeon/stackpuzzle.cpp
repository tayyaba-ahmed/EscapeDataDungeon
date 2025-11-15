#include "StackPuzzle.h"
#include <stack>
using namespace std;

// Constructor
// Initializes the StackPuzzle with a question and stack data
// Stores elements in a vector for reference
StackPuzzle::StackPuzzle(const string& q, const vector<int>& st)
    : PuzzleBase(q), data(st) {}

// Getter
// Returns the vector version of the stack data
vector<int> StackPuzzle::getData() const {
    return data;
}

// Check Answer
// Checks if the user's answer matches the correct solution
bool StackPuzzle::checkAnswer(const string& userAnswer) {
    // Step 1: Push all elements into a stack 's' (top = last element of vector)
    stack<int> s, newStack;
    for (size_t i = 0; i < data.size(); i++) {
        s.push(data[i]);
    }

    // Step 2: Reverse the stack by pushing elements from 's' to 'newStack'
    while (!s.empty()) {
        newStack.push(s.top());
        s.pop();
    }

    // Step 3: Convert final stack to string (top → bottom)
    string ans;
    while (!newStack.empty()) {
        ans += to_string(newStack.top());
        newStack.pop();
    }

    // Step 4: Compare with user input (numbers without separators)
    return userAnswer == ans;
}
