// Globals.h
// Header file defining functions required globally
// Author: Sol Cotton

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

// define other external ints to be modified by options
extern int rowsize;
extern int columnsize;
extern int amountOfBoxes;
extern int totalActions;
extern int numActionsForSuddenDeath;
extern int bombDropPercentage;
extern std::string infoText;
extern std::string pickupText;
extern int numberOfDeadPlayers;
typedef enum SCREEN {TITLE, OPTIONS, GAME, PAUSE} SCREEN;
extern enum SCREEN screen;

// global functions 
void rangeCheck(int x, int y);
bool checkValidInput(std::string myInput, SCREEN thisScreen = GAME);
char getValidInput(SCREEN thisScreen = GAME);
void clearScreen();
int getIntBetweenPandQ(int p, int q);
// functions not required by everything, but included in global to reduce number of includes in main
void displayTitleScreen(int chosenScreen);
void optionsMenu();
void displayLoadingScreen();
void loadingScreen();
int getNumberOfPlayers();
void resetCounters();


#endif