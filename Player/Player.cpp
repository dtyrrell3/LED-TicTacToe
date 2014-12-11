#include "Player.h"

Player::Player(Board board1, uint32_t color1) {
    board = board1;
    color = color1;
}

byte Player::getMove() {
    return board.getMove();
}

void Player::makeMove(byte numTile) {
    board.makeMove(numTile, color);
}