#include "GameEngine.h"
#include <queue>
#include <stack>
using namespace std;

// Constructor
// Initializes game state and loads all puzzles into roomQueue
GameEngine::GameEngine() : keyCollected(false) {

    // Stack for lives
    // Player starts with 3 lives stored in a stack
    // LIFO behavior: last added life is removed first when player makes mistakes
    for (int i = 0; i < 3; i++) lives.push(1);

    // Queue for rooms (FIFO)
    // Player solves puzzles in the same order they were added

    // Array puzzle
    roomQueue.push(new ArrayPuzzle(
        "Following array rotated right by 2 positions become?\n(no need for comma and square brackets)",
        vector<int>{4,6,1,3,7}));

    // Stack puzzle
    roomQueue.push(new StackPuzzle(
        "Given this stack, pop all elements and push them into a\nnew empty stack.\nWrite the final stack (top to bottom, no commas).",
        vector<int>{2,5,8}));

    // Queue puzzle
    roomQueue.push(new QueuePuzzle(
        "Perform Dequeue. What is the update queue?\n(no need for comma)",
        vector<int>{1,7,4,2}));

    // Min-heap puzzle
    HeapPuzzle* heapPuzzle = new HeapPuzzle(
        "After inserting 1 into the min-heap.\nWhat is the heap array level-order? (no need for comma)",
        vector<int>{3,6,4,2});
    heapPuzzle->convertToMinHeap();    // Convert the vector to a valid min-heap
    roomQueue.push(heapPuzzle);

    // BST puzzle
    roomQueue.push(new BSTPuzzle(
        "In-order successor of 5?",
        vector<int>{10,5,15,2,6,11,16}));

    // Linked list puzzle
    roomQueue.push(new LinkedListPuzzle(
        "If the linked list is reversed, what is the 2nd element?",
        vector<int>{7,8,9}));

    // Trap puzzle (secret code room)
    roomQueue.push(new TrapPuzzle("Enter the SECRET word:"));
}

// Destructor
// Cleans up all dynamically allocated puzzle objects
GameEngine::~GameEngine() {

    // Delete puzzles that still remain in roomQueue
    while (!roomQueue.empty()) {
        delete roomQueue.front();
        roomQueue.pop();
    }

    // Delete puzzles stored in completedRooms stack
    while (!completedRooms.empty()) {
        delete completedRooms.top();
        completedRooms.pop();
    }
}

// Returns pointer to the current puzzle
PuzzleBase* GameEngine::getCurrentPuzzle() {
    if (roomQueue.empty()) return nullptr;
    return roomQueue.front();
}

// Checks if the game is over (player has no lives left)
bool GameEngine::isGameOver() const {
    return lives.empty();
}

// Submit answer for the current puzzle
// Returns true if correct, false otherwise
bool GameEngine::submitAnswer(const string& answer) {
    if (roomQueue.empty()) return false;

    PuzzleBase* puzzle = roomQueue.front();
    bool correct = puzzle->checkAnswer(answer);

    if (!correct) {
        // Wrong answer → lose a life
        if (!lives.empty()) lives.pop();
    } 
    else {
        // Award special bonus life after finishing 3rd puzzle
        if (!keyCollected && completedRooms.size() == 2) {
            lives.push(1);
            keyCollected = true;
            emit keyCollectedSignal();   // Notify UI
        }

        // If TrapPuzzle, store secret code word
        if (TrapPuzzle* trap = dynamic_cast<TrapPuzzle*>(puzzle)) {
            codeWord = answer;
        }

        // Move puzzle from roomQueue to completedRooms stack
        completedRooms.push(puzzle);
        roomQueue.pop();
    }

    return correct;
}

// Skip or move to the next room (optional feature)
void GameEngine::moveToNextRoom() {
    if (!roomQueue.empty()) {
        completedRooms.push(roomQueue.front());
        roomQueue.pop();
    }
}

// Returns true if there are no more rooms left
bool GameEngine::isLastRoom() const {
    return roomQueue.empty();
}

// Returns number of remaining lives
int GameEngine::getHealth() const {
    return static_cast<int>(lives.size());
}

// Returns stored code word (TrapPuzzle)
string GameEngine::getCodeWord() const {
    return codeWord;
}

// Returns the index of the current room (count of completed rooms)
int GameEngine::getCurrentRoomIndex() const {
    return static_cast<int>(completedRooms.size());
}
