// Dynamics.cpp
// Defines member functions from the header file Dynamics.h
// Author: Sol Cotton

#include "Dynamics.h"
#include "TileList.h"

void Player::move(char direction, TileList &playerBoard, std::shared_ptr<Tile> bombToPlant) {
    if (bombToPlant != nullptr && !isAwaitingPlant) {
        // the controller has sent a bomb to the move methods when the player was not awaiting a plant
        std::cout << "Cannot plant when already awaiting plant!\n";
        exit(1);
    }
    if(playerBoard.moveTile(getX(), getY(), direction, bombToPlant)) {
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
    }    
}

// parameterised constructor for player
Player::Player(int inPlayerNumber) {
    isAwaitingPlant = false;
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

// function to increase a players action count
bool Player::incrementActionCount() {
    if (actionCount < actionsInTurn) {
        actionCount += 1;
        return true;
    } else {
        // player's turn is over, return false
        return false;
    }
}
