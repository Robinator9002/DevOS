// core/src/main.cpp

#include <iostream>
#include <vector>

// Include custom classes
#include <dungeon.h>

// Include custom getch tool
#include <getch.h>

using namespace std;

vector<int> convertInputToMovement(char input) {
    // Init Movement
    vector<int> movement = {0, 0};

    // Iterate through Input
    switch (input) {
    case 'w':
        movement[0] = -1;
        break;
    case 'a':
        movement[1] = -1;
        break;
    case 's':
        movement[0] = 1;
        break;
    case 'd':
        movement[1] = 1;
        break;
    default:
        break;
    }

    // Return final Movement
    return movement;
}

int main() {
    // Variables
    int rows = 10, cols = 50;
    vector<int> startingPos = {0, 0};
    vector<vector<int>> walls = {{2, 3}};

    // Create and Initialize Dungeon and Player
    Dungeon dungeon = Dungeon(rows, cols, startingPos, walls);
    dungeon.Initialize();

    // Print out the dungeon once at the beginning
    dungeon.Print();

    // The main loop
    char input;
    while ((input = getch()) != 'q') {
        vector<int> movement = convertInputToMovement(input);
        dungeon.MovePlayer(movement);
        dungeon.Print();
    }

    // Cleanup afterwards
    dungeon.Cleanup();
}
