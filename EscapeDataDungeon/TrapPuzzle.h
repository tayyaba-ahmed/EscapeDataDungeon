#ifndef TRAPPUZZLE_H
#define TRAPPUZZLE_H

#include "PuzzleBase.h"
#include <string>
using namespace std;

class TrapPuzzle : public PuzzleBase {
public:
    TrapPuzzle(const string& q);
    bool checkAnswer(const string& userAnswer) override;
};

#endif
