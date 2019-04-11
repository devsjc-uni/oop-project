#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Dynamics.h"
#include "TileList.h"


class Controller {
private:
    std::vector<Player> players;
public:
    void makeAction();

};

#endif