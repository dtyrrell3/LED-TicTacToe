#ifndef PLAYER_H
#define PLAYER_H

#include "Arduino.h"

class Player {
    uint32_t color;
    Board board;
public:
    Player(Board board, uint32_t color);
    byte getMove();
    makeMove(byte numTile);
};

#endif