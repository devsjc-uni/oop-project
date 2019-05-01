// Dynamics.h
// Defines DynamicObject derived class
// And classes derived from DynamicObject:
    // Player 
// Author: Sol Cotton 17/04/19

#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "TileList.h"

// Tile derived class - DynamicObject
class DynamicObject : public Tile {
public:
    // member function to change XY values only present in DynamicObjects
    void setXY(int inX, int inY) {rangeCheck(inX, inY); x = inX; y = inY;};
    // destructor
    virtual ~DynamicObject() {};
};

// DynamicObject derived class - Player
class Player : public DynamicObject {
private:
    bool isAwaitingPlant;
    int playerNumber;
    std::string playerName;
    int actionCount;
    int range;
    int strength;
    int agility;
public:
    // parameterised constructor
    Player(int playerNumber);
    // override Tile member functions
    std::string getObjectType() {return "Player";}
    void draw() {std::cout << getIcon();};
    // member functions
    void move(char direction, TileList &playerBoard, std::shared_ptr<Tile> bombToPlant = nullptr);
    void resetActionCount() {actionCount = 0;}
    bool incrementActionCount(); 
    void zeroAttributes();
    // getters and setters for player attributes
    int getStrength() const {return strength;}
    int getRange() const {return range;}
    int getAgility() const {return agility;}
    void setStrength(int inStrength) {strength = inStrength;}
    void setRange(int inRange) {range = inRange;}
    void setAgility(int inAgility) {agility = inAgility;}
    // getters and setters for other private data
    std::string getPlayerName() const {return playerName;}
    void setPlayerName(std::string inName) {playerName = inName;}
    std::string getIcon() const;
    void setAwaitingPlant(bool truth) {isAwaitingPlant = truth;}
    bool getIsAwaitingPlant() const {return isAwaitingPlant;} 
    int getPlayerNumber() const {return playerNumber;}
    int getActionCount() const {return actionCount;}
    // overload < operator to allow for vector sorting by name
    bool operator <(const Player& inPlayer) const {return (name < inPlayer.name);}
    //destructor
    ~Player() {};
};

#endif