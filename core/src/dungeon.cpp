// core/src/dungeon.cpp

#include <dungeon.h>
#include <generator.h> // Used locally in Initialize
#include <ncurses.h>   // For printing functions

Dungeon::Dungeon(int rows, int cols, std::vector<int> startingPos) : rows(rows), cols(cols), grid(nullptr), player(nullptr), startingPos(startingPos) {
    CreateDungeon();
}

Dungeon::~Dungeon() {
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
    delete player;
}

void Dungeon::Initialize() {
    InitDungeon();

    Generator generator(rows, cols, grid, startingPos);
    generator.ProceduralGenerateWalls();

    InitPlayer();
}

bool Dungeon::MovePlayer(const std::vector<int> &movement) {
    const std::vector<int> &pos = player->getPosition();
    std::vector<int> newPos = {pos[0] + movement[0], pos[1] + movement[1]};

    if (newPos[0] < 0 || newPos[0] >= rows || newPos[1] < 0 || newPos[1] >= cols)
        return false;
    if (grid[newPos[0]][newPos[1]].type != ' ')
        return false;

    grid[pos[0]][pos[1]].type = ' ';
    player->move(movement[0], movement[1]);
    grid[player->getPosition()[0]][player->getPosition()[1]].type = 'P';
    return true;
}

void Dungeon::Print() const {
    // Ncurses uses (y, x) coordinates
    // Print top/bottom borders
    for (int j = 0; j < cols + 2; ++j) {
        mvaddch(0, j, '#');
        mvaddch(rows + 1, j, '#');
    }

    // Print grid and side borders
    for (int i = 0; i < rows; ++i) {
        mvaddch(i + 1, 0, '#'); // Left border
        for (int j = 0; j < cols; ++j) {
            mvaddch(i + 1, j + 1, grid[i][j].type);
        }
        mvaddch(i + 1, cols + 1, '#'); // Right border
    }
}

void Dungeon::CreateDungeon() {
    grid = new Tile *[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new Tile[cols];
    }
}

void Dungeon::InitDungeon() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j].type = ' ';
        }
    }
}

void Dungeon::InitPlayer() {
    player = new Player(startingPos);
    grid[startingPos[0]][startingPos[1]].type = 'P';
}
