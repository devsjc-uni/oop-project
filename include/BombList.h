/*#ifndef BOMBLIST_H
#define BOMBLIST_H

#include "TileList.h"
#include "Bomb.h"
#include <vector>
#include <memory>

class BombList {
public:
    typedef std::shared_ptr<Bomb> BombPtr;
    std::vector<BombPtr> activeBombs;
    BombList() {}
    void addBomb(int inX, int inY, int inStrength);
    void removeBombs();
    void reduceTimers(TileList &inPlayerBoard);
    ~BombList();
};

#endif
*/