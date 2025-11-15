#include "QueuePuzzle.h"
#include <vector>
#include <queue>
using namespace std;

// Constructor
// Initializes the QueuePuzzle with a question and initial queue data
// Stores data in a vector for reference
QueuePuzzle::QueuePuzzle(const string& q, const vector<int>& qd)
    : PuzzleBase(q), queueData(qd) {}

// Getter
// Returns the vector version of the queue data
vector<int> QueuePuzzle::getData() const {
    return queueData;
}

// Check Answer
// Checks if the user's answer matches the correct solution
// In this puzzle, the question asks: "What is the queue after one dequeue?"
bool QueuePuzzle::checkAnswer(const string& userAnswer) {
    // Create a new queue and push all elements from the vector
    queue<int> q;
    for (size_t i = 0; i < queueData.size(); i++) {
        q.push(queueData[i]);
    }

    // Dequeue (remove front element) to simulate one operation
    if (!q.empty()) q.pop();

    // Convert remaining queue elements to string for comparison
    string ans;
    while (!q.empty()) {
        ans += to_string(q.front()); // append front element
        q.pop();                     // remove it after reading
    }

    // Return true if user's answer matches the queue after dequeue
    return userAnswer == ans;
}
