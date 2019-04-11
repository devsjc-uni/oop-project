#include "Globals.h"
#include "Tiles.h"
#include "TileList.h"
#include "Dynamics.h"
#include <iostream>


int main() {

    TileList gameBoard(1);
    //gameBoard.printBoard();
    //gameBoard.printBoard();
    //auto player1 = std::make_shared<Player>(2);
    //gameBoard.addPlayer(player1);
    //std::cout << player1->getX() << " " << player1->getY() << std::endl;
    //gameBoard.printBoard();

    gameBoard.printBoard();
    auto player1 = std::make_shared<Player>(1);
    auto player2 = std::make_shared<Player>(2);
    gameBoard.addPlayer(player1);
    gameBoard.addPlayer(player2);
    gameBoard.printBoard();
    
    while (true){
        for (int  i = 0; i < 100; i++) {
            char input = getValidInput();
            player1->move(input, gameBoard);
            gameBoard.printBoard();
            input = getValidInput();
            player2->move(input, gameBoard);
            gameBoard.printBoard();
        }
    }


}