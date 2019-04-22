// Globals.cpp
// Defines functions declared in globals.h
// Author: Sol Cotton 19/04/19
 
#include "Globals.h"
#include <iostream>
#include <vector>
#include <string>

int rowsize = 15;
int columnsize = 13;
int amountOfBoxes = 3;
int totalActions = 0;
int numActionsForSuddenDeath = 150;
int bombDropPercentage = 2;
std::string infoText = " Setting up...";
std::string pickupText = "\n";
int numberOfDeadPlayers = 0;

// function to check whether inputted xy values are in range
void rangeCheck(int x, int y) {
    if (x < 0 || x > rowsize - 1 || y < 0 || y > columnsize - 1) {
    std::cout << "Error: Out of bounds on board.\n";
    exit(1);
    }
}

// function to return an uppercased string
std::string toUpper(std::string input){
	// uppercases all chars in input std::string
	for (auto& x : input)
		x = toupper(x);
	return input;
}

// function to check whether an input is valid for a given screen
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
			validInputs.push_back("Q");
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
	// check over the whole valid inputs vector and compare
	for (unsigned i = 0; i < validInputs.size(); i++) {
		if (!myInput.compare(validInputs[i])) {
			// strings are equal
			isValid = true;
			break;
		}
	}
	return isValid;
}

// function to get valid input for a given screen
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

