// core/src/generator.cpp

// Import .h file
#include <generator.h>

// Include random for random numbers
#include <random>
#include <queue>

#include <iostream>

using namespace std;

void Generator::ProceduralGenerateWalls() {
    // A modern C++ random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> wallTypeDist(0, 2); // 0=H-Line, 1=V-Line, 2=Square
    uniform_int_distribution<> lengthDist(1, 5);
    uniform_int_distribution<> squareDist(2, 3);
    uniform_int_distribution<> rowDist(0, rows - 1);
    uniform_int_distribution<> colDist(0, cols - 1);

    const int numberOfWallsToTry = 50; // How many wall pieces we attempt to place

    for (int i = 0; i < numberOfWallsToTry; ++i) {
        // 1. Decide on a random wall shape and position
        vector<vector<int>> newWall;
        int r = rowDist(gen);
        int c = colDist(gen);

        // (Code to generate the coordinates for a line or square goes here)
        // ... let's pretend 'newWall' is now full of {row, col} pairs ...

        // 2. Check if the placement is valid (in-bounds and not overlapping)
        bool canPlace = true;
        for (const auto& pos : newWall) {
            if (pos[0] < 0 || pos[0] >= rows || pos[1] < 0 || pos[1] >= cols || grid[pos[0]][pos[1]].type != ' ') {
                canPlace = false;
                break;
            }
        }

        if (!canPlace) continue; // Try again with a new random wall

        // 3. Temporarily place the wall
        for (const auto& pos : newWall) {
            grid[pos[0]][pos[1]].type = '#';
        }

        // 4. Check for connectivity. If it's broken, undo the change.
        if (!IsConnected()) {
            for (const auto& pos : newWall) {
                grid[pos[0]][pos[1]].type = ' '; // Revert
            }
        }
    }
}

bool Generator::IsConnected() {
    // Find total number of empty tiles
    int totalEmptyTiles = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j].type == ' ') {
                totalEmptyTiles++;
            }
        }
    }

    // If there are no empty tiles, it's technically connected.
    if (totalEmptyTiles == 0) return true;

    // Setup for BFS
    queue<vector<int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int reachableEmptyTiles = 0;

    // Start BFS from player's starting position (guaranteed to be empty)
    q.push(startingPos);
    visited[startingPos[0]][startingPos[1]] = true;

    while (!q.empty()) {
        vector<int> current = q.front();
        q.pop();
        reachableEmptyTiles++;

        // Check neighbors (Up, Down, Left, Right)
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int newRow = current[0] + dr[i];
            int newCol = current[1] + dc[i];

            // Check bounds and if it's a valid, unvisited empty tile
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                !visited[newRow][newCol] && grid[newRow][newCol].type == ' ') {
                visited[newRow][newCol] = true;
                q.push({newRow, newCol});
            }
        }
    }

    // If we reached every empty tile, the map is connected.
    return totalEmptyTiles == reachableEmptyTiles;
}
