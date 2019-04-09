// Tiles.h
// Header file defining abstract base class:
    // Tile
// Also defines wrapper for vector of Tiles (container):
    // TileList
// Author: Sol Cotton

#ifndef TILES_H
#define TILES_H

#include <iostream> // for cout
#include <vector>   // for vector
#include <memory>   // for shared_ptr
#include <string>   // for string

// Abstract Base Class - Tile
class Tile {
private:
protected:
    std::string name;
    int tileNumber;
    int x;
    int y;
public:
    virtual void draw() {std::cout << ' ';}
    // pure virtual functions
    virtual int getX() {return 0;}
    virtual int getY() {return 0;}
    virtual std::string getObjectType() {return "tile";};
    // destructor
    virtual ~Tile() {};
};

// Wrapper for gameboard container object
class TileList {
private:
    const int rowsize = 15;
    const int columnsize = 13;
public:
    typedef std::shared_ptr<Tile> TilePtr;
    std::vector<TilePtr> board;
    // default, parameterised constructor
    TileList();
    TileList(bool boxes);
    // member functions
    void printBoard();
    void setTile(int x, int y, TilePtr generalTile) {board[y*rowsize + x] = generalTile;} 
    int size() {return rowsize * columnsize;}
    bool onSpace(std::string spaceType, int x, int y);
    TilePtr getTile(int x, int y) {return board[y*rowsize + x];}
    TilePtr operator[] (const int index) {return board[index];}
    TilePtr operator() (const int x, const int y) {return board[y*rowsize + x];}
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