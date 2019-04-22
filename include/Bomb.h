// Bomb.h
// Initialises Bomb class (Derived from Tile) and its member functions
// Author: Sol Cotton 22/04/19


#ifndef BOMB_H
#define BOMB_H

#include "TileList.h"
#include <iostream>

class Bomb : public Tile {
private:
    int timer;
    int bombStrength;
    int bombRange;
public:
    // parameterised constructor
    Bomb(int inX, int inY, int inStrength, int inRange);
    // member functions
    int getTimer() {return timer;}
    void reduceTimer(TileList &playerBoard);
    void explode(TileList &playerBoard);
    bool getExplodedState() {return isExploded;}
    std::string getObjectType() {return "Bomb";}
    void draw() {std::cout << timer;}
    ~Bomb() {}
};

#endif