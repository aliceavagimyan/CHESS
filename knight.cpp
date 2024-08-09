#include "knight.hpp"
bool Knight::isValidMove(int x, int y, Piece* board[8][8]) {
    int dx = std::abs(this->x - x);
    int dy = std::abs(this->y - y);
    return ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) && (board[x][y] == nullptr || board[x][y]->getColor() != this->color);
}