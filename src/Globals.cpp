// Globals.cpp
// Defines functions declared in globals.h
// Author: Sol Cotton 19/04/19
 
#include "Globals.h"
#include <iostream>
#include <vector>
#include <string>

// globally accessible variables
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

// function to check whether an input is valid for a given screen
bool checkValidInput(std::string myInput, SCREEN thisScreen){
	bool isValid = false;
	// define a list of valid inputs
	std::vector<std::string> validInputs;
	switch(thisScreen) {
		// push back the valid inputs for each screen case onto the vector
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
	// Lambda function to uppercase a string
	auto toUpper = [](std::string inString) {
		for (auto& x : inString) {x = toupper(x);}
		return inString;
	};
	// get input until it is valid
	while (!checkValidInput(input, thisScreen)){
		std::cin >> input;
		std::cin.ignore(100, '\n');
		input = toUpper(input);
	}
	character = input[0];
    return character;
}

// function to imporve clarity of printing several newlines elsewhere in code
void clearScreen() {
	for (int i = 0; i < 30; i++) {std::cout << std::endl;}
}

std::string getStringOfLength(int length) {
	auto validString = [length](const std::string& s) {
		int i = 0;
		for (const char c : s) {
			i += 1;
			if (!isalpha(c)) return false;
			if (i > length) return false;
		}
		return true;
	};
	// initialise an invalid string
	std::string input = "*";
	while (!validString(input)) {
		std::cin >> input;
		std::cin.ignore(100, '\n');
	}
	return input;
}

