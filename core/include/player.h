// core/include/player.h

#pragma once

#include <vector>

class Player {
public:
    // Constructor
    Player(const std::vector<int> &pos) : pos(pos) {}

    // Move Function
    void move(int x, int y);

    // Getter and Setter
    std::vector<int> getPosition() const { return pos; }
    void setPosition(const std::vector<int> &newPos) { pos = newPos; }

private:
    // Position
    std::vector<int> pos;
};
