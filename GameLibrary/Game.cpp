#include "Game.h"

Game::Game(Adafruit_NeoPixel *strip1) {
    strip = strip1;
    uint32_t color0 = (*strip).color(100, 0, 0);
    uint32_t color1 = (*strip).color(0, 0, 100);
    board = Board(strip);
    player0 = Player(&board, color0);
    player1 = Player(&board, color1);
    player0Turn = true;
    playerWon = false;
    gameDraw = false;
}

void Game::play() {
    while(!playerWon && !gameOver) {
        takeTurn(&player0);
        if (playerWon || gameOver) {
            break;
        }
        takeTurn(&player1);
    }
    delay(5000); // Delay 5 seconds before victory sequence
    if (playerWon) {
        board.victory();    
    } else if (gameDraw) {
        // Nobody won.
    }
    board.reset();
}

void Game::takeTurn(Player *player) {
    boolean validMove = false;
    byte move;
    while (!validMove) {
        move = (*player).getMove();
        validMove = checkValidMove(move);
        if (validMove) {
            break;
        }
    }
    (*player).makeMove(move);
    achievedVictory();
}

boolean Game::checkValidMove(byte numTile) {
    if (board.boardState[numTile]) {
        return false;
    }
    return true;
}

void Game::achievedVictory() {
    // Check for victory
    // If victory, set playerWon to True
    // If gameDraw, set gameDraw to True
}