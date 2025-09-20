// core/include/dungeon

#pragma once

#include <vector>

// Include custom classes
#include <player.h>
#include <tile.h>

// Include generator class for Procedural Wall Generation
#include <generator.h>

using namespace std;

class Dungeon {
public:
    // Constructor
    Dungeon(int rows, int cols, vector<int> startingPos, vector<vector<int>> walls);

    // Public class variables
    int rows;
    int cols;
    Tile **grid;
    Player *player;
    vector<int> startingPos;
    vector<vector<int>> walls;

    // Initialize function calls all other private init functions
    void Initialize();

    // Moves the player element
    bool MovePlayer(const vector<int> &movement);

    // Printing
    void Print();

    // Final Cleanup (deletes everything for garbage collection)
    void Cleanup();

private:
    // Create Dungeon
    void CreateDungeon();

    // Init Functions
    void InitDungeon();
    void InitPlayer();

    // Print Border
    void PrintBorder();
};
