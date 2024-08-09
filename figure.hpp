#ifndef PIECE_H
#define PIECE_H
#include <cmath>
#include <vector>
#include <string>

enum Color { WHITE, BLACK };

class Piece {
protected:
    int x, y;
    Color color;
public:
    Piece(int x, int y, Color color) : x(x), y(y), color(color) {}
    //Piece(const Piece& other) : x(other.x), y(other.y), color(other.color) {}
    virtual ~Piece() {}
    Color getColor() { return color; }
     Color getColor()const { return color; }
    virtual bool isValidMove(int x, int y, Piece* board[8][8]) = 0;
      int getX() const { return x; }
    int getY() const { return y; }
    virtual std::string getSymbol() const=0;
    void setPosition(int x, int y) { this->x = x; this->y = y; }
    
};
#endif //Piece