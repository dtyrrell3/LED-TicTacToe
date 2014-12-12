#include "Game.h"

Game::Game(Adafruit_NeoPixel *strip1) {
    strip = strip1;
    strip->setPixelColor(0, 150, 0, 0);
    color0 = strip->Color(100, 0, 0);
    color1 = strip->Color(0, 0, 100);
    board = new Board(strip);
    player0 = new Player(board, color0);
    player1 = new Player(board, color1);
    playerWon = false;
    gameDraw = false;
    for (int i = 0; i < 4; i++) {
        winningTiles[i] = 0;
    }
}

Game::~Game() {
    delete(board);
    delete(player0);
    delete(player1);
}

void Game::play() {
    board->reset();
    while(!playerWon && !gameDraw) {
        takeTurn(player0);
        if (playerWon || gameDraw) {
            break;
        }
        takeTurn(player1);
    }
    delay(2500); // Delay 2.5 seconds before victory sequence
    if (playerWon) {
        board->victory(&winningTiles[0], winningColor);    
    } else if (gameDraw) {
        // Nobody won.
        board->reset();
        board->draw();
    }

    board->reset();
    playerWon = false;
    gameDraw = false;
    for (int i = 0; i < 4; i++) {
        winningTiles[i] = 0;
    }
}

void Game::takeTurn(Player *player) {
    boolean validMove = false;
    byte move;
    while (!validMove) {
        move = player->getMove();
        delay(250);
        validMove = checkValidMove(move);
        if (validMove) {
            break;
        }
    }
    player->makeMove(move);
    achievedVictory();
}

boolean Game::checkValidMove(byte numTile) {
    if (board->boardState[numTile]) {
        return false;
    }
    return true;
}

void Game::achievedVictory() {
    /* Check columns. */
    uint32_t color;
    for (byte i = 0; i < 4; i++) {
        color = board->getColorTile(i);
        if (color == board->getColorTile(i+4)
            && board->getColorTile(i+4) == board->getColorTile(i+8)
            && board->getColorTile(i+8) == board->getColorTile(i+12)
            && (color == color0 || color == color1)) {
            winningTiles[0] = i;
            winningTiles[1] = i + 4;
            winningTiles[2] = i + 8;
            winningTiles[3] = i + 12;
            playerWon = true;
            if (color == color0) {
                winningColor = strip->Color(255, 0, 0);
            } else {
                winningColor = strip->Color(0, 0, 255);
            }
            return;
        }
    }
    /* Check rows. */
    for (byte i = 0; i < 4; i++) {
        byte j = 4*i;
        color = board->getColorTile(j);
        if (color == board->getColorTile(j+1)
            && board->getColorTile(j+1) == board->getColorTile(j+2)
            && board->getColorTile(j+2) == board->getColorTile(j+3)
            && (color == color0 || color == color1)) {
            winningTiles[0] = j;
            winningTiles[1] = j + 1;
            winningTiles[2] = j + 2;
            winningTiles[3] = j + 3;
            playerWon = true;
            if (color == color0) {
                winningColor = strip->Color(255, 0, 0);
            } else {
                winningColor = strip->Color(0, 0, 255);
            }
            return;
        }
    }
    /* Check diagonals. */
    color = board->getColorTile(0);
    if (color == board->getColorTile(5)
        && board->getColorTile(5) == board->getColorTile(10)
        && board->getColorTile(10) == board->getColorTile(15)
        && (color == color0 || color == color1)) {
        winningTiles[0] = 0;
        winningTiles[1] = 5;
        winningTiles[2] = 10;
        winningTiles[3] = 15;
        playerWon = true;
        if (color == color0) {
                winningColor = strip->Color(255, 0, 0);
            } else {
                winningColor = strip->Color(0, 0, 255);
            }
        return;
    }
    color = board->getColorTile(3);
    if (color == board->getColorTile(6)
        && board->getColorTile(6) == board->getColorTile(9)
        && board->getColorTile(9) == board->getColorTile(12)
        && (color == color0 || color == color1)) {
        winningTiles[0] = 3;
        winningTiles[1] = 6;
        winningTiles[2] = 9;
        winningTiles[3] = 12;
        playerWon = true;
        if (color == color0) {
                winningColor = strip->Color(255, 0, 0);
            } else {
                winningColor = strip->Color(0, 0, 255);
            }
        return;
    }
    /* If board is filled up, it's a draw. */
    for (byte i = 0; i < BOARD_SIZE; i++) {
        if (board->boardState[i] == 0) {
            return;
        }
    }
    gameDraw = true;
}