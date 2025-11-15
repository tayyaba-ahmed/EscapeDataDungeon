#include "HeapPuzzle.h"
#include <vector>
#include <string>
#include <algorithm> // for std::swap
using namespace std;

// Constructor
// Initializes the HeapPuzzle with a question and initial vector
// The input vector is stored as-is; no automatic min-heap conversion
HeapPuzzle::HeapPuzzle(const string& q, const vector<int>& h)
    : PuzzleBase(q), heapData(h) {
}

// Getter
// Returns a copy of the current heap data
vector<int> HeapPuzzle::getData() const {
    return heapData;
}

// Convert to Min-Heap
// Converts the vector into a valid min-heap using heapify-down
void HeapPuzzle::convertToMinHeap() {
    int n = heapData.size();
    // Start from last non-leaf node and heapify down
    for (int i = n / 2; i >= 0; i--) {
        heapifyDown(heapData, i, n);
    }
}

// Heapify Down
// Ensures the subtree rooted at 'index' satisfies min-heap property
void HeapPuzzle::heapifyDown(vector<int>& heap, int index, int n) {
    int smallest = index;        // Assume current node is smallest
    int left = 2 * index;        // Left child index
    int right = 2 * index + 1;   // Right child index

    // Compare with left child
    if (left < n && heap[left] < heap[smallest])
        smallest = left;

    // Compare with right child
    if (right < n && heap[right] < heap[smallest])
        smallest = right;

    // Swap and continue heapifying if needed
    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        heapifyDown(heap, smallest, n); // Recursive call
    }
}

// Check Answer
// Checks if user's answer matches heap after inserting '1'
bool HeapPuzzle::checkAnswer(const string& userAnswer) {
    vector<int> tempHeap = heapData; // Copy original heap

    int n = tempHeap.size();
    // Convert to valid min-heap
    for(int i = n/2; i >= 0; i--) {
        heapifyDown(tempHeap, i, n);
    }

    // Simulate insertion of value 1
    tempHeap.push_back(1);
    int i = tempHeap.size() - 1;

    // Heapify up to maintain min-heap property
    while (i > 0) {
        int parent = (i - 1) / 2;   // Parent index
        if (tempHeap[i] < tempHeap[parent]) {
            swap(tempHeap[i], tempHeap[parent]); // Swap if smaller
            i = parent; // Move up
        } else {
            break; // Heap property satisfied
        }
    }

    // Convert heap to concatenated string
    string ans = "";
    for (size_t i = 0; i < tempHeap.size(); i++) {
        ans += to_string(tempHeap[i]);
    }

    // Return true if user's answer matches simulated heap
    return userAnswer == ans;
}
