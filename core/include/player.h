// core/include/player.h

#pragma once

#include <vector>

using namespace std;

class Player {
public:
    // Contstructor
    Player(const vector<int> &pos) : pos(pos) {}

    // Move Function
    void move(int x, int y);

private:
    // Position
    vector<int> pos;

public:
    // Getter and Setter
    vector<int> getPosition() { return pos; }
    void setPosition(vector<int> newPos) { pos = newPos; }
};
