#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "PuzzleBase.h"
#include "ArrayPuzzle.h"
#include "StackPuzzle.h"
#include "QueuePuzzle.h"
#include "HeapPuzzle.h"
#include "LinkedListPuzzle.h"
#include "BSTPuzzle.h"
#include "TrapPuzzle.h"
#include <queue>
#include <stack>
#include <string>
#include <QObject>

using namespace std;

// GameEngine manages game flow, puzzles, lives, and progress
class GameEngine : public QObject {
    Q_OBJECT  // Required for Qt signals and slots

private:
    queue<PuzzleBase*> roomQueue;        // Queue of upcoming rooms (FIFO)
    stack<PuzzleBase*> completedRooms;   // Stack of completed rooms (LIFO)
    stack<int> lives;                    // Player lives stored as a stack
    bool keyCollected;                   // Tracks if bonus key life was awarded
    string codeWord;                     // Stores secret word from TrapPuzzle

public:
    // Constructor loads puzzles and initializes game state
    GameEngine();

    // Destructor cleans up all dynamically allocated puzzles
    ~GameEngine();

    // Returns number of completed rooms (used as current room index)
    int getCurrentRoomIndex() const;

    // Returns pointer to the current puzzle
    PuzzleBase* getCurrentPuzzle();

    // Checks answer and updates lives & puzzle progress
    bool submitAnswer(const string& answer);

    // Optional skip to move to next puzzle
    void moveToNextRoom();

    // Returns true if player has no lives left
    bool isGameOver() const;

    // Returns true if all rooms are solved
    bool isLastRoom() const;

    // Returns number of lives remaining
    int getHealth() const;

    // Returns stored secret code word from TrapPuzzle
    string getCodeWord() const;

signals:
    // Signal emitted when bonus key is collected
    void keyCollectedSignal();
};

#endif
