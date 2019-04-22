// Controller.h
// Initialises the Controller class and its member functions
// Defines gameplay, member data include a TileList object for a board and containers for bombs and players
// Author: Sol Cotton 16/04/19

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Globals.h"
#include "Tiles.h"
#include "TileList.h"
#include "Dynamics.h"
#include "Bomb.h"
#include <vector>
#include <deque>
#include <memory>
#include <string>

class Controller {
private:
    TileList gameBoard;
    std::vector<std::shared_ptr<Player>> playerPtrs;
    std::deque<std::shared_ptr<Bomb>> bombPtrs;
public:
    // parameterised constructor
    Controller(TileList &inPlayerBoard, int numPlayers);
    // member functions
    void playerAction(std::shared_ptr<Player> activePlayer);
    void reduceTimers();
    void performRound();
    void setInfo(int PlayerNumber, int actionNumber);
    void placeSuddenDeathBombs();
    bool gameHasEnded();
    void displayTitleScreen();
    std::shared_ptr<Player> & operator()(int i);
    ~Controller();
};

#endif

