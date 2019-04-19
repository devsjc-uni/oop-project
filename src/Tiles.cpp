#include "Tiles.h"
#include <string>
#include <iostream>

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
            exit(1);
        }
    }
}

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
            exit(1);
        }
    }
}