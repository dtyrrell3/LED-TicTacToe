#ifndef GAME_H
#define GAME_H

#include "Arduino.h"
#include "Board.h"
#include "Player.h"
#include <Adafruit_NeoPixel.h>

class Game {
    Adafruit_NeoPixel *strip;
    Board *board;
    Player *player0;
    Player *player1;
    uint32_t color0;
    uint32_t color1;
    boolean playerWon;
    boolean gameDraw;
    boolean checkValidMove(byte numTile);
    void achievedVictory();
    uint32_t winningColor;
public:
    Game(Adafruit_NeoPixel *strip);
    ~Game();
    void play();
    void takeTurn(Player *player);
    byte winningTiles[4];
};

#endif