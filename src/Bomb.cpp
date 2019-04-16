#include "Bomb.h"
#include "TileList.h"

Bomb::Bomb(int inX, int inY, int inStrength, int inPower) {
    x = inX;
    y = inY;
    bombStrength = inStrength;
    bombPower = inPower;
    timer = 7; 
    isExploded = false;
}

void Bomb::reduceTimer(TileList &playerBoard) {
    if (timer > 1) {
        timer -= 1;
    } else if (!isExploded) {
        playerBoard.explodeBomb(x, y, bombStrength, bombPower);
        isExploded = true;
    }
}
