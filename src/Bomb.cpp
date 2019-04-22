// Bomb.cpp
//Defines member functions initialised in Bomb.h
    // Parameterised constructor
    // reduceTimer
// Author: Sol Cotton 14/04/19

#include "Bomb.h"
#include "TileList.h"

// Parameterised Constructor
Bomb::Bomb(int inX, int inY, int inStrength, int inRange) {
    x = inX;
    y = inY;
    bombStrength = inStrength;
    bombRange = inRange;
    timer = 7; 
    isExploded = false;
}

// reduceTimer
void Bomb::reduceTimer(TileList &playerBoard) {
    if (timer > 1) {
        timer -= 1;
    } else if (!isExploded) {
        playerBoard.explodeBomb(x, y, bombStrength, bombRange);
        isExploded = true;
    }
}
