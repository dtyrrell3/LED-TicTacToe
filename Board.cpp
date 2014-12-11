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

Board::reset() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        ledArray[i].turnOff();
    }
}

Board::pollTile(byte num) {
    /* Check if our index is within range. */
    if (num >= BOARD_SIZE) {
        return -1;
    }
    TouchSensor touchSensor = touchSensorArray[num];
    return touchSensor.touched();
}

