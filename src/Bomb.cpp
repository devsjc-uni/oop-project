#include "Bomb.h"
#include "TileList.h"

Bomb::Bomb(int inX, int inY, int inStrength, int inPower) {
    x = inX;
    y = inY;
    bombStrength = inStrength;
    bombPower = inPower;
    timer = 7; 
    exploded = false;
}

void Bomb::reduceTimer(TileList &playerBoard) {
    if (timer > 1) {
        timer -= 1;
    } else if (!exploded) {
        playerBoard.explodeBomb(x, y, bombStrength, bombPower);
        exploded = true;
    }
}
