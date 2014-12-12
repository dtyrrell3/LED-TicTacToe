#include <Adafruit_NeoPixel.h>
#include <Board.h>
#include <LED.h>
#include <TouchSensor.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 0, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(0,0,125);
LED led(&strip, 2, color);
Board board(&strip);

void setup() {
  strip.begin();
  strip.show(); 
}

void loop() {
//  led.turnOn(color);
//  delay(300);
//  board.reset();
//  delay(300);

//  for (int i = 0; i < 16; i++) {
//    strip.setPixelColor(i, 100,0,0);
//    strip.show();
//    delay(200);
//  }

  LED ledArray[16];
  for(int j = 0; j < 255; j++) {
    for(int k = 0; k < 255; k++) {
     for (int l = 0; l < 255; l++) {
        for(int i = 0; i < 16; i++) {
           ledArray[i].initializeWithParams(&strip, i, j);
        }
        for(int i = 0; i < 16; i++) {
          ledArray[i].turnOn(strip.Color(l, j, l));
          delay(10);
        }
        for(int i = 0; i < 16; i++) {
          ledArray[i].turnOff();
           delay(10);
        }
     }
    }
  }
}
