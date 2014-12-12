#include "Game.h"

Game::Game(Adafruit_NeoPixel *strip1) {
    strip = strip1;
    (*strip).setPixelColor(0, 150, 0, 0);
    uint32_t color0 = (*strip).Color(100, 0, 0);
    uint32_t color1 = (*strip).Color(0, 0, 100);
    board = &Board(strip);
    player0 = &Player(board, color0);
    player1 = &Player(board, color1);
    playerWon = false;
    gameDraw = false;
}

void Game::play() {
    // (*strip).setPixelColor(2, 150, 0, 0);
    (*board).reset();
    Serial.println("Entering Play");
    while(!playerWon && !gameDraw) {
        Serial.println("Beginning Player0's turn");
        takeTurn(player0);
        if (playerWon || gameDraw) {
            break;
        }
        Serial.println("Beginning Player1's turn");
        takeTurn(player1);
    }
    delay(5000); // Delay 5 seconds before victory sequence
    if (playerWon) {
        (*board).victory();    
    } else if (gameDraw) {
        // Nobody won.
    }
    (*board).reset();
}

void Game::takeTurn(Player *player) {
    Serial.println("Entering Taketurn");
    boolean validMove = false;
    byte move;
    while (!validMove) {
        move = (*player).getMove();
        Serial.print("Received move ");
        Serial.println(move);
        validMove = checkValidMove(move);
        Serial.print("The move was ");
        Serial.println(validMove);
        if (validMove) {
            break;
        }
    }
    (*player).makeMove(move);
    Serial.print("Made move ");
    Serial.println(move);
    achievedVictory();
}

boolean Game::checkValidMove(byte numTile) {
    Serial.print("Entering check valid move on ");
    Serial.println(numTile);
    if ((*board).boardState[numTile]) {
        return false;
    }
    return true;
}

void Game::achievedVictory() {
    // Check for victory
    // If victory, set playerWon to True
    // If gameDraw, set gameDraw to True
}