// Tiles.h
// Header file defining abstract base class:
    // Tile
// Also Defines StaticObject abstract derived class
// And classes derived from StaticObject:
    // Box
    // Wall
// Also defines DynamicObject abstract derived class
// And classes derived from DynamicObject:
    // Player
// Author: Sol Cotton

#ifndef TILES_H
#define TILES_H

#include "Globals.h"
#include <vector>
#include <iostream>
#include <string>
#include <iostream> // for cout
#include <vector>   // for vector
#include <memory>   // for shared_ptr
#include <string>   // for string

// Abstract Base Class - Tile
class Tile {
private:
protected:
    std::string name;
    int x;
    int y;
public:
    bool destroyedBox;
    bool isExploded;
    virtual void draw() {std::cout << ' ';}
    // pure virtual functions
    int getX() {return x;}
    int getY() {return y;}
    virtual std::string getObjectType() {return "Tile";};
    // destructor
    virtual ~Tile() {};
};

// Tile derived class - StaticObject
class StaticObject : public Tile {
public:
    // destructor
    virtual ~StaticObject() {};
};

class Explosion : public StaticObject {
public:
    // parameterised constructor
    Explosion(bool onBoxSquare) {destroyedBox = onBoxSquare;}
    std::string getObjectType() {return "Explosion";}
    void draw() {std::cout << "X";} //\u1F4A3 \u1F4A2 \u1F525
};

// Static object derived class - Wall
class Wall : public StaticObject {
public:
    // constructor
    Wall() {isExploded = false;}
    // overload Tile functions
    std::string getObjectType() {return "Wall";}
    void draw() {std::cout << "\u25A0";}
    ~Wall() {};
};

// StaticObject derived class - Box
class Box : public StaticObject {
public:
    // constructor
    Box() {isExploded = false;}
    // overload Tile functions
    std::string getObjectType() {return "Box";}
    void draw() {std::cout << "\u25A4";} // \u25A4
    ~Box() {};
};

class PowerUp : public StaticObject {
public:
    enum powerUpType {STRENGTH, AGILITY, POWER};
    // constructor
    PowerUp(powerUpType thisType) {type = thisType;}
    std::string getObjectType();
    void draw();
private:
    powerUpType type;
};

#endif