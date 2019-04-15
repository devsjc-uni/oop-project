// Globals.h
// Header file defining functions required globally
// Author: Sol Cotton

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

extern const int rowsize;
extern const int columnsize;
extern const int actionsInTurn;

void rangeCheck(int x, int y);
bool checkValidInput(std::string myInput);
char getValidInput();


#endif