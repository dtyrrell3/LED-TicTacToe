#include <Adafruit_NeoPixel.h>
#include <Board.h>
#include <LED.h>
#include <TouchSensor.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 0, NEO_GRB + NEO_KHZ800);

Board board(&strip);

void setup() {
  strip.begin();
  strip.show();  
}

void loop() {
   for (int i = 0; i < 20; i++) { 
     byte move = board.getMove(); 
     board.makeMove(move, strip.Color(100,0,0));
     delay(250);
     move = board.getMove(); 
     board.makeMove(move, strip.Color(0,0,100));
     delay(250);
   }
   board.reset();
}
