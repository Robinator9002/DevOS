// core/src/dungeon.cpp

#include <dungeon.h>

Dungeon::Dungeon(int rows, int cols, vector<int> startingPos, vector<vector<int>> walls) : rows(rows), cols(cols), startingPos(startingPos), walls(walls) {
    // Start of by calling the create dungeon function
    CreateDungeon();
}

void Dungeon::Initialize() {
    // Initialize Grid and Player Variables
    InitDungeon();
    InitPlayer();
}

bool Dungeon::MovePlayer(const vector<int> &movement) {
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

void Dungeon::Print() {
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

void Dungeon::Cleanup() {
    // Clear individual Tiles
    for (int i = 0; i < rows; ++i)
        delete[] grid[i];

    // Clear full Dungeon
    delete[] grid;

    // Clear Player
    delete player;
}

void Dungeon::CreateDungeon() {
    // Create empty Grid
    grid = new Tile *[rows];

    // Fill Grid with Cols
    for (int i = 0; i < rows; ++i)
        grid[i] = new Tile[cols];
}

void Dungeon::InitDungeon() {
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

void Dungeon::InitPlayer() {
    // Create Player Class
    player = new Player(startingPos);

    // Get Position
    vector<int> pos = player->getPosition();

    // Intialize Player
    grid[pos[0]][pos[1]].type = 'P';
}

void Dungeon::PrintBorder() {
    // A line of cols number of # plus 2 for corners
    for (int j = 0; j < cols + 2; ++j)
        cout << "#";
    cout << "\n";
}
