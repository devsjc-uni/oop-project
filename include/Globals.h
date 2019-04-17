// Globals.h
// Header file defining functions required globally
// Author: Sol Cotton

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

extern int rowsize;
extern int columnsize;
extern int totalActions;
extern std::string infoText;
extern std::string pickupText;
extern int numberOfDeadPlayers;
typedef enum SCREEN {TITLE, OPTIONS, GAME, PAUSE} SCREEN;
extern enum SCREEN screen;

void rangeCheck(int x, int y);
bool checkValidInput(std::string myInput, SCREEN thisScreen = GAME);
char getValidInput(SCREEN thisScreen = GAME);
void clearScreen();
int getIntBetweenPandQ(int p, int q);
void displayTitleScreen(int chosenScreen);
void optionsMenu();
void displayLoadingScreen();
void loadingScreen();
int getNumberOfPlayers();


#endif