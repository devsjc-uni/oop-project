// Globals.cpp
// Defines functions declared in globals.h
// Author: Sol Cotton
 
#include "Globals.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

const int rowsize = 15;
const int columnsize = 13;
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

bool checkValidInput(std::string myInput){
	bool isValid = false;
	// define a list of valid inputs
	std::vector<std::string> validInputs;
	validInputs.push_back("W");
	validInputs.push_back("A");
	validInputs.push_back("S");
	validInputs.push_back("D");
	validInputs.push_back("B");
	validInputs.push_back("X");
	for (unsigned i = 0; i < validInputs.size(); i++) {
		if (!myInput.compare(validInputs[i])) {
			// strings are equal
			isValid = true;
			break;
		}
	}
	return isValid;
}

char getValidInput() {
	// uppercase everything for consistency
	std::string input;
    char character;
	
	while (!checkValidInput(input)){
		std::cin >> input;
		std::cin.ignore(100, '\n');
		input = toUpper(input);
	}
	character = input[0];
    return character;
}

void clearScreen() {
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}