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

class Bomb;

// DynamicObject derived class - Player
class Player : public DynamicObject {
private:
    bool isAwaitingPlant;
    int playerNumber;
    int actionCount;
    int power;
    int strength;
    int agility;
public:
    // parameterised constructor
    Player(int playerNumber);
    std::string getObjectType() {return "Player";}
    void move(char direction, TileList &playerBoard, std::shared_ptr<Tile> bombToPlant = nullptr);
    void draw();
    void setAwaitingPlant(bool truth) {isAwaitingPlant = truth;}
    bool getIsAwaitingPlant() {return isAwaitingPlant;} 
    int getPlayerNumber() {return playerNumber;}
    int getActionCount() {return actionCount;}
    bool incrementActionCount(); 
    void resetActionCount() {actionCount = 0;}
    int getStrength() {return strength;}
    int getPower() {return power;}
    int getAgility() {return agility;}
    int setStrength(int inStrength) {strength = inStrength;}
    int setPower(int inPower) {power = inPower;}
    int setAgility(int inAgility) {agility = inAgility;}
    ~Player() {};
};


#endif