#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "TileList.h"

// Tile derived class - DynamicObject
class DynamicObject : public Tile {
public:
    void setXY(int inX, int inY) {rangeCheck(inX, inY); x = inX; y = inY;};
    // destructor
    virtual ~DynamicObject() {};
};

// DynamicObject derived class - Player
class Player : public DynamicObject {
public:
    // default constructor
    Player() {x = 1; y = 1;}
    // parameterised constructor
    Player(int playerNumber);
    std::string getObjectType() {return "Player";}
    void move(char direction, TileList &playerBoard);
    void draw() {std::cout << "\u2687";} // \u26D1 \u267E
    ~Player() {};
};


#endif