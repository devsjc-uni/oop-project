// Menu.h
// Defines functions for displaying menu screens and getting input to navigate through them
// Author: Sol Cotton 22/04/19

#ifndef MENU_H
#define MENU_H

// functions required by menuscreen methods
int getIntBetweenPandQ(int p, int q);
int getNumberOfPlayers();
void resetCounters();
void displayPauseText();
enum TITLECHOICE {NONE, NEWGAME, OPTIONS, QUIT};

// menuscreen methods
namespace menuscreen {
    void title(TITLECHOICE choice);
    void options();
    void pause();
}


#endif