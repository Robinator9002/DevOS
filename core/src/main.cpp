// core/src/main.cpp

#include <iostream>
#include <vector>

// Import custom classes
#include <player.h>

// Import custom getch tool
#include <getch.h>

using namespace std;

class Dungeon {
public:
    Dungeon(int rows, int cols, vector<int> startingPos, vector<vector<int>> walls) : rows(rows), cols(cols), startingPos(startingPos), walls(walls) {
        CreateDungeon();
    }

    int rows;
    int cols;
    Tile **grid;
    Player *player;
    vector<int> startingPos;
    vector<vector<int>> walls;

    void Initialize() {
        InitDungeon();
        InitPlayer();
    }

    bool MovePlayer(const vector<int> &movement) {
        // Save old Position for later
        const vector<int> &pos = player->getPosition();

        // Find new Position
        vector<int> newPos = {pos[0] + movement[0], pos[1] + movement[1]};

        // Validate Position
        // if occupied or outside of map return failure
        if (newPos[0] < 0 || newPos[0] >= rows || newPos[1] < 0 || newPos[1] >= cols)
            return false;
        if (!(grid[newPos[0]][newPos[1]].type == ' '))
            return false;

        // Call the Player Move Function
        player->move(movement[0], movement[1]);

        // Actualize Position in the dungeon
        grid[pos[0]][pos[1]].type = ' ';
        grid[newPos[0]][newPos[1]].type = 'P';

        // Return success
        return true;
    }

    void Print() {
        // Print out every Row and Column in the Dungeon, and borders at each side
        PrintBorder(); // Top border
        for (int i = 0; i < rows; ++i) {
            cout << "#"; // Left Border
            for (int j = 0; j < cols; ++j) {
                cout << grid[i][j].type;
            }
            cout << "#\n"; // Right Border
        }
        PrintBorder(); // Bottom border
    }

    void Cleanup() {
        // Clear individual Tiles
        for (int i = 0; i < rows; ++i)
            delete[] grid[i];

        // Clear full Dungeon
        delete[] grid;

        // Clear Player
        delete[] player;
    }

private:
    void CreateDungeon() {
        // Create empty Grid
        grid = new Tile *[rows];

        // Fill Grid with Cols
        for (int i = 0; i < rows; ++i)
            grid[i] = new Tile[cols];
    }

    void InitDungeon() {
        // Initialize Empty
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; ++j) {
                grid[i][j].type = ' ';
            }
        }

        // Initialize Walls
        for (vector<int> wall : walls)
            grid[wall[0]][wall[1]].type = '#';
    }

    void InitPlayer() {
        // Create Player Class
        player = new Player(startingPos);

        // Get Position
        vector<int> pos = player->getPosition();

        // Intialize Player
        grid[pos[0]][pos[1]].type = 'P';
    }

    void PrintBorder() {
        // A line of cols number of # plus 2 for corners
        for (int j = 0; j < cols + 2; ++j)
            cout << "#";
        cout << "\n";
    }
};

struct Tile {
    char type; // ' ' = empty, '#' = wall, 'P' = Player
};

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
    Dungeon *dungeon = &Dungeon(rows, cols, startingPos, walls);
    dungeon->Initialize();

    // Print out the dungeon once at the beginning
    dungeon->Print();

    // The main loop
    char input;
    while ((input = getch()) != 'q') {
        vector<int> movement = convertInputToMovement(input);
        dungeon->MovePlayer(movement);
        dungeon->Print();
    }

    // Cleanup afterwards
    dungeon->Cleanup();
}
