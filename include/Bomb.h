#ifndef BOMB_H
#define BOMB_H

#include "TileList.h"
#include <iostream>

class Bomb : public StaticObject {
private:
    int timer;
    int bombStrength;
    int bombPower;
public:
    // parameterised constructor
    Bomb(int inX, int inY, int inStrength, int inPower);
    int getTimer() {return timer;}
    void reduceTimer(TileList &playerBoard);
    void explode(TileList &playerBoard);
    bool getExplodedState() {return isExploded;}
    std::string getObjectType() {return "Bomb";}
    void draw() {std::cout << timer;}
    ~Bomb() {}
};

#endif