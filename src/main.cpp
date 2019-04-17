#include "TileList.h"
#include "Controller.h"
#include "Globals.h"
#include <iostream>


int main() {

    while (true) {
        displayTitleScreen(0);
        char input = getValidInput(SCREEN::TITLE);
        while (input != 'N') {
            if (input == 'O') {
                optionsMenu();
            } else {
                // quit was selected
                displayTitleScreen(3);
                std::cout << "\n\n";
                for (int i = 0; i < 73; i++) {std::cout << "-";}
	            std::cout << "\nQUIT\n\n";
                std::cout << "Exiting. Thanks for playing!<\n";
                exit(0);
            }
            displayTitleScreen(0);
            input = getValidInput(SCREEN::TITLE);
        }
        int players = getNumberOfPlayers();
        TileList gameboard(1);
        Controller controller(gameboard);
        controller.createPlayers(players);
        loadingScreen();

        while (!controller.gameHasEnded()) {
            controller.performRound();
        }
    }

}
