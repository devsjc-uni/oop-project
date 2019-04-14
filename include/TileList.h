// TileList.h
// Defines wrapper for vector of Tiles (container):
    // TileList
// Author: Sol Cotton

#ifndef TILELIST_H
#define TILELIST_H

#include "Tiles.h"
#include "Globals.h"
#include <iostream> // for cout
#include <vector>   // for vector
#include <memory>   // for shared_ptr
#include <string>   // for string

// Wrapper for gameboard container object
class TileList {
public:
    typedef std::shared_ptr<Tile> TilePtr;
    std::vector<TilePtr> playerVector;
    std::vector<TilePtr> board;
    // default, parameterised constructor
    TileList();
    TileList(bool boxes);
    // member functions
    int size() {return rowsize * columnsize;}
    int getRowsize() {return rowsize;}
    int getColumnsize() {return columnsize;}
    void addPlayer(std::shared_ptr<Tile> player);
    void printBoard();
    void setObject(int x, int y, TilePtr generalTile) {rangeCheck(x, y); board[y*rowsize + x] = generalTile;} 
    void explodeBomb(int x, int y, int bombStrength);
    bool moveTile(int oldX, int oldY, char direction);
    bool onSpace(std::string spaceType, int x, int y);
    TilePtr getObject(int x, int y) {rangeCheck(x, y); return board[y*rowsize + x];}
    TilePtr operator[] (const int index) {return board[index];}
    TilePtr operator() (const int x, const int y) {rangeCheck(x, y); return board[y*rowsize + x];}
    // template function for performing nested loop 
    template<typename FUNCTION>
    inline void boardLoop(FUNCTION f) {
        for (int x = 0; x < rowsize; x++) {
            for (int y = 0; y < columnsize; y++){
                f(x, y);
            }
        }
    }
};


#endif
