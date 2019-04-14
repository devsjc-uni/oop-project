#include "Globals.h"
#include "Tiles.h"
#include "TileList.h"
#include "Dynamics.h"
#include "Bomb.h"
#include <iostream>


int main() {

    TileList gameBoard(1);
    auto player1 = std::make_shared<Player>(1);
    auto bomb1 = std::make_shared<Bomb>(rowsize - 2, 1, 4);
    gameBoard.setObject(rowsize - 2, 1, bomb1);
    gameBoard.addPlayer(player1);
    gameBoard.printBoard();

    while (true) {
        char input = getValidInput();
        player1->move(input, gameBoard);
        bomb1->reduceTimer(gameBoard);
        gameBoard.printBoard();
    }
}
