// core/include/generator.h

#pragma once

#include <vector>

// Include tile class for type definition
#include "tile.h"

class Generator {
public:
    // Constructor
    Generator(int rows, int cols, Tile **grid, vector<int> startingPos) : rows(rows), cols(cols), grid(grid), startingPos(startingPos) {}

    int rows;
    int cols;
    Tile **grid;
    vector<int> startingPos;

    // Generate the Walls randomly
    // Needs to be public because Dungeon calls it
    void ProceduralGenerateWalls();

private:
    // Checks if every tile on the map is reachable
    // Can stay private as a helper function
    bool IsConnected();
};
