#ifndef  KNIGHT_HPP
#define  KNIGHT_HPP
#include "figure.hpp"

class Knight : public Piece {
public:
    Knight(int x, int y, Color color) : Piece(x, y, color) {}
    bool isValidMove(int x, int y, Piece* board[8][8]) override;
      std::string getSymbol() const override { return "N"; }
      
  //  Knight(const Knight& other) : Piece(other.x, other.y, other.color) {}
    
};

#endif // KNIGHT_CPP