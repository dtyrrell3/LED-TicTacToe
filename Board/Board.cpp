#include "Board.h"
#include "LED.h"

Board::Board(Adafruit_NeoPixel strip1) {
    strip = strip1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        ledArray[i] = LED(strip, i);
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        touchSensorArray[i] = TouchSensor(3, i + 1, i);
    }
}

void Board::reset() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        ledArray[i].turnOff();
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        boardState[i] = 0;
    }
}

boolean Board::pollTile(byte numTile) {
    /* Check if our index is within range. */
    if (numTile >= BOARD_SIZE) {
        return -1;
    }
    TouchSensor touchSensor = touchSensorArray[numTile];
    return touchSensor.touched();
}

byte Board::getMove() {
    while (1) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (pollTile(i)) {
                return i;
            }
        }
    }
}

void Board::makeMove(byte numTile, uint32_t color) {
    if (numTile >= BOARD_SIZE) {
        return -1;
    }
    ledArray[numTile].turnOn(color);
    boardState[numTile] = 1;
}

void Board::victory() {
    // Put victory sequence
}

