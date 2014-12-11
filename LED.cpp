#include "LED.h"

LED::LED(Adafruit_NeoPixel strip1, byte num1) {
    strip = strip1;
    num = num1;
}

LED::turnOn(uint32_t color) {
    strip.setPixelColor(num, color);
    strip.show();
    on = true;
}

LED::turnOff() {
    strip.setPixelColor(num, 0);
    strip.show();
    on = false;
}