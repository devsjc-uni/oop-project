// Menu.cpp
// Defines functions initialised in Menu.h header file used for displaying menu screens
// Author: Sol Cotton 22/04/19

#include "Menu.h"
#include "Globals.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <thread>

int getIntBetweenPandQ(int p, int q){
    // Returns validated integer between p and q
    int result = 0;
    bool validated = false;
    while (!validated) {
        std::string line;
        getline(std::cin, line);
        std::istringstream is(line);
        char dummy = '\0'; 
        // if we fail to extract an int
        // or we find something apart from whitespace after the int
        // or the value isn't in range
        if   (!(is >> result)
             || (is >> std::ws && is.get(dummy))
             || (result < p) || (result > q))
             { std::cout << "Input must be an valid integer. Try again!\n"; }
        else { validated = true; }
    }
    return result;
}

// function to print out the title screen
void menuscreen::title(TITLECHOICE choice) {
	clearScreen();
    for (int i = 0; i < 73; i++) {(!(i % 2)) ? std::cout << "\u25A0" : std::cout << " ";}
    // Lambda function for printing lines beginning and ending with a box
    auto printBoxedNewLines = [](int num) {
        for (int i = 0; i < num; i++) {std::cout << "\u25A0" << std::setw(75) << "\u25A0\n";}
    };
    std::cout << std::endl;
    printBoxedNewLines(2);
    std::cout << "\u25A0         Welcome to Sol Cottons marvellous turn-based game of          \u25A0\n"
              << "\u25A0      ____                  _                                          \u25A0\n"                              
              << "\u25A0     | __ )  ___  _ __ ___ | |__   ___ _ __ _ __ ___   __ _ _ __       \u25A0\n" 
              << "\u25A0     |  _ \\ / _ \\| '_ ` _ \\| '_ \\ / _ \\ '__| '_ ` _ \\ / _` | '_ \\      \u25A0\n"
              << "\u25A0     | |_) | (_) | | | | | | |_) |  __/ |  | | | | | | (_| | | | |     \u25A0\n"
              << "\u25A0     |____/ \\___/|_| |_| |_|_.__/ \\___|_|  |_| |_| |_|\\__,_|_| |_|     \u25A0\n";
	
    printBoxedNewLines(3);
    std::cout << "\u25A0" << std::setw(20) << "NEW GAME [n]" << std::setw(22) 
			  << "OPTIONS [o]" << std::setw(19)  << "QUIT [q]" << std::setw(14) << "\u25A0\n";
    // Lambda function to draw an underline at a certain point in the line
	auto underline = [](int distance, int length) {
		std::cout << "\u25A0" << std::setw(distance);
		for (int i = 0; i < length; i++) {
			std::cout << "\u25A4";
		}
		std::cout << std::setw(78-length-distance) << "\u25A0\n";
	};
    // Underline a different menu option depending on which was chosen
	switch (choice) {
		case TITLECHOICE::NEWGAME: {underline(11, 12); break;}
		case TITLECHOICE::OPTIONS: {underline(34, 11); break;}
		case TITLECHOICE::QUIT: {underline(56, 8); break;}
		case TITLECHOICE::NONE: {printBoxedNewLines(1); break;}
	}
    printBoxedNewLines(2);
    for (int i = 0; i < 73; i++) {(!(i % 2)) ? std::cout << "\u25A0" : std::cout << " ";}
    std::cout << std::endl;
	if (choice == TITLECHOICE::QUIT) {
		std::cout << "\n\n";
		for (int i = 0; i < 73; i++) {std::cout << "-";}
		std::cout << "\nQUIT\n\n";
		std::cout << "Exiting. Thanks for playing!<\n";
        exit(0);
	}
}

// function for the options menu
void menuscreen::options() {
	menuscreen::title(TITLECHOICE::OPTIONS);
	std::cout << "\n\n";
    for (int i = 0; i < 73; i++) {std::cout << "-";}
	std::cout << "\nOPTIONS\n\n"
		 	  << "1/5: Enter your desired gameboard rowsize (5-100, standard 15): ";
	rowsize = getIntBetweenPandQ(5, 100);
	std::cout << "\n2/5: Enter your desired gameboard columnsize (5-100, standard 13): ";
	columnsize = getIntBetweenPandQ(5, 100);
	std::cout << "\n3/5: Choose the amount of boxes to be spawned (standard HIGH)\n"
			  << "NONE [0]\t LOW [1]\t MEDIUM [2]\t HIGH [3]: ";
	amountOfBoxes = getIntBetweenPandQ(0, 3);
	std::cout << "\n4/5: Enter the number of actions before sudden death (0-500, standard 150): ";
	numActionsForSuddenDeath = getIntBetweenPandQ(0, 500);
	std::cout << "\n5/5: Enter the likelihood of a bomb drop per square per action during sudden death (0-10, standard 2): ";
	bombDropPercentage = getIntBetweenPandQ(0, 10);

	std::cout << "\nSaving changes...\n";
    // Mimic long save time to reasure player 
	using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);

}

// Function to display the pause screen text
void displayPauseText() {
	for (int i = 0; i < 73; i++) {std::cout << "-";}
	std::cout << "\nPAUSE\n\n"
			  << "Perform an action by typing a letter followed by the ENTER key.\n"
			  << "Possible letters are:\n"
			  << "\t- W: Move up\n\t- A: Move left\n\t- S: Move down\n\t- D: Move right\n"
			  << "\t- B: Plant bomb\n\t- X: Skip action\n\t- P: Pause game\n"
			  << "\nBombs are an infinite resource, but once you've planted a bomb you must move off that square next action!"
			  << "\nThey have a timer of five actions and cannot penetrate through walls (\u25A0).\n"
			  << "\nPlant bombs to blow up boxes (\u25A4) in order to collect powerups and clear a path to your enemies."
			  << "\nPowerups include:\n"
			  << "\t- R: Range boost - increases the radius of your bomb's explosions\n"
			  << "\t- S: Strength boost - increases the number of boxes your bombs are able to penetrate through\n"
			  << "\t- A: Agility boost - increase the number of actions you can make per turn\n"
			  << "\nThe last player standing wins!"
			  << "\n\nCONTINUE [c]             QUIT [q]\n\nInput :";
}

// Function to implement navigation with the loading screen
void menuscreen::pause() {
	clearScreen();
    displayPauseText();
    char input = getValidInput(SCREEN::PAUSE);
    if (input == 'Q') {
        clearScreen();
        std::cout << "Exiting. Thanks for playing!";
        exit(0);
    }
}

// Function to return the number of players
int getNumberOfPlayers() {
	menuscreen::title(TITLECHOICE::NEWGAME);
	std::cout << "\n\n";
    for (int i = 0; i < 73; i++) {std::cout << "-";}
	std::cout << "\nNEW GAME\n\n";
    std::cout << "Enter number of players (2-4): ";
    int players = getIntBetweenPandQ(2, 4); 
	return players;
}

// Function to reset the number of counters
void resetCounters() {
	totalActions = 0;
	numberOfDeadPlayers = 0;
}