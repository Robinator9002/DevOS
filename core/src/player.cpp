// core/src/player.cpp

#include <player.h>

void Player::move(int x, int y) {
    // Move the player by an x and y value
    pos[0] += x;
    pos[1] += y;
}
