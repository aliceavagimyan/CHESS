#include "queen.hpp"
bool Queen::isValidMove(int x, int y, Piece* board[8][8]) {
    int dx = std::abs(this->x - x);
    int dy = std::abs(this->y - y);
    if (dx == dy || this->x == x || this->y == y) {
        int stepX = (x > this->x) ? 1 : ((x < this->x) ? -1 : 0);
        int stepY = (y > this->y) ? 1 : ((y < this->y) ? -1 : 0);
        for (int i = this->x + stepX, j = this->y + stepY; i != x || j != y; i += stepX, j += stepY) {
            if (board[i][j] != nullptr) return false;
        }
        return (board[x][y] == nullptr || board[x][y]->getColor() != this->color);
    }
    return false;
}