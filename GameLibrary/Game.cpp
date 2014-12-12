#include "Game.h"

Game::Game(Adafruit_NeoPixel *strip1) {
    strip = strip1;
    strip->setPixelColor(0, 150, 0, 0);
    color0 = strip->Color(100, 0, 0);
    color1 = strip->Color(0, 0, 100);
    // board = &Board(strip);
    // player0 = &Player(board, color0);
    // player1 = &Player(board, color1);
    board = new Board(strip);
    player0 = new Player(board, color0);
    player1 = new Player(board, color1);
    playerWon = false;
    gameDraw = false;
}

Game::~Game() {
    delete(board);
    delete(player0);
    delete(player1);
}

void Game::play() {
    // (*strip).setPixelColor(2, 150, 0, 0);
    board->reset();
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
    delay(2500); // Delay 5 seconds before victory sequence
    if (playerWon) {
        board->victory();    
    } else if (gameDraw) {
        // Nobody won.
    }
    board->reset();
}

void Game::takeTurn(Player *player) {
    Serial.println("Entering Taketurn");
    boolean validMove = false;
    byte move;
    while (!validMove) {
        move = player->getMove();
        delay(250);
        Serial.print("Received move ");
        Serial.println(move);
        validMove = checkValidMove(move);
        Serial.print("The move was ");
        Serial.println(validMove);
        if (validMove) {
            break;
        }
    }
    player->makeMove(move);
    Serial.print("Made move ");
    Serial.println(move);
    achievedVictory();
}

boolean Game::checkValidMove(byte numTile) {
    Serial.print("Entering check valid move on ");
    Serial.println(numTile);
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
            // strip->setPixelColor(0, 0, 100, 0);
            playerWon = true;
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
            // strip->setPixelColor(1, 0, 100, 0);
            playerWon = true;
            return;
        }
    }
    /* Check diagonals. */
    color = board->getColorTile(0);
    if (color == board->getColorTile(5)
        && board->getColorTile(5) == board->getColorTile(10)
        && board->getColorTile(10) == board->getColorTile(15)
        && (color == color0 || color == color1)) {
        // strip->setPixelColor(2, 0, 100, 0);
        playerWon = true;
        return;
    }
    color = board->getColorTile(3);
    if (color == board->getColorTile(6)
        && board->getColorTile(6) == board->getColorTile(9)
        && board->getColorTile(9) == board->getColorTile(12)
        && (color == color0 || color == color1)) {
        // strip->setPixelColor(3, 0, 100, 0);
        playerWon = true;
        return;
    }
    /* If board is filled up, it's a draw. */
    for (byte i = 0; i < BOARD_SIZE; i++) {
        if (!board->boardState[i]) {
            return;
        }
    }
    gameDraw = true;
}