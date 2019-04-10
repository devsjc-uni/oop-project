// TileList.cpp
// Defines member functions for classes defined in TileList.h:
    // TileList
// Author: Sol Cotton

#include "TileList.h"
#include <iostream> // for cout
#include <memory>   // for shared_ptr
#include <random>   // for random

// create a random generator using mersenne twister algorithm
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dist(1.0, 9.0);

bool TileList::onSpace(std::string spaceType, int x, int y) {
    rangeCheck(x, y);
    if (spaceType == "wall") {
        // return true if:
            // we are at least two spaces off the edge of the grid 
            // we are on an even tile
        return y % 2 == 0 && x % 2 == 0 && y > 1 && x > 1 && y < columnsize - 2 && x < rowsize - 2;
    } else if (spaceType == "start") {
        // return true if:
            // we are in one of four corner spaces
            // or adjacent spaces
        return ((y == 1 || y == columnsize - 2) && (x == 1 || x == 2 || x == rowsize - 3 || x == rowsize - 2)) 
            || ((y == 2 || y == columnsize - 3) && (x == 1 || x == rowsize - 2));
    } else if (spaceType == "edge") {
        // return true if we are on edge space
        return y == 0 || x == 0 || y == columnsize - 1 || x == rowsize - 1;
    } else {
        std::cout << "Incorrect input in onSpace bool!\n";
        exit(1);
    }
}

// TileList default constructor
TileList::TileList() {
    // initialise board
    for (int i = 0; i < size(); i++) {
        board.emplace_back(std::make_shared<Tile>());
    }
    // loop over all positions in grid
    boardLoop([this](int x, int y){
        if (onSpace("edge", x, y)) {
            setObject(x, y, std::make_shared<Wall>());
        }
        if (onSpace("wall", x, y)) {
            setObject(x, y, std::make_shared<Wall>());
        }
    });
}

// TileList parameterised constructor
TileList::TileList(bool boxes) : TileList() {
    // call default constructor to create blank board of walls
    if (boxes) {
        // loop over board
        boardLoop([this](int x, int y){
            if (getObject(x, y)->getObjectType() != "Wall" && !onSpace("start", x, y)) {
                // we are not on a wall or start space -> place a box
                if (dist(mt) < 7.5) setObject(x, y, std::make_shared<Box>());
            }
        });
    } 
}

// function to print populated board
void TileList::printBoard() {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    for (int y = 0; y < columnsize; y++) {
        // loop over each column
        for (int x = 0; x < rowsize; x++) {
            // then draw whatever tile objects exist in that row
            this->getObject(x, y)->draw();
            // draw a space to fix ratio in terminal
            std::cout << " ";
        }
        std::cout << "\b\n";
    }
}

// function to move board objects around
bool TileList::moveTile(int oldX, int oldY, char direction) {
    bool moved = false;
    switch(direction){
        case 'W': {
            // object wants to move up
            if (getObject(oldX, oldY - 1)->getObjectType() == "Tile") {
                // space is free, move object
                setObject(oldX, oldY - 1, getObject(oldX, oldY));
                setObject(oldX, oldY, std::make_shared<Tile>());
                moved = true;
            }
            break;
        } case 'D': {
            // object wants to move right
            if (getObject(oldX + 1, oldY)->getObjectType() == "Tile") {
                // space is free, move object
                setObject(oldX + 1, oldY, getObject(oldX, oldY));
                setObject(oldX, oldY, std::make_shared<Tile>());
                moved = true;
            }
            break;
        } case 'S': {
            // object wants to move down
            if (getObject(oldX, oldY + 1)->getObjectType() == "Tile") {
                // space is free, move object
                setObject(oldX, oldY + 1, getObject(oldX, oldY));
                setObject(oldX, oldY, std::make_shared<Tile>());
                moved = true;
            }
            break;
        } case 'A': {
            // object wants to move left
            if (getObject(oldX - 1, oldY)->getObjectType() == "Tile") {
                // space is free, move object
                setObject(oldX - 1, oldY, getObject(oldX, oldY));
                setObject(oldX, oldY, std::make_shared<Tile>());
                moved = true;
            }
            break;
        } default: {
            std::cout << "Incorrect movement argument passed\n";
            exit(1);
        }
    }
    std::cout << moved<<std::endl;
    return moved;
}

void TileList::addPlayer(std::shared_ptr<Tile> player) {
    if (playerVector.size() > 3) {
        std::cout << "Cannot add more than four players!\n";
        exit(1);
    } else { 
        playerVector.push_back(player); 
        if (playerVector.size() > 0) {
            for (unsigned i = 0; i < playerVector.size(); i++) {
                setObject(playerVector[i]->getX(), playerVector[i]->getY(), playerVector[i]);
            }
        }
    }
}