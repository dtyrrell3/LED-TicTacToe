#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class LED {
    byte num;
    Adafruit_NeoPixel strip;
    uint32_t color;
    boolean on;
public:
    LED(Adafruit_NeoPixel strip, byte num, uint32_t color);
    turnOn(uint32_t color);
    turnOff();
};


#endif