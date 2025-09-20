// core/include/generator.h

#pragma once

#include "tile.h"
#include <vector>

class Generator {
public:
    // Constructor
    Generator(int rows, int cols, Tile **grid, std::vector<int> startingPos);

    // The main public method to start generation
    void ProceduralGenerateWalls();

private:
    // Member variables to hold the context
    int rows;
    int cols;
    Tile **grid;
    std::vector<int> startingPos;

    // Helper function to check if the map is still fully connected
    bool IsConnected();
};
