#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Tiles.h"
#include <string>
#include <iostream>

class Explosion : public Tile {
public:
    std::string getObjectType() {return "Explosion";}
    void draw() {std::cout << "X";} //\u1F4A3 \u1F4A2 \u1F525
};

#endif