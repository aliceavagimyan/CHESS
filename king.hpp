#ifndef  KING_HPP
#define  KING_HPP
#include "figure.hpp"

class King : public Piece {
public:
    King(int x, int y, Color color) : Piece(x, y, color) {}
  
    bool isValidMove(int x, int y, Piece* board[8][8]) override;
      std::string getSymbol() const override { return "K"; }
     //  King(const King& other) : Piece(other.x, other.y, other.color) {}
   
};
#endif // KING_HPP