#include "Board.h"

Board::Board(Adafruit_NeoPixel *strip1) {
    strip = strip1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        ledArray[i].initializeWithParams(strip, i, 0);
    }
    touchSensorArray[0].initializeWithParams(4, 17, 0);
    for (byte i = 1; i < BOARD_SIZE; i++) {
        touchSensorArray[i].initializeWithParams(4, i + 1, i);
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        boardState[i] = 0;
    }
}

void Board::reset() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        ledArray[i].turnOff();
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        boardState[i] = 0;
    }
}

boolean Board::pollTile(byte numTile) {
    /* Check if our index is within range. */
    if (numTile >= BOARD_SIZE) {
        return -1;
    }
    return touchSensorArray[numTile].touched();
}

byte Board::getMove() {
    while (1) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (pollTile(i)) {
                return i;
            }
        }
    }
}

uint32_t Board::getColorTile(byte numTile) {
    if (numTile >= BOARD_SIZE) {
        return -1;
    }
    return ledArray[numTile].getColor();
}

void Board::makeMove(byte numTile, uint32_t color) {
    if (numTile >= BOARD_SIZE) {
        return;
    }
    ledArray[numTile].turnOn(color);
    boardState[numTile] = 1;
}

void Board::draw() {
    uint32_t red = strip->Color(255, 0, 0);
    uint32_t green = strip->Color(0, 100, 0);
    uint32_t redGreen = strip->Color(100, 100, 0);
    uint32_t greenBlue = strip->Color(0, 100, 100);
    uint32_t blue = strip->Color(0, 0, 100);
    for (byte i = 0; i < 20; i++) {
        drawX(red);
        delay(100);
        drawX(0);
        delay(100);
    }
    drawD(redGreen);
    delay(3000);
    drawD(0);
    drawR(green);
    delay(3000);
    drawR(0);
    drawA(greenBlue);
    delay(3000);
    drawA(0);
    drawW(blue);
    delay(3000);
    drawW(0);
}

void Board::drawX(uint32_t color) {
    for (byte i = 0; i <= 15; i+= 5) {
        strip->setPixelColor(i, color);
    }
    for (byte i = 3; i <= 12; i+= 3) {
        strip->setPixelColor(i, color);
    }
    strip->show();
}

void Board::drawD(uint32_t color) {
    strip->setPixelColor(0, color);
    strip->setPixelColor(1, color);
    strip->setPixelColor(2, color);
    strip->setPixelColor(4, color);
    strip->setPixelColor(7, color);
    strip->setPixelColor(8, color);
    strip->setPixelColor(11, color);
    strip->setPixelColor(12, color);
    strip->setPixelColor(13, color);
    strip->setPixelColor(14, color);
    strip->show();
}

void Board::drawR(uint32_t color) {
    strip->setPixelColor(0, color);
    strip->setPixelColor(1, color);
    strip->setPixelColor(2, color);
    strip->setPixelColor(3, color);
    strip->setPixelColor(4, color);
    strip->setPixelColor(7, color);
    strip->setPixelColor(8, color);
    strip->setPixelColor(9, color);
    strip->setPixelColor(10, color);
    strip->setPixelColor(12, color);
    strip->setPixelColor(15, color);
    strip->show();
}

void Board::drawA(uint32_t color) {
    strip->setPixelColor(1, color);
    strip->setPixelColor(2, color);
    strip->setPixelColor(4, color);
    strip->setPixelColor(7, color);
    strip->setPixelColor(8, color);
    strip->setPixelColor(9, color);
    strip->setPixelColor(10, color);
    strip->setPixelColor(11, color);
    strip->setPixelColor(12, color);
    strip->setPixelColor(15, color);
    strip->show();
}

void Board::drawW(uint32_t color) {
    strip->setPixelColor(0, color);
    strip->setPixelColor(3, color);
    strip->setPixelColor(4, color);
    strip->setPixelColor(7, color);
    strip->setPixelColor(9, color);
    strip->setPixelColor(10, color);
    strip->setPixelColor(13, color);
    strip->setPixelColor(14, color);
    strip->show();
}


void Board::victory(byte *winningTiles, uint32_t winningColor) {
    for (byte j = 0; j < 5; j++) {
        for (byte i = 0; i < 4; i++) {
            strip->setPixelColor(winningTiles[i], winningColor);
        }
        strip->show();
        delay(500);
        for (byte i = 0; i < 4; i++) {
            strip->setPixelColor(winningTiles[i], 0);
        }
        strip->show();
        delay(500);
    }

    /* Victory sequence is the strandTest example 
     * for the LED strip. I have adapted it to work
     * with this class structure. */
    colorWipe(strip->Color(255, 0, 0), 50); // Red
    colorWipe(strip->Color(0, 255, 0), 50); // Green
    colorWipe(strip->Color(0, 0, 255), 50); // Blue
    // Send a theater pixel chase in...
    theaterChase(strip->Color(127, 127, 127), 50); // White
    theaterChase(strip->Color(127,   0,   0), 50); // Red
    theaterChase(strip->Color(  0,   0, 127), 50); // Blue

    rainbow(20);
    rainbowCycle(20);
    theaterChaseRainbow(50);
}



/* From the example strandTest for the LED strip. */

// Fill the dots one after the other with a color
void Board::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip->numPixels(); i++) {
      strip->setPixelColor(i, c);
      strip->show();
      delay(wait);
  }
}

void Board::rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip->numPixels(); i++) {
      strip->setPixelColor(i, Wheel((i+j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void Board::rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip->numPixels(); i++) {
      strip->setPixelColor(i, Wheel(((i * 256 / strip->numPixels()) + j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void Board::theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip->show();
     
      delay(wait);
     
      for (int i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void Board::theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip->numPixels(); i=i+3) {
          strip->setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip->show();
       
        delay(wait);
       
        for (int i=0; i < strip->numPixels(); i=i+3) {
          strip->setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Board::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}