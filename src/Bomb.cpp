#include "Bomb.h"
#include "TileList.h"

Bomb::Bomb(int inX, int inY, int inStrength) {
    x = inX;
    y = inY;
    strength = inStrength;
    timer = 5; 
    exploded = false;
}

void Bomb::reduceTimer(TileList &playerBoard) {
    if (timer > 1) {
        timer -= 1;
    } else if (!exploded) {
        playerBoard.explodeBomb(x, y, strength);
        exploded = true;
    }
}
