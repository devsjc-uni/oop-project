// Menu.h
// Defines functions for displaying menu screens and getting input to navigate through them
// Author: Sol Cotton 22/04/19

#ifndef MENU_H
#define MENU_H

int getIntBetweenPandQ(int p, int q);
void displayTitleScreen(int chosenScreen);
void optionsMenu();
void displayLoadingScreen();
void loadingScreen();
int getNumberOfPlayers();
void resetCounters();

#endif