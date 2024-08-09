#include "bishop.hpp"

bool Bishop::isValidMove(int x, int y, Piece* board[8][8]) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) return false;
    
    int dx = abs(this->x - x);
    int dy = abs(this->y - y);
    if (dx == dy) {
        int stepX = (x > this->x) ? 1 : -1;
        int stepY = (y > this->y) ? 1 : -1;
        int currX = this->x + stepX;
        int currY = this->y + stepY;
        
        while (currX != x && currY != y) {
            if (board[currX][currY] != nullptr) return false;
            currX += stepX;
            currY += stepY;
        }
        return board[x][y] == nullptr || board[x][y]->getColor() != this->color;
    }
    return false;
}