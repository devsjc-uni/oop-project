// Tiles.cpp
// Defines member functions for tile class and derived classes
// Author: Sol Cotton

#include "Tiles.h"
#include <stdio.h>
#include <memory>

// default constructor
TileList::TileList() {
    std::cout << "Default TileLest constructor called" << std::endl;
    // initialise board with tiles in constructor
    for (int i = 0; i < (rowsize * columnsize); i++) {
        board.emplace_back(new Tile());
    }
}

// parameterised constructor
TileList::TileList(bool boxes) : TileList() {
    std::cout << "Parameterised constructor called" << std::endl;
    // call default constructor to create blank board
    if (boxes) {
        // loop over all positions in grid
        for (int y = 0; y < columnsize; y++) {
            for (int x = 0; x < rowsize; x++) {
                if (y % 2 == 0 && x % 2 == 0 && y != 0 && x != 0 && y != rowsize - 1 && x != rowsize - 1) {
                    // place boxes on odd squares, not including first and last row and column
                    auto box = std::make_shared<Box>();
                    board[y*rowsize + x] = box;
                }
            }
        }
    }
}

void TileList::printBoard() {
    // draw top of board
    std::cout << " ------------- \n";
    for (int y = 0; y < columnsize; y++) {
        // draw side of board for row y
        std::cout << "|";
        // then draw whatever tile objects exist in that row
        for (int x = 0; x < rowsize; x++) {
            board[y*(rowsize-1) + x]->draw();
        }
        // then draw last side of board
        std::cout << "|\n";
    }
    // draw bottom of board
    std::cout << " ------------- \n";
}