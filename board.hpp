#ifndef BOARD_HPP
#define BOARD_HPP
#include <iostream>
#include <string>
#include <vector>


#include "figure.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "pawn.hpp"
#include "knight.hpp"


class Board {
    Piece* board[8][8];

public:
    Board();
    Board(const Board& other);
    Board& operator=(const Board& other);
    ~Board();
    void addPiece(Piece* piece);
    bool isCheck(Color color);
    bool isCheckmate(Color color);
     void printBoard();
     bool areKingsAdjacent();
     bool isCheckmateInOneMove(Color color);
     bool isCheckmateInTwoMoves(Color color);
     
     bool isInsideBoard(int x, int y);
     bool isUnderAttack(int x, int y, Color color);
     int countAttacks(int x, int y, Color color);
};

#endif //