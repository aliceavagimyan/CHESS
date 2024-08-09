#ifndef  ROOK_HPP
#define  ROOK_HPP
#include "figure.hpp"

class Rook : public Piece {
public:
    Rook(int x, int y, Color color) : Piece(x, y, color) {}
     std::string getSymbol() const override { return "R"; }
    bool isValidMove(int x, int y, Piece* board[8][8]) override;
};
#endif //ROOK_CPP