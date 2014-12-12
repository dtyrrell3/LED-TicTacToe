#ifndef PLAYER_H
#define PLAYER_H

#include "Arduino.h"
#include "Board.h"

class Player {
    uint32_t color;
    Board *board;
public:
    Player(Board *board1, uint32_t color1);
    byte getMove();
    void makeMove(byte numTile);
};

#endif