// Statics.h
// Defines StaticObject abstract derived class
// And classes derived from StaticObject:
    // Box
    // Wall
// Author: Sol Cotton

#ifndef STATICS_H
#define STATICS_H

#include "Tiles.h"

// Tile derived class - StaticObject
class StaticObject : public Tile {
private:
protected:
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
    std::string getObjectType() {return "box";}
    void draw() {std::cout << "\u25A4";} // \u25A4
    ~Box() {};
};

#endif