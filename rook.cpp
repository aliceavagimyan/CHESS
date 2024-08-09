#include "rook.hpp"
bool Rook::isValidMove(int x, int y, Piece* board[8][8]) {
    if (this->x == x || this->y == y) {
        int stepX = (x > this->x) ? 1 : ((x < this->x) ? -1 : 0);
        int stepY = (y > this->y) ? 1 : ((y < this->y) ? -1 : 0);
        for (int i = this->x + stepX, j = this->y + stepY; i != x || j != y; i += stepX, j += stepY) {
            if (board[i][j] != nullptr) return false;
        }
        return (board[x][y] == nullptr || board[x][y]->getColor() != this->color);
    }
    return false;
}