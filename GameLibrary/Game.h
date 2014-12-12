#ifndef GAME_H
#define GAME_H

#include "Arduino.h"
#include "Player.h"
#include "Board.h"
#include <Adafruit_NeoPixel.h>

class Game {
    Board board;
    Player player0;
    Player player1;
    boolean player0Turn;
    boolean playerWon;
    boolean gameDraw;
    boolean checkValidMove(byte numTile);
    void achievedVictory();
public:
    Game(Adafruit_NeoPixel *strip);
    void play();
    void takeTurn(Player *player);
};

#endif