#include "Game.h"

Game::Game() {
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(BOARD_SIZE, PIN, NEO_GRB + NEO_KHZ800);
    uint32_t color0 = strip.color(100, 0, 0);
    uint32_t color1 = strip.color(0, 0, 100);
    board = Board(strip);
    player0 = Player(board, color0);
    player1 = Player(board, color1);
    player0Turn = true;
    playerWon = false;
}

void Game::play() {
    while(!playerWon) {
        takeTurn(player0);
        if (playerWon) {
            break;
        }
        takeTurn(player1);
    }
    delay(5000); // Delay 5 seconds before victory sequence
    board.victory();
    board.reset();
}

void Game::takeTurn(Player player) {
    boolean validMove = false;
    byte move;
    while (!validMove) {
        move = player.getMove();
        validMove = checkValidMove(move);
        if (validMove) {
            break;
        }
    }
    player.makeMove(move);
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
}