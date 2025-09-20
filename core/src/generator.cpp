// core/src/generator.cpp

#include <generator.h>
#include <queue>
#include <random>

Generator::Generator(int rows, int cols, Tile **grid, std::vector<int> startingPos) : rows(rows), cols(cols), grid(grid), startingPos(startingPos) {
}

void Generator::ProceduralGenerateWalls() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wallTypeDist(0, 2); // 0=H-Line, 1=V-Line, 2=Square
    std::uniform_int_distribution<> lengthDist(2, 5);
    std::uniform_int_distribution<> squareDist(2, 3);
    std::uniform_int_distribution<> rowDist(0, rows - 1);
    std::uniform_int_distribution<> colDist(0, cols - 1);

    const int numberOfWallsToTry = 75;

    for (int i = 0; i < numberOfWallsToTry; ++i) {
        std::vector<std::vector<int>> newWallCoords;
        int r_start = rowDist(gen);
        int c_start = colDist(gen);
        int type = wallTypeDist(gen);

        if (type == 0) { // Horizontal Line
            int len = lengthDist(gen);
            for (int c = 0; c < len; ++c)
                newWallCoords.push_back({r_start, c_start + c});
        } else if (type == 1) { // Vertical Line
            int len = lengthDist(gen);
            for (int r = 0; r < len; ++r)
                newWallCoords.push_back({r_start + r, c_start});
        } else { // Square
            int size = squareDist(gen);
            for (int r = 0; r < size; ++r) {
                for (int c = 0; c < size; ++c)
                    newWallCoords.push_back({r_start + r, c_start + c});
            }
        }

        bool canPlace = true;
        for (const auto &pos : newWallCoords) {
            if (pos[0] <= 0 || pos[0] >= rows - 1 || pos[1] <= 0 || pos[1] >= cols - 1 || grid[pos[0]][pos[1]].type != ' ') {
                canPlace = false;
                break;
            }
        }

        if (!canPlace)
            continue;

        for (const auto &pos : newWallCoords)
            grid[pos[0]][pos[1]].type = '#';

        if (!IsConnected()) {
            for (const auto &pos : newWallCoords)
                grid[pos[0]][pos[1]].type = ' ';
        }
    }
}

bool Generator::IsConnected() {
    int totalEmptyTiles = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j].type == ' ')
                totalEmptyTiles++;
        }
    }
    if (totalEmptyTiles == 0)
        return true;

    std::queue<std::vector<int>> q;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    int reachableEmptyTiles = 0;

    q.push(startingPos);
    visited[startingPos[0]][startingPos[1]] = true;

    while (!q.empty()) {
        std::vector<int> current = q.front();
        q.pop();
        reachableEmptyTiles++;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int newRow = current[0] + dr[i];
            int newCol = current[1] + dc[i];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                !visited[newRow][newCol] && grid[newRow][newCol].type == ' ') {
                visited[newRow][newCol] = true;
                q.push({newRow, newCol});
            }
        }
    }
    return totalEmptyTiles == reachableEmptyTiles;
}
