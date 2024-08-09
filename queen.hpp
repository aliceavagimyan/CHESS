#ifndef  QUEEN_HPP
#define  QUEEN_HPP
#include "figure.hpp"

class Queen : public Piece {
public:
    Queen(int x, int y, Color color) : Piece(x, y, color) {}
    bool isValidMove(int x, int y, Piece* board[8][8]) override;
      std::string getSymbol() const override { return "Q"; } 
    
};

#endif //QUEEN_CPP