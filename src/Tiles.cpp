// Tiles.cpp
// Defines functions initialised in Tile.h
// For the PowerUp class
// Author: Sol Cotton 16/04/19

#include "Tiles.h"
#include <string>
#include <iostream>

// Function to return the object type of a powerup - depends on the powerup
std::string PowerUp::getObjectType() {
    switch (type) {
        case STRENGTH: {
            return "Strength";
            break;
        } case AGILITY: {
            return "Agility";
            break;
        } case RANGE: {
            return "Range";
        } default: {
            std::cout << "Invalid PowerUp Type!\n";
            exit(0);
        }
    }
}

// Override Tile draw function depending on powerup type
void PowerUp::draw() {
    switch (type) {
        case STRENGTH: {
            std::cout << "S";
            break;
        } case AGILITY: {
            std::cout << "A";
            break;
        } case RANGE: {
            std:: cout << "R";
            break;
        } default: {
            std::cout << "Invalid PowerUp Type!\n";
            exit(0);
        }
    }
}