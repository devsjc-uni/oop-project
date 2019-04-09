#ifndef TILES_H
#define TILES_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>

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

class TileList {
private:
    const int rowsize = 13;
    const int columnsize = 11;
public:
    std::vector<std::shared_ptr<Tile>> board;
    // default, parameterised constructor
    TileList();
    TileList(bool boxes);
    // member functions
    void printBoard();
    std::shared_ptr<Tile> getTile(int x, int y) {return board[y*rowsize + x];}
    void setTile(int x, int y, std::shared_ptr<Tile> generalTile) {board[y*rowsize + x] = generalTile;} 
    int size() {return rowsize * columnsize;}
    std::shared_ptr<Tile> operator[] (const int index) {return board[index];}
    std::shared_ptr<Tile> operator() (const int x, const int y) {return board[y*rowsize + x];}
};
 

class StaticObject : public Tile {
private:
protected:
public:
    // destructor
    virtual ~StaticObject() {};
};

class Box : public StaticObject {
private:
protected:
public:
    // constructor
    Box() {}
    // overload Tile functions
    std::string getObjectType() {return "box";}
    void draw() {std::cout << "\u25A0";}
    ~Box() {};
};


#endif