// core/include/generator.h

#pragma once

#include <vector>

// Include tile class for type definition
#include "tile.h"

class Generator {
public:
    // Constructor
    Generator(int rows, int cols, Tile** grid, vector<int> startingPos) :
        rows(rows), cols(cols), grid(grid), startingPos(startingPos) {}

    int rows;
    int cols;
    Tile** grid;
    vector<int> startingPos;

private:
    // Generate the Walls randomly
    void ProceduralGenerateWalls();    

    // Checks if every tile on the map is reachable
    bool IsConnected();
};
