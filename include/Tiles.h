// Tiles.h
// Header file defining abstract base class:
    // Tile
// And classes derived from Tile:
    // Explosion
    // Box
    // Wall
    // PowerUp
// Author: Sol Cotton 08/04/19

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

class Explosion : public Tile {
public:
    // parameterised constructor
    Explosion(bool onBoxSquare) {destroyedBox = onBoxSquare;}
    std::string getObjectType() {return "Explosion";}
    void draw() {std::cout << "X";} //\u1F4A3 \u1F4A2 \u1F525
    ~Explosion() {}
};

// Static object derived class - Wall
class Wall : public Tile {
public:
    // constructor
    Wall() {isExploded = false;}
    // override Tile functions
    std::string getObjectType() {return "Wall";}
    void draw() {std::cout << "#";} // unicode "\u25A0"
    ~Wall() {};
};

// Tile derived class - Box
class Box : public Tile {
public:
    // constructor
    Box() {isExploded = false;}
    // override Tile functions
    std::string getObjectType() {return "Box";}
    void draw() {std::cout << "+";} // unicode "\u25A4"
    ~Box() {};
};

class PowerUp : public Tile {
public:
    enum powerUpType {STRENGTH, AGILITY, RANGE};
    // constructor
    PowerUp(powerUpType thisType) {type = thisType;}
    std::string getObjectType();
    void draw();
    ~PowerUp() {}
private:
    powerUpType type;
};

#endif