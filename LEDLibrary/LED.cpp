#include "LED.h"

LED::LED() {
    // This should never be used.
}

LED::LED(Adafruit_NeoPixel *strip1, byte num1, uint32_t color1) {
    strip = strip1;
    num = num1;
    color = color1;
}

void LED::initializeWithParams(Adafruit_NeoPixel *strip1, byte num1, uint32_t color1) {
    strip = strip1;
    num = num1;
    color = color1;
}

void LED::turnOn(uint32_t color1) {
    strip->setPixelColor(num, color1);
    strip->show();
    on = true;
    color = color1;
}

void LED::turnOff() {
    Serial.println("Entering turnOff");
    strip->setPixelColor(num, 0);
    strip->show();
    on = false;
    color = 0;
}

uint32_t LED::getColor() {
    return color;
}