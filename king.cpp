#include "king.hpp"

bool King::isValidMove(int x, int y, Piece* board[8][8]) {
    int dx = std::abs(this->x - x);
    int dy = std::abs(this->y - y);

    if ((dx <= 1 && dy <= 1) && (board[x][y] == nullptr || board[x][y]->getColor() != this->color)) {
        return true;
    }
    return false;
}
