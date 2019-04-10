#include "Globals.h"
#include "Tiles.h"
#include "TileList.h"
#include "Dynamics.h"
#include <iostream>


int main() {

    TileList gameBoard(0);
    //gameBoard.printBoard();
    //gameBoard.printBoard();
    auto player1 = std::make_shared<Player>(1);
    gameBoard.addPlayer(player1);
    std::cout << player1->getX() << player1->getY() << std::endl;
    //gameBoard.printBoard();

    while (true) {
        char input = getValidInput();
        player1->move(input, gameBoard);
        std::cout << player1->getX() << player1->getY() << std::endl;
        //gameBoard.printBoard();
    }


}