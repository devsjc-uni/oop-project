// Globals.cpp
// Defines functions declared in globals.h
// Author: Sol Cotton
 
#include "Globals.h"
#include <iostream>
#include <stdio.h>

const int rowsize = 15;
const int columnsize = 13;

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

char getValidInput() {
	// returns true on validated "a" input, false on "b" input
	// uppercase everything for consistency
	std::string input;
    char character;
	while (input.compare("W") && input.compare("A") && input.compare("S") && input.compare("D")){
		std::cout << "\r";
		std::cin >> input;
		std::cin.ignore(100, '\n');
		input = toUpper(input);
	}
	character = input[0];
    return character;
}
