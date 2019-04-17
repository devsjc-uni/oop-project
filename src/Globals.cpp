// Globals.cpp
// Defines functions declared in globals.h
// Author: Sol Cotton
 
#include "Globals.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <thread>

int rowsize = 15;
int columnsize = 13;
int totalActions = 0;
std::string infoText = " Setting up...";
std::string pickupText = "\n";
int numberOfDeadPlayers = 0;


void rangeCheck(int x, int y) {
    if (x < 0 || x > rowsize - 1 || y < 0 || y > columnsize - 1) {
    std::cout << "Out of bounds error.\n";
    exit(1);
    }
}
std::string toUpper(std::string input){
	// uppercases all chars in input std::string
	for (auto& x : input)
		x = toupper(x);
	return input;
}

bool checkValidInput(std::string myInput, SCREEN thisScreen){
	bool isValid = false;
	// define a list of valid inputs
	std::vector<std::string> validInputs;
	switch(thisScreen) {
		case GAME : {
			validInputs.push_back("W");
			validInputs.push_back("A");
			validInputs.push_back("S");
			validInputs.push_back("D");
			validInputs.push_back("B");
			validInputs.push_back("X");
			validInputs.push_back("P");
		} case TITLE : {
			validInputs.push_back("N");
			validInputs.push_back("O");
		} case OPTIONS : {
			validInputs.push_back("Q");
			validInputs.push_back("R");
			validInputs.push_back("C");
			validInputs.push_back("T");
		} case PAUSE : {
			validInputs.push_back("C");
			validInputs.push_back("Q");
		}
	}
	
	for (unsigned i = 0; i < validInputs.size(); i++) {
		if (!myInput.compare(validInputs[i])) {
			// strings are equal
			isValid = true;
			break;
		}
	}
	return isValid;
}

char getValidInput(SCREEN thisScreen) {
	// uppercase everything for consistency
	std::string input;
    char character;
	
	while (!checkValidInput(input, thisScreen)){
		std::cin >> input;
		std::cin.ignore(100, '\n');
		input = toUpper(input);
	}
	character = input[0];
    return character;
}

// function to make printing 30 newlines look slightly less suspect elsewhere in code
void clearScreen() {
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

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
void displayTitleScreen(int chosenScreen) {
	clearScreen();
    for (int i = 0; i < 73; i++) {(!(i % 2)) ? std::cout << "\u25A0" : std::cout << " ";}
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
	auto underline = [](int distance, int length) {
		std::cout << "\u25A0" << std::setw(distance);
		for (int i = 0; i < length; i++) {
			std::cout << "\u25A4";
		}
		std::cout << std::setw(78-length-distance) << "\u25A0\n";
	};
	switch (chosenScreen) {
		case 1: {underline(11, 12); break;}
		case 2: {underline(34, 11); break;}
		case 3: {underline(55, 8); break;}
		case 0: {printBoxedNewLines(1); break;}
	}
    printBoxedNewLines(2);
    for (int i = 0; i < 73; i++) {(!(i % 2)) ? std::cout << "\u25A0" : std::cout << " ";}
    std::cout << std::endl;
}

// function for the options menu
void optionsMenu() {
	displayTitleScreen(2);
	std::cout << "\n\n";
    for (int i = 0; i < 73; i++) {std::cout << "-";}
	std::cout << "\nOPTIONS\n\n"
		 	  << "Enter your desired gameboard rowsize (standard 15): ";
	rowsize = getIntBetweenPandQ(5, 100);
	std::cout << "\nEnter your desired gameboard columnsize (standard 13): ";
	columnsize = getIntBetweenPandQ(5, 100);
	std::cout << "\nSaving changes...\n";
	using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
}

void displayLoadingScreen() {
	for (int i = 0; i < 73; i++) {std::cout << "-";}
	std::cout << "\nTIPS\n\n"
			  << "Perform an action by typing a letter followed by the ENTER key.\n"
			  << "Possible letters are:\n"
			  << "\t- W: Move up\n\t- A: Move left\n\t- S: Move down\n\t- D: Move right\n"
			  << "\t- B: Plant bomb\n\t- X: Skip action\n\t- P: Pause game\n"
			  << "\nBombs are an infinite resource, but once you've planted a bomb you must move off that square next action!"
			  << "\nThey have a timer of five actions and cannot penetrate through walls (\u25A0).\n"
			  << "\nPlant bombs to blow up boxes (\u25A4) in order to collect powerups and clear a path to your enemies."
			  << "Powerups include:\n"
			  << "\t- R: Range boost - increases the radius of your bomb's explosions\n"
			  << "\t- S: Strength boost - increases the number of boxes your bombs are able to penetrate through\n"
			  << "\t- A: Agility boost - increase the number of actions you can make per turn\n"
			  << "\nThe last player standing wins!"
			  << "\n\nCONTINUE [c]             QUIT [q]\n\nInput :";
}

void loadingScreen() {
	clearScreen();
    displayLoadingScreen();
    char input = getValidInput(SCREEN::PAUSE);
    if (input == 'Q') {
        clearScreen();
        std::cout << "Exiting. Thanks for playing!";
        exit(1);
    }
}

int getNumberOfPlayers() {
	displayTitleScreen(1);
	std::cout << "\n\n";
    for (int i = 0; i < 73; i++) {std::cout << "-";}
	std::cout << "\nNEW GAME\n\n";
    std::cout << "Enter number of players (2-4): ";
    int players = getIntBetweenPandQ(2, 4); 
	return players;
}