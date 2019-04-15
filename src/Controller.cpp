#include "Controller.h"

Controller::Controller(TileList &inPlayerBoard) {
    gameBoard = inPlayerBoard;
}

void Controller::createPlayers(int numPlayers) {
    if (numPlayers < 1 || numPlayers > 4) {
        std::cout << "Can only add one to four players!\n";
        exit(1);
    } else {
        for (int i = 0; i < numPlayers; i++) {
            playerPtrs.emplace_back(std::make_shared<Player>(i+1));
            gameBoard.setObject(playerPtrs[i]->getX(), playerPtrs[i]->getY(), playerPtrs[i]);
        } 
    }
}

void Controller::plantBomb() {
    std::shared_ptr<Bomb> lastBomb = bombPtrs[bombPtrs.size() - 1];
    gameBoard.setObject(lastBomb->getX(), lastBomb->getY(), lastBomb);
}

void Controller::playerAction(std::shared_ptr<Player> activePlayer) {
    char input = getValidInput();
    if (input == 'B') {
        activePlayer->setAwaitingPlant(true);
        bombPtrs.emplace_back(std::make_shared<Bomb>(activePlayer->getX(), activePlayer->getY(), 4));
    } else {
        if (activePlayer->getIsAwaitingPlant()) {activePlayer->move(input, gameBoard, bombPtrs[bombPtrs.size() - 1]);}
        else {activePlayer->move(input, gameBoard);} 
        activePlayer->setAwaitingPlant(false);
    }
}

void Controller::reduceTimers() {
    std::vector<std::shared_ptr<Bomb>>::iterator thisBomb;
    for(thisBomb = bombPtrs.begin(); thisBomb != bombPtrs.end(); thisBomb++) {
        (*thisBomb)->reduceTimer(gameBoard);
    }
}

void Controller::performRound() {
    std::vector<std::shared_ptr<Player>>::iterator thisPlayer;
    for (thisPlayer = playerPtrs.begin(); thisPlayer != playerPtrs.end(); thisPlayer++) {
        while ((*thisPlayer)->incrementActionCount()) {
            playerAction((*thisPlayer));
            reduceTimers();
            gameBoard.printBoard();
        }   
        (*thisPlayer)->resetActionCount();
    }
    std::cout << "Round Over\n";
}