#include "TileList.h"
#include "Controller.h"
#include <iostream>


int main() {

    TileList gameBoard(1);
    Controller controller(gameBoard);
    controller.createPlayers(3);

    while (!controller.gameHasEnded()) {
        controller.performRound();
    }

}
