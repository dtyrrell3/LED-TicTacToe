#include <Game.h>
#include <Player.h>
#include <Board.h>
#include <LED.h>
#include <TouchSensor.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 0, NEO_GRB + NEO_KHZ800);
Game game(&strip);
  
void setup() {
  strip.begin();
  strip.show();

}

void loop() {
  game.play();
}
