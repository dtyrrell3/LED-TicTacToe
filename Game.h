#ifndef GAME_H
#define GAME_H

#include "Arduino.h"
#include "Board.h"
#include "Player.h"

class Game {
    Player player0;
    Player player1;
    Board board;
    boolean player0Turn;
    boolean checkValidMove(byte numTile);
public:
    Game();
    play();
    takeTurn(Player player);
};

#endif