#ifndef BOARD_H
#define BOARD_H
#define BOARD_SIZE 16


#include "Arduino.h"
#include "LED.h"
#include "TouchSensor.h"


/* This is a (sqrt(BOARD_SIZE)) 4x4 board.  */
class Board {
    Adafruit_NeoPixel *strip;
    LED ledArray[BOARD_SIZE];
    TouchSensor touchSensorArray[BOARD_SIZE];
    boolean pollTile(byte numTile);
    /* Victory and draw sequence functions. */
    void drawX(uint32_t color);
    void drawD(uint32_t color);
    void drawR(uint32_t color);
    void drawA(uint32_t color);
    void drawW(uint32_t color);
    void colorWipe(uint32_t c, uint8_t wait);
    void rainbow(uint8_t wait);
    void rainbowCycle(uint8_t wait);
    void theaterChase(uint32_t c, uint8_t wait);
    void theaterChaseRainbow(uint8_t wait);
    uint32_t Wheel(byte WheelPos);
public:
    Board(Adafruit_NeoPixel *strip);
    void reset();
    void victory(byte *winningTiles, uint32_t winningColor);
    void draw();
    byte getMove();
    void makeMove(byte numTile, uint32_t color);
    uint32_t getColorTile(byte numTile);
    byte boardState[BOARD_SIZE];
};

#endif