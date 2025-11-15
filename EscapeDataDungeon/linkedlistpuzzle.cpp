#include "LinkedListPuzzle.h"
#include <list>
using namespace std;

// Constructor
// Initializes the LinkedListPuzzle with a question and initial data
// Stores data in both vector (easy access) and std::list (for linked list operations)
LinkedListPuzzle::LinkedListPuzzle(const string& q, const vector<int>& l)
    : PuzzleBase(q), listData(l) {
    // Populate the linked list (std::list) with the vector elements
    for (int val : listData) {
        llData.push_back(val);
    }
}

// Getter
// Returns a copy of the vector containing the linked list data
vector<int> LinkedListPuzzle::getData() const {
    return listData;
}

// Check Answer
// Checks if user's answer matches the 2nd element after reversing the list
bool LinkedListPuzzle::checkAnswer(const string& userAnswer) {
    // Copy the linked list to reverse it
    list<int> reversedList = llData;
    reversedList.reverse();

    // Move iterator to the second element
    auto i = reversedList.begin();
    ++i;
    int second = *i;

    // Convert to string for comparison
    string ans = to_string(second);

    // Return true if user's answer matches
    return userAnswer == ans;
}
