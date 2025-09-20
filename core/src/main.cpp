// core/src/main.cpp

#include <iostream>
#include <vector>
#include <unistd.h>
#include <termios.h>

using namespace std;

char getch() {
    // Custom getch() function, cause linux doesnt support it directly
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;  // Disable buffered I/O
    old.c_lflag &= ~ECHO;    // Disable echo
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return buf;
}

class Player {
    public:
        // Contstructor
        Player(const vector<int>& pos) : pos(pos) {}

        // Move Function
        void move(int x, int y) {
            pos[0] += x;
            pos[1] += y;
        }
    private:
        // Position
        vector<int> pos;
    public:
        // Getter and Setter
        vector<int> getPosition() { return pos; }
        void setPosition(vector<int> newPos) { pos = newPos; }
};

class Dungeon {
    public:
        Dungeon(int rows, int cols, vector<vector<int>> walls) : rows(rows), cols(cols), walls(walls) {
            CreateDungeon();
        }

        int rows;
        int cols;
        vector<vector<int>> walls;
        Tile** grid;
        Player* player;

    private:
        void CreateDungeon() {
            // Create empty Grid
            grid = new Tile*[rows];

            // Fill Grid with Cols
            for (int i = 0; i < rows; ++i)
                grid[i] = new Tile[cols];
        }

        void InitDungeon() {
            // Initialize Empty
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; ++j) {
                    grid[i][j].type = ' ';
                }
            }

            // Initialize Walls
            for(vector<int> wall : walls)
                grid[wall[0]][wall[1]].type = '#';
        }
};

struct Tile {
    char type; // ' ' = empty, '#' = wall, 'P' = Player
};

void InitPlayer() {
    // Get Position:
    vector<int> pos = player->getPosition();

    // Intialize Player
    grid[pos[0]][pos[1]].type = 'P';
}

bool MovePlayer(Tile** dungeon, Player* player, int rows, int cols, const vector<int>& movement) {
    // Save old Position for later
    const vector<int>& pos = player->getPosition();

    // Find new Position
    vector<int> newPos = { pos[0] + movement[0], pos[1] + movement[1] };

    // Validate Position
    // if occupied or outside of map return failure
    if (newPos[0] < 0 || newPos[0] >= rows || newPos[1] < 0 || newPos[1] >= cols) return false;
    if(!(dungeon[newPos[0]][newPos[1]].type == ' ')) return false;

    // Call the Player Move Function
    player->move(movement[0], movement[1]);

    // Actualize Position in the dungeon
    dungeon[pos[0]][pos[1]].type = ' ';
    dungeon[newPos[0]][newPos[1]].type = 'P';

    // Return success
    return true;
}

void PrintBorder(int cols) {
    // A line of cols number of # plus 2 for corners
    for(int j = 0; j < cols + 2; ++j) cout << "#";
    cout << "\n";
}

void PrintDungeon(Tile** dungeon, int rows=5, int cols=5) {
    // Print out every Row and Column in the Dungeon, and borders at each side
    PrintBorder(cols);  // Top border
    for(int i = 0; i < rows; ++i) {
        cout << "#";    // Left Border
        for(int j = 0; j < cols; ++j) {
            cout << dungeon[i][j].type;
        }
        cout << "#\n";  // Right Border
    }
    PrintBorder(cols);  // Bottom border
}

vector<int> convertInputToMovement(char input) {
    // Init Movement
    vector<int> movement = {0,0};

    // Iterate through Input
    switch(input) {
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

void Cleanup(Tile** dungeon, int rows, Player* player) {
    // Clear individual Tiles
    for(int i = 0; i < rows; ++i)
        delete[] dungeon[i];

    // Clear full Dungeon
    delete[] dungeon;

    // Clear Player
    delete[] player;
}

int main() {
    // Variables
    int rows = 10, cols = 50;

    // Create and Initialize Dungeon and Player
    Tile** dungeon = CreateDungeon(rows, cols);
    InitDungeon(dungeon, rows, cols);
    Player* player = new Player({0,0});
    InitPlayer(dungeon, player);

    // Print out the dungeon once at the beginning
    PrintDungeon(dungeon, rows, cols);

    // The main loop
    char input;
    while ((input = getch()) != 'q') {
        vector<int> movement = convertInputToMovement(input);
        MovePlayer(dungeon, player, rows, cols, movement);
        PrintDungeon(dungeon, rows, cols);
    }

    // Cleanup afterwards
    Cleanup(dungeon, rows, player);
}
