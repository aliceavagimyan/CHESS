#ifndef  PAWN_HPP
#define   PAWN_HPP
#include "figure.hpp"

class Pawn : public Piece {
public:
    Pawn(int x, int y, Color color) : Piece(x, y, color) {}
    bool isValidMove(int x, int y, Piece* board[8][8]) override;
      std::string getSymbol() const override { return "P"; }
      
   // Pawn(const Pawn& other) : Piece(other.x, other.y, other.color) {}
 
};
#endif //  PAWN_HPP