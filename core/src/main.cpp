// core/src/main.cpp

#include <dungeon.h>
#include <ncurses.h>
#include <unistd.h>
#include <vector>

int main() {
    // NCURSES INITIALIZATION
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    // GAME SETUP
    Dungeon dungeon(20, 70, {10, 35});
    dungeon.Initialize();

    // GAME LOOP
    bool game_running = true;
    while (game_running) {
        // 1. INPUT
        int ch = getch();
        std::vector<int> movement = {0, 0};

        switch (ch) {
        case 'q':
            game_running = false;
            break; // Exit game
        // WASD Movement
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
        // Diagonal Movement
        case 'e':
            movement = {-1, 1};
            break; // Up-Right
        case 'r':
            movement = {-1, -1};
            break; // Up-Left (using 'r' for qwert)
        case 'c':
            movement = {1, 1};
            break; // Down-Right
        case 'z':
            movement = {1, -1};
            break; // Down-Left
        }

        // 2. UPDATE
        if (movement[0] != 0 || movement[1] != 0) {
            dungeon.MovePlayer(movement);
        }

        // 3. DRAW
        clear();
        dungeon.Print();
        mvprintw(22, 2, "Use WASD, (r,e,z,c) for diagonals. Press 'q' to quit.");
        refresh();

        // 4. TIMING
        usleep(16000); // ~60 FPS
    }

    // NCURSES CLEANUP
    endwin();

    return 0;
}
