#ifndef BOARD_H
#define BOARD_H
#define BOARD_SIZE 16


#include "Arduino.h"
#include "LED.h"
#include "TouchSensor.h"


/* This is a (sqrt(BOARD_SIZE)) 4x4 board.  */
class Board {
    Adafruit_NeoPixel strip;
    LED ledArray[BOARD_SIZE];
    TouchSensor touchSensorArray[BOARD_SIZE];
    boolean pollTile(byte numTile);
public:
    Board(Adafruit_NeoPixel strip);
    reset();
    victory();
    byte getMove();
    makeMove(byte numTile, uint32_t color);
};

#endif