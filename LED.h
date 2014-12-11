#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class LED {
    byte num;
    Adafruit_NeoPixel strip;
    boolean on;
public:
    LED(Adafruit_NeoPixel strip, byte num);
    turnOn(uint32_t color);
    turnOff();
};


#endif