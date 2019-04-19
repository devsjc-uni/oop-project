// TileList.cpp
// Defines member functions for classes defined in TileList.h:
    // TileList
// Author: Sol Cotton

#include "TileList.h"
#include <iostream> // for cout
#include <iomanip>
#include <memory>   // for shared_ptr
#include <thread>   // for sleep
#include <random>

// create a random generator using mersenne twister algorithm
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dist(1.0, 9.0);

bool TileList::onSpace(std::string spaceType, int x, int y) {
    rangeCheck(x, y);
    if (spaceType == "wall") {
        // return true if:
            // we are at least two spaces off the edge of the grid 
            // we are on an even tile
        return y % 2 == 0 && x % 2 == 0 && y > 1 && x > 1 && y < columnsize - 2 && x < rowsize - 2;
    } else if (spaceType == "start") {
        // return true if:
            // we are in one of four corner spaces
            // or adjacent spaces
        return ((y == 1 || y == columnsize - 2) && (x == 1 || x == 2 || x == rowsize - 3 || x == rowsize - 2)) 
            || ((y == 2 || y == columnsize - 3) && (x == 1 || x == rowsize - 2));
    } else if (spaceType == "edge") {
        // return true if we are on edge space
        return y == 0 || x == 0 || y == columnsize - 1 || x == rowsize - 1;
    } else {
        std::cout << "Incorrect input in onSpace bool!\n";
        exit(1);
    }
}

// TileList default constructor
TileList::TileList() {
    // initialise board
    for (int i = 0; i < size(); i++) {
        board.emplace_back(std::make_shared<Tile>());
    }
    // loop over all positions in grid
    boardLoop([this](int x, int y){
        if (onSpace("edge", x, y)) {
            setObject(x, y, std::make_shared<Wall>());
        }
        if (onSpace("wall", x, y)) {
            setObject(x, y, std::make_shared<Wall>());
        }
    });
}

// TileList parameterised constructor
TileList::TileList(int levelOfBoxes) : TileList() { 
    // call default constructor to create blank board of walls
    if (levelOfBoxes) {
        // loop over board
        boardLoop([=](int x, int y){
            if (getObject(x, y)->getObjectType() != "Wall" && !onSpace("start", x, y)) {
                // we are not on a wall or start space -> place a box
                float level;
                switch (levelOfBoxes) {
                    case 1: {level = 2.5; break;}
                    case 2: {level = 5.0; break;}
                    case 3: {level = 7.5; break;}
                    default: {std::cout << "Error! Incorrect level of boxes passed!"; exit(1);}
                }
                if (dist(mt) < level) setObject(x, y, std::make_shared<Box>());
            }
        });
    } 
}

// function to print populated board
void TileList::printBoard() {
    std::cout << infoText << std::endl;
    for (int y = 0; y < columnsize; y++) {
        // loop over each column, draw some initial space
        std::cout << " ";
        for (int x = 0; x < rowsize; x++) {
            // then draw whatever tile objects exist in that row
            this->getObject(x, y)->draw();
            // draw a space to fix ratio in terminal
            std::cout << " ";
        }
        std::cout << "\b\n";
    }
    if (totalActions > numActionsForSuddenDeath) {
        std::cout << " SUDDEN DEATH! WATCH YOUR STEP!\n Input: ";} 
    else { std::cout << "Total actions " << totalActions << "/" << numActionsForSuddenDeath <<"\n Input: ";}
}

// function that checks if a tile can be moved onto another tile
// returns an int according to whether it can or cannot move
int TileList::canMoveTile(int oldX, int oldY, char direction) {
    int canMoveCode = 0;
    // use a lambda function to get the appropriate return values
    auto getMoveCode = [] (std::string inString) {
        if (inString == "Tile") return 1;
        else if (inString == "Strength") return 2;
        else if (inString == "Range") return 3;
        else if (inString == "Agility") return 4;
        else return 0; 
    };
    switch(direction){
        case 'W': {
            // object wants to move up
            std::string spaceToBeMovedTo = getObject(oldX, oldY - 1)->getObjectType();
            canMoveCode = getMoveCode(spaceToBeMovedTo);
            break;
        } case 'D': {
            // object wants to move right
            std::string spaceToBeMovedTo = getObject(oldX + 1, oldY)->getObjectType();
            canMoveCode = getMoveCode(spaceToBeMovedTo);
            break;
        } case 'S': {
            // object wants to move down
            std::string spaceToBeMovedTo = getObject(oldX, oldY + 1)->getObjectType();
            canMoveCode = getMoveCode(spaceToBeMovedTo);
            break;
        } case 'A': {
            // object wants to move left
            std::string spaceToBeMovedTo = getObject(oldX - 1, oldY)->getObjectType();
            canMoveCode = getMoveCode(spaceToBeMovedTo);
            break;
        } default: {
            std::cout << "Incorrect movement argument passed\n";
            exit(1);
        }
    }
    return canMoveCode;
}
// function to move board objects around
void TileList::moveTile(int oldX, int oldY, char direction, std::shared_ptr<Tile> bombToPlant) {
    switch(direction){
        case 'W': {
            // object wants to move up
            setObject(oldX, oldY - 1, getObject(oldX, oldY));
            if (bombToPlant != nullptr) {setObject(oldX, oldY, bombToPlant);}
            else {setObject(oldX, oldY, std::make_shared<Tile>());}
            break;
        } case 'D': {
            // object wants to move right
            setObject(oldX + 1, oldY, getObject(oldX, oldY));
            if (bombToPlant != nullptr) {setObject(oldX, oldY, bombToPlant);}
            else {setObject(oldX, oldY, std::make_shared<Tile>());}
            break;
        } case 'S': {
            // object wants to move down
            setObject(oldX, oldY + 1, getObject(oldX, oldY));
            if (bombToPlant != nullptr) {setObject(oldX, oldY, bombToPlant);}
            else {setObject(oldX, oldY, std::make_shared<Tile>());}
            break;
        } case 'A': {
            // object wants to move left
            setObject(oldX - 1, oldY, getObject(oldX, oldY));
            if (bombToPlant != nullptr) {setObject(oldX, oldY, bombToPlant);}
            else {setObject(oldX, oldY, std::make_shared<Tile>());}
            break;
        } default: {
            std::cout << "Incorrect movement argument passed\n";
            exit(1);
        }
    }
}

// function to explode a bomb object found at x, y 
void TileList::explodeBomb(int x, int y, int bombStrength, int bombRange) {
    // check if bomb was under player
    if (getObject(x, y)->getObjectType() == "Player") {
        // if so, set player to killed
        getObject(x, y)->isExploded = true;
        infoText = "Player Killed!";
        numberOfDeadPlayers += 1;
    }
    // set bomb tile to explosion tile
    setObject(x, y, std::make_shared<Explosion>(false));
    // loop over all compass possible directions
    for (int direction = 0; direction < 4; direction++){
        int strengthLeft = bombStrength;
        for (int tileIterator = 1; tileIterator < bombRange; tileIterator++){
            // loop over all tiles in this direction up to bomb range
            std::string obstacle;
            int obstacleX, obstacleY;
            // set the encountered obstacle according to the direction
            switch (direction) {
                case 0: {
                    obstacleX = x; obstacleY = y - tileIterator;
                    obstacle = getObject(obstacleX, obstacleY)->getObjectType();
                    break;
                } case 1: {
                    obstacleX = x; obstacleY = y + tileIterator;
                    obstacle = getObject(obstacleX, obstacleY)->getObjectType();
                    break;
                } case 2: {
                    obstacleX = x - tileIterator; obstacleY = y;
                    obstacle = getObject(obstacleX, obstacleY)->getObjectType();
                    break;
                } case 3: {
                    obstacleX = x + tileIterator; obstacleY = y;
                    obstacle = getObject(obstacleX, obstacleY)->getObjectType();
                    break;
                }
            } 
            if (obstacle == "Wall") {
                // stop the propagating explosion in this direction
                break;
            } else if (obstacle == "Box") {
                // replace the box with an explosion tile
                setObject(obstacleX, obstacleY, std::make_shared<Explosion>(true));
                if (strengthLeft > 1) {
                    // if strength is not depleted, continue
                    strengthLeft -= 1;
                } else { 
                    // stop propagating explosion
                    break;
                }
            } else if (obstacle == "Player") {
                // delete the player object, set to explosion tile
                getObject(obstacleX, obstacleY)->isExploded = true;
                infoText = "Player Killed!";
                numberOfDeadPlayers += 1;
                setObject(obstacleX, obstacleY, std::make_shared<Explosion>(false));
            } else if (obstacle == "Bomb") {
                // stop the explosion
                break;
            } else {
                // set the tile to an explosion tile
                setObject(obstacleX, obstacleY, std::make_shared<Explosion>(false));
            }
        }
    }
    // print the explosion
    clearScreen();
    printBoard();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(0.25s);
    // then remove explosion tiles and reprint
    boardLoop([this](int x, int y){
        if (getObject(x, y)->getObjectType() == "Explosion") {
            if (getObject(x, y)->destroyedBox) {
                // explosion destroyed a box, drop loot
                float randomNum = dist(mt);
                if (randomNum < 1.5) setObject(x, y, std::make_shared<PowerUp>(PowerUp::STRENGTH));
                else if (randomNum < 3.8) setObject(x, y, std::make_shared<PowerUp>(PowerUp::RANGE));
                else if (randomNum < 5) setObject(x, y, std::make_shared<PowerUp>(PowerUp::AGILITY));
                else {setObject(x, y, std::make_shared<Tile>());}
            } else {
                setObject(x, y, std::make_shared<Tile>());
            }
        }
    });
    clearScreen();
    printBoard();
    
}
    

