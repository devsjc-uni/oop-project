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

// Abstract Base Class - Tile
class Tile {
private:
protected:
    std::string name;
    int x;
    int y;
public:
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

// Static object derived class - Wall
class Wall : public StaticObject {
public:
    // constructor
    Wall() {}
    // overload Tile functions
    std::string getObjectType() {return "Wall";}
    void draw() {std::cout << "\u25A0";}
    ~Wall() {};
};

// StaticObjet derived class - Box
class Box : public StaticObject {
public:
    // constructor
    Box() {}
    // overload Tile functions
    std::string getObjectType() {return "Box";}
    void draw() {std::cout << "\u25A4";} // \u25A4
    ~Box() {};
};


#endif