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
    // default constructor
    Controller(TileList &inPlayerBoard);

    // member functions
    void createPlayers(int numPlayers);

    void plantBomb();

    void playerAction(std::shared_ptr<Player> activePlayer);
    
    void reduceTimers();

    void performRound();

    void setInfo(int PlayerNumber, int actionNumber);

    bool gameHasEnded();

    std::shared_ptr<Player> & operator()(int i);

    ~Controller() {};


};

#endif

