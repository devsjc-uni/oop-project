// Dynamics.cpp
// Defines member functions from the header file Dynamics.h
// Author: Sol Cotton 16/04/19

#include "Dynamics.h"
#include "TileList.h"

// function that moves a player on a board "playerBoard", and increments player's x and y accordingly
// also increments players attributes
void Player::move(char direction, TileList &playerBoard, std::shared_ptr<Tile> bombToPlant) {
    if (bombToPlant != nullptr && !isAwaitingPlant) {
        // the controller has sent a bomb to the move methods when the player was not awaiting a plant
        throw "Error: Bomb passed when not awaiting plant!\n";
    }
    int movementCode = playerBoard.canMoveTile(getX(), getY(), direction);
    // get the movement code from the canMoveTile method, move the object
    playerBoard.moveTile(getX(), getY(), direction, bombToPlant);
    // change the player's xy values according to direction  
    switch (direction) {
        case 'A': {
            setXY(getX() - 1, getY());
            break;    
        }
        case 'D': {
            setXY(getX() + 1, getY());
            break;
        }
        case 'W': {
            setXY(getX(), getY() - 1);
            break;    
        }
        case 'S': {
            setXY(getX(), getY() + 1);
            break;
        }
    }
    // change the players attributes according to the movement code
    switch(movementCode) {
        case 2: {
            pickupText = " Strength Increased!";
            setStrength(getStrength() + 1);
            break;
        } case 3: {
            pickupText = " Range Increased!";
            setRange(getRange() + 1);
            break;
        } case 4: {
            pickupText = " Agility Increased!:";
            setAgility(getAgility() + 1);
            break;
        } default: {
            pickupText = " ";
        }
    }    
}

// parameterised constructor for player
Player::Player(int inPlayerNumber) {
    isExploded = false;
    isAwaitingPlant = false;
    range = 2;
    strength = 1;
    agility = 5;
    playerNumber = inPlayerNumber;
    actionCount = 0;
    if(playerNumber == 1) { x = 1; y = 1; }
    else if(playerNumber == 4) { x = rowsize - 2; y = 1; }
    else if(playerNumber == 3) { x = 1; y = columnsize - 2; }
    else if(playerNumber == 2) { x = rowsize - 2; y = columnsize - 2; }
    else {std::cout << "Playernumber too high\n"; exit(1);}
}

// draw function for player
void Player::draw() {
    switch(playerNumber) {
        case 1: {std::cout << "\u2687"; break;}
        case 2: {std::cout << "\u26D1"; break;}
        case 3: {std::cout << "\u267E"; break;}
        case 4: {std::cout << "\u263A"; break;}
    }
}

std::string Player::getIcon() const {
    switch(playerNumber) {
        case 1: {return "\u2687"; break;}
        case 2: {return "\u26D1"; break;}
        case 3: {return "\u267E"; break;}
        case 4: {return "\u263A"; break;}
        default: {
            std:: cout << "Error! Incorrect playerNumber";
            exit(1);
        }
    }
}

// function to increase a players action count
bool Player::incrementActionCount() {
    if (actionCount < agility) {
        actionCount += 1;
        return true;
    } else {
        // player's turn is over, return false
        return false;
    }
}
