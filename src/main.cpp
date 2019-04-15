#include "TileList.h"
#include "Controller.h"
#include <iostream>


int main() {

    TileList gameBoard(1);
    Controller controller(gameBoard);
    controller.createPlayers(2);
    gameBoard.printBoard();

    while (true) {
        controller.performRound();
    }

}