#include "pawn.hpp"
bool Pawn::isValidMove(int x, int y, Piece *board[8][8])
{
    int dx = x - this->x;
    int dy = y - this->y;

    if (color == WHITE)
    {

        if (this->y == y && (dx == 1 || (this->x == 1 && dx == 2)))
        {

            if (dx == 2 && (board[this->x + 1][this->y] != nullptr || board[x][y] != nullptr))
                return false;
            if (board[x][y] == nullptr)
                return true;
        }

        if (abs(dy) == 1 && dx == 1 && board[x][y] != nullptr && board[x][y]->getColor() == BLACK)
            return true;
    }

    else
    {

        if (this->y == y && (dx == -1 || (this->x == 6 && dx == -2)))
        {

            if (dx == -2 && (board[this->x - 1][this->y] != nullptr || board[x][y] != nullptr))
                return false;
            if (board[x][y] == nullptr)
                return true;
        }

        if (abs(dy) == 1 && dx == -1 && board[x][y] != nullptr && board[x][y]->getColor() == WHITE)
            return true;
    }

    return false;
}
