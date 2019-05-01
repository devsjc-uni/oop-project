// Controller.cpp
// Defines memeber functions initialised in Controller.h
// Author: Sol Cotton 16/04/19

#include "Controller.h"
#include "Globals.h"
#include "Menu.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iomanip>
#include <random>
#include <thread>
#include <chrono>

// parameterised constructor
Controller::Controller(TileList &inPlayerBoard, int numPlayers) {
    // initialise TileList object
    gameBoard = inPlayerBoard;
    // add players to vector
    if (numPlayers < 2 || numPlayers > 4) {
        // an unalowwable number of players has been chosen
        std::cout << "\nError: Can only add two to four players!\n";
        exit(0);
    } else {
        // an allowable number of players has been chosen
        for (int i = 0; i < numPlayers; i++) {
            playerPtrs.emplace_back(std::make_shared<Player>(i+1));
            // Get user input names for each player
            std::cout << "\n";
            switch(i) {
                case 0: {std::cout << "First player, enter your name (max 5 letters, no special characters): "; break;}
                case 1: {std::cout << "Second "; break;}
                case 2: {std::cout << "Third "; break;}
                case 3: {std::cout << "Fourth "; break;}
            }
            if (i != 0) std::cout << "player, enter your name: ";
            std::string name = getStringOfLength(5);
            playerPtrs[i]->setPlayerName(name);
            gameBoard.setObject(playerPtrs[i]->getX(), playerPtrs[i]->getY(), playerPtrs[i]);
        } 
    }
    // player 1 begins
    infoText = " " + (*this)(1)->getPlayerName() + " " + playerPtrs[0]->getIcon() + ", begin!";
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
                infoText = " Error: Cannot plant bomb whilst already awaiting plant! ";
            } else {
                // player's previous order was not to plant bomb
                activePlayer->setAwaitingPlant(true);
                bombPtrs.emplace_back(std::make_shared<Bomb>(activePlayer->getX(), activePlayer->getY(), activePlayer->getStrength(), activePlayer->getRange()));
                madeValidMovement = true;
            }
        } else if (input == 'X') {
            // player wants to skip action
            if (activePlayer->getIsAwaitingPlant()) {
                infoText = " Error: Cannot skip action whilst awaiting plant! ";
            } else {
                madeValidMovement = true;
            }
        } else if (input == 'P') {
            // player wants to pause
            menuscreen::pause();
        } else {
            // player wants to move
            int movementCode = gameBoard.canMoveTile(activePlayer->getX(), activePlayer->getY(), input);
            if (movementCode > 0) {
                // player is not trying to move into an obstacle
                if (activePlayer->getIsAwaitingPlant()) {
                    // player was awaiting a plant -> pass bomb object to move function
                    try {
                        activePlayer->move(input, gameBoard, bombPtrs[bombPtrs.size() - 1]);
                    } catch (const char* errorMessage) {
                        std::cerr << errorMessage;
                        exit(0);
                    }
                } else {
                    // player was not awaiting plant
                    activePlayer->move(input, gameBoard);
                } 
                activePlayer->setAwaitingPlant(false);
                madeValidMovement = true;
            }
        }
    }
    totalActions += 1;
}

// funtion that calls the reduce timer function on all bomb objects in activeBombs
void Controller::reduceTimers() {
    int numExplodedBombs = 0;
    for(auto thisBomb = bombPtrs.cbegin(); thisBomb != bombPtrs.cend(); thisBomb++) {
        (*thisBomb)->reduceTimer(gameBoard);
        if ((*thisBomb)->getExplodedState()) {numExplodedBombs += 1;}
    }
    for(int i = 0; i < numExplodedBombs; i++) {
        // delete the exploded bomb objects - will be the first elements in the deque
        bombPtrs.pop_front();
    }
}

// function to carry out a round of actions for each alive player
void Controller::performRound() {
    std::vector<std::shared_ptr<Player>>::iterator thisPlayer;
    for (thisPlayer = playerPtrs.begin(); thisPlayer != playerPtrs.end(); thisPlayer++) {
        if (!(*thisPlayer)->isExploded) {
            while ((*thisPlayer)->incrementActionCount()) {
                // first check whether we are in sudden death
                if (totalActions > numActionsForSuddenDeath) placeSuddenDeathBombs();
                playerAction((*thisPlayer));
                reduceTimers();
                if (gameHasEnded()) {break;}
                clearScreen();
                setInfo((*thisPlayer)->getPlayerNumber(), (*thisPlayer)->getActionCount());
            }
            (*thisPlayer)->resetActionCount();
        }
        if (gameHasEnded()) {
            clearScreen();
            // find the player who won
            int playerWhoWon;
            for (unsigned int i = 0; i < playerPtrs.size(); i++) {
                if (!playerPtrs[i]->isExploded) playerWhoWon = playerPtrs[i]->getPlayerNumber();
            }
            // cout who won
            std::cout << (*this)(playerWhoWon)->getPlayerName() << " wins!\n\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
            }
    }
}

// function to set the info text according to the gamestate
void Controller::setInfo(int PlayerNumber, int actionNumber) {
    std::stringstream setText;
    // sort the vector by who is doing best via a lambda function
    std::sort(playerPtrs.begin(), playerPtrs.end(), [](const std::shared_ptr<Player> p1, const std::shared_ptr<Player> p2) {
        return (p1->getAgility() + p1->getRange() + p1->getStrength() > p2->getAgility() + p2->getRange() + p2->getStrength());
    });
    // first print each player's attributes
    for (unsigned int i = 0; i < playerPtrs.size(); i++) {
        // draw a > infront of the currently active player
        (PlayerNumber == playerPtrs[i]->getPlayerNumber() && actionNumber < (*this)(PlayerNumber)->getAgility()) ? setText << ">" : setText << " "; 
        // denote the player number, their icon, their alive status, and their current attributes
        setText << playerPtrs[i]->getPlayerName() 
                << std::setw(7 - playerPtrs[i]->getPlayerName().length())
                << " " << playerPtrs[i]->getIcon();
        if (playerPtrs[i]->isExploded) {
            playerPtrs[i]->zeroAttributes();
            setText << ": --- \n";
        } else {
            setText << ": R(+" << playerPtrs[i]->getRange() - 1 << ")"
                    << " S(+" << playerPtrs[i]->getStrength() << ")"
                    << " A(+" << playerPtrs[i]->getAgility() << ")\n";
        }
    }
    // also add any powerup text
    setText << pickupText << std::endl;
    int actionsRemaining;
    try {
        // get the number of actions remaining
        actionsRemaining = (*this)(PlayerNumber)->getAgility() - actionNumber;
    } catch (const char* errorMessage) {
        std::cerr << errorMessage;
        exit(0);
    }
    // resort by player number
    // sort the vector by who is doing best via a lambda function - only modifies copy in this method
    std::sort(playerPtrs.begin(), playerPtrs.end(), [](const std::shared_ptr<Player> p1, const std::shared_ptr<Player> p2) {
        return (p1->getPlayerNumber() < p2->getPlayerNumber());
    });
    // text to print if a players turn is not over
    if (actionsRemaining != 0) {
        setText << " " << (*this)(PlayerNumber)->getPlayerName()
                  << ": " 
                  << actionsRemaining
                  << " Actions remaining";
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
        setText << " " << (*this)(nextPlayer)->getPlayerName() << "'s Turn";
    }
    infoText = setText.str();
}

// quick check to see if game has ended
bool Controller::gameHasEnded() {
    if (static_cast<unsigned int>(numberOfDeadPlayers) > playerPtrs.size() - 2) {
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
    else {throw "Error: Trying to access non existant player!\n";}
}

// create a random generator using mersenne twister algorithm
std::random_device rnd;
std::mt19937 alg(rnd());
std::uniform_real_distribution<float> getRand(0, 400);

// function to carry out sudden death mode
void Controller::placeSuddenDeathBombs() {
    // loop over the board
    gameBoard.boardLoop([this](int x, int y){
        if (gameBoard(x, y)->getObjectType() == "Tile") {
            // on each tile, plant a bomb with a certain probability
            if (getRand(alg) < bombDropPercentage) {
                // create a ptr to a bomb object and place on the board
                bombPtrs.emplace_back(std::make_shared<Bomb>(x, y, 1, 3));
                gameBoard.setObject(x, y, bombPtrs[bombPtrs.size() - 1]);
            }
        }
    });
}

// destructor
Controller::~Controller() {
    for (unsigned int i = 0; i < bombPtrs.size(); i++) {
        bombPtrs.pop_back();
    }
    for (unsigned int i = 0; i < playerPtrs.size(); i++) {
        playerPtrs.pop_back();
    }
}




