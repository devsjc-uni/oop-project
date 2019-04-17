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
private:
    bool isAwaitingPlant;
    int playerNumber;
    int actionCount;
    int range;
    int strength;
    int agility;
public:
    // parameterised constructor
    Player(int playerNumber);
    std::string getObjectType() {return "Player";}
    void move(char direction, TileList &playerBoard, std::shared_ptr<Tile> bombToPlant = nullptr);
    void draw();
    std::string getIcon() const;
    void setAwaitingPlant(bool truth) {isAwaitingPlant = truth;}
    bool getIsAwaitingPlant() const {return isAwaitingPlant;} 
    int getPlayerNumber() const {return playerNumber;}
    int getActionCount() const {return actionCount;}
    bool incrementActionCount(); 
    void resetActionCount() {actionCount = 0;}
    int getStrength() const {return strength;}
    int getRange() const {return range;}
    int getAgility() const {return agility;}
    void setStrength(int inStrength) {strength = inStrength;}
    void setRange(int inRange) {range = inRange;}
    void setAgility(int inAgility) {agility = inAgility;}
    ~Player() {};
};


#endif