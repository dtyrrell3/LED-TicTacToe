#include "Game.h"

Game::Game() {
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(BOARD_SIZE, PIN, NEO_GRB + NEO_KHZ800);
    board = Board(strip);
    player0 = Player()
}