// Tiles.cpp
// Defines member functions for classes defined in Tiles.h:
    // Tile
    // TileList
// Author: Sol Cotton

#include "Tiles.h"
#include "Statics.h"
#include <iostream> // for cout
#include <memory>   // for shared_ptr
#include <random>   // for random

// define shared pointers to walls and boxes
auto wall = std::make_shared<Wall>();
auto box = std::make_shared<Box>();

// create a random generator using mersenne twister algorithm
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dist(1.0, 9.0);

bool TileList::onSpace(std::string spaceType, int x, int y) {
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
    // initialise board with tiles in constructor
    for (int i = 0; i < size(); i++) {
        board.emplace_back(new Tile());
    }
    // loop over all positions in grid
    boardLoop([this](int x, int y){
        if (onSpace("edge", x, y)) {
            setTile(x, y, wall);
        }
        if (onSpace("wall", x, y)) {
            setTile(x, y, wall);
        }
    });
}

// TileList parameterised constructor
TileList::TileList(bool boxes) : TileList() {
    // call default constructor to create blank board of walls
    if (boxes) {
        // loop over board
        boardLoop([this](int x, int y){
            if (getTile(x, y) != wall && !onSpace("start", x, y)) {
                // we are not on a wall or start space -> place a box
                if (dist(mt) < 7.5) setTile(x, y, box);
            }
        });
    }
}

void TileList::printBoard() {
    for (int y = 0; y < columnsize; y++) {
        // loop over each column
        for (int x = 0; x < rowsize; x++) {
            // then draw whatever tile objects exist in that row
            board[y*rowsize + x]->draw();
            // draw a space to fix ratio in terminal
            std::cout << " ";
        }
        std::cout << "\b\n";
    }
}