#ifndef  BISHOP_HPP
#define  BISHOP_HPP
#include "figure.hpp"

class Bishop : public Piece {
public:
    Bishop(int x, int y, Color color) : Piece(x, y, color) {}
    bool isValidMove(int x, int y, Piece* board[8][8]) override;
      std::string getSymbol() const override { return "B"; }
       //Bishop(const Bishop& other) : Piece(other.x, other.y, other.color) {}
   
};
#endif // BISHOP_CPP