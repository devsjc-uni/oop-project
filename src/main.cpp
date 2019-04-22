#include "TileList.h"
#include "Controller.h"
#include "Globals.h"
#include "Menu.h"


int main() {

    while (true) {
        // reset external counters
        resetCounters();
        menuscreen::title(TITLECHOICE::NONE);
        char input = getValidInput(SCREEN::TITLE);
        switch(input) {
            case 'O': {menuscreen::options(); break;}
            case 'Q': {menuscreen::title(TITLECHOICE::QUIT); break;}
            case 'N': {
                // get the desired number of players
                int numberOfPlayers = getNumberOfPlayers();
                // initialise a board and the controller
                TileList gameboard(amountOfBoxes);
                Controller controller(gameboard, numberOfPlayers);
                // display pause screen for instructions
                menuscreen::pause();
                // perform rounds until game has ended
                while (!controller.gameHasEnded()) {
                    controller.performRound();
                }
                break;
            }
        }
    }
    
}
