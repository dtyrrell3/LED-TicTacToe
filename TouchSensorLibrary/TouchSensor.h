#ifndef TouchSensor_H
#define TouchSensor_H

#include "Arduino.h"

class TouchSensor {
    byte sensitivity;
    byte pin;
    byte position;
    uint8_t readCapacitivePin(byte pinToMeasure);
public:
    TouchSensor();
    TouchSensor(byte sensitivity, byte pin, byte position);
    void initializeWithParams(byte sensitivity, byte pin, byte position);
    boolean touched();
};


#endif