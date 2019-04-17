#include "Controller.h"
#include "Globals.h"
#include <iomanip>
#include <sstream>
#include <iomanip>

Controller::Controller(TileList &inPlayerBoard) {
    gameBoard = inPlayerBoard;
}

// function to initilaise players in the vector of players
// pointers to these are then set on the board
void Controller::createPlayers(int numPlayers) {
    if (numPlayers < 2 || numPlayers > 4) {
        std::cout << "Can only add two to four players!\n";
        exit(1);
    } else {
        for (int i = 0; i < numPlayers; i++) {
            playerPtrs.emplace_back(std::make_shared<Player>(i+1));
            gameBoard.setObject(playerPtrs[i]->getX(), playerPtrs[i]->getY(), playerPtrs[i]);
        } 
    }
    infoText = " Player 1 \u2687, begin!";
}

// function that places a bomb in the activeBombs deque
void Controller::plantBomb() {
    std::shared_ptr<Bomb> lastBomb = bombPtrs[bombPtrs.size() - 1];
    gameBoard.setObject(lastBomb->getX(), lastBomb->getY(), lastBomb);
}

// function to get input and carry out a player action
void Controller::playerAction(std::shared_ptr<Player> activePlayer) {
    bool madeValidMovement = false;
    while (!madeValidMovement){
        clearScreen();
        gameBoard.printBoard();
        char input = getValidInput();
        if (input == 'B') {
            // player wants to plant bomb
            if (activePlayer->getIsAwaitingPlant()) {
                // player's previous order was to plant bomb
                infoText = "Error: Cannot plant bomb whilst already awaiting plant! ";
            } else {
                // player's previous order was not to plant bomb
                activePlayer->setAwaitingPlant(true);
                bombPtrs.emplace_back(std::make_shared<Bomb>(activePlayer->getX(), activePlayer->getY(), activePlayer->getStrength(), activePlayer->getRange()));
                madeValidMovement = true;
            }
        } else if (input == 'X') {
            // player wants to skip action
            if (activePlayer->getIsAwaitingPlant()) {
                infoText = "Error: Cannot skip action whilst awaiting plant! ";
            } else {
                madeValidMovement = true;
            }
        } else if (input == 'P') {
            // player wants to pause
            loadingScreen();
        } else {
            int movementCode = gameBoard.canMoveTile(activePlayer->getX(), activePlayer->getY(), input);
            if (movementCode > 0) {
                // player is not trying to move into an obstacle
                if (activePlayer->getIsAwaitingPlant()) {
                    // player was awaiting a plant -> pass bomb object to move function
                    activePlayer->move(input, gameBoard, bombPtrs[bombPtrs.size() - 1]);
                } else {
                    // player was not awaiting plant
                    activePlayer->move(input, gameBoard);
                } 
                activePlayer->setAwaitingPlant(false);
                madeValidMovement = true;
            }
        }
    }
}

// funtion that calls the reduce timer function on all bomb objects in activeBombs
void Controller::reduceTimers() {
    bool aBombHasExploded = false;
    for(auto thisBomb = bombPtrs.cbegin(); thisBomb != bombPtrs.cend(); thisBomb++) {
        (*thisBomb)->reduceTimer(gameBoard);
        if ((*thisBomb)->getExplodedState()) {aBombHasExploded = true;}
    }
    if (aBombHasExploded) {
        // delete the exploded bomb object - will be the first element in the deque
        bombPtrs.pop_front();
    }
}

// function to carry out a round of actions for each alive player
void Controller::performRound() {
    std::vector<std::shared_ptr<Player>>::iterator thisPlayer;
    for (thisPlayer = playerPtrs.begin(); thisPlayer != playerPtrs.end(); thisPlayer++) {
        if (!(*thisPlayer)->isExploded) {
            while ((*thisPlayer)->incrementActionCount()) {
                playerAction((*thisPlayer));
                reduceTimers();
                if (gameHasEnded()) {break;}
                clearScreen();
                setInfo((*thisPlayer)->getPlayerNumber(), (*thisPlayer)->getActionCount());
                //gameBoard.printBoard();
            }
            (*thisPlayer)->resetActionCount();
        }
        if (gameHasEnded()) {break;}
    }
}

// function to set the info text according to the gamestate
void Controller::setInfo(int PlayerNumber, int actionNumber) {
    std::stringstream setText;
    // first print each player's attributes
    for (unsigned int i = 0; i < playerPtrs.size(); i++) {
        (PlayerNumber == playerPtrs[i]->getPlayerNumber() && actionNumber != 0) ? setText << ">" : setText << " "; 
        setText << "Player " << playerPtrs[i]->getPlayerNumber()
                << " " << playerPtrs[i]->getIcon();
        if (playerPtrs[i]->isExploded) {setText << " --- \n";}
        else {
            setText << ": R(+" << playerPtrs[i]->getRange() << ")"
                    << " S(+" << playerPtrs[i]->getStrength() << ")"
                    << " A(+" << playerPtrs[i]->getAgility() << ")\n";
        }
    }
    setText << pickupText << std::endl;
    int actionsRemaining = (*this)(PlayerNumber)->getAgility() - actionNumber;
    // text to print if a players turn is not over
    if (actionsRemaining != 0) {
        setText << " Player " << PlayerNumber  
                  << " Actions remaining: " 
                  << actionsRemaining;
    } else {
        // otherwise find the next not dead player
        int nextPlayer = PlayerNumber;
        do {
            // first increment, then carry out is exploded check
            if (nextPlayer == playerPtrs.back()->getPlayerNumber()) {
                // current player is the last in playervector, set next player to player 1
                nextPlayer = 1;
            } else {
                // current player is not last in playervector
                nextPlayer += 1;
            }
        } while ((*this)(nextPlayer)->isExploded);
        setText << " Player " << nextPlayer << "'s Turn";
    }
    infoText = setText.str();
}

// quick check to see if game has ended
bool Controller::gameHasEnded() {
    if (static_cast<unsigned int>(numberOfDeadPlayers) == playerPtrs.size() - 1) {
        return true;
    } else {
        return false;
    }
}

// overload () operator to acces specific player
std::shared_ptr<Player> & Controller::operator()(int i) {
    bool playerFound = false;
    unsigned int elementNumber;
    for (elementNumber = 0; elementNumber < playerPtrs.size(); elementNumber++) {
        if (i == playerPtrs[elementNumber]->getPlayerNumber()) {
            playerFound = true;
            break;
        }
    }
    if (playerFound) return playerPtrs[elementNumber];
    else {
        std::cout << "Trying to access non existant player!\n";
        exit(1);
    }
}




