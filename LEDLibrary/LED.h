#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class LED {
    byte num;
    Adafruit_NeoPixel *strip;
    uint32_t color;
    boolean on;
public:
    LED();
    LED(Adafruit_NeoPixel *strip, byte num, uint32_t color);
    void turnOn(uint32_t color);
    void turnOff();
};


#endif