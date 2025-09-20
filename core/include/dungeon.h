// core/include/dungeon.h

#pragma once

#include "player.h"
#include "tile.h"
#include <vector>

class Dungeon {
public:
    Dungeon(int rows, int cols, std::vector<int> startingPos);
    ~Dungeon(); // Destructor for cleanup

    void Initialize();
    bool MovePlayer(const std::vector<int> &movement);
    void Print() const;

private:
    void CreateDungeon();
    void InitDungeon();
    void InitPlayer();

    int rows;
    int cols;
    Tile **grid;
    Player *player;
    std::vector<int> startingPos;
};
