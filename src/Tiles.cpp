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
        } case POWER: {
            return "Power";
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
        } case POWER: {
            std:: cout << "P";
            break;
        } default: {
            std::cout << "Invalid PowerUp Type!\n";
            exit(1);
        }
    }
}