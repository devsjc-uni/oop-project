#ifndef BOMB_H
#define BOMB_H

#include "TileList.h"
#include <iostream>

class Bomb : public StaticObject {
private:
    int timer;
    int strength;
    bool exploded;
public:
    // default constructor
    Bomb() {timer = 5; strength = 4; exploded = false;}
    // parameterised constructor
    Bomb(int inX, int inY, int inStrength);
    int getTimer() {return timer;}
    void reduceTimer(TileList &playerBoard);
    void explode(TileList &playerBoard);
    std::string getObjectType() {return "Bomb";}
    void draw() {std::cout << timer;}
    ~Bomb() {}
};

#endif