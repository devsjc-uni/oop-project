// Dynamics.cpp
// Defines member functions from the header file Dynamics.h
// Author: Sol Cotton

#include "Dynamics.h"

void Player::move(char direction, TileList &playerBoard) {
    if(playerBoard.moveTile(getX(), getY(), direction)) {
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
Player::Player(int playerNumber) {
    if(playerNumber == 1) { x = 1; y = 1; }
    else if(playerNumber == 4) { x = rowsize - 2; y = 1; }
    else if(playerNumber == 3) { x = 1; y = columnsize - 2; }
    else if(playerNumber == 2) { x = rowsize - 2; y = columnsize - 2; }
    else {std::cout << "Playernumber too high\n"; exit(1);}
}
