#include <iostream>
#include "board.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"

int main(){
  Board board;
  //  board.addPiece(new King(0, 1, WHITE));
  // board.addPiece(new King(0, 0, BLACK));
  // board.addPiece(new Queen(-1, 1, WHITE));
  // board.addPiece(new Rook(8, 4, BLACK));

  //     board.addPiece(new Bishop(1, 7, WHITE));
  //  board.addPiece(new King(5,1, WHITE));
  //     board.addPiece(new King(7,0, BLACK));
  //     board.addPiece(new Rook(6,1, WHITE));

  //  board.addPiece(new King(6, 5, WHITE));  // King on f7
  // board.addPiece(new King(0, 7, BLACK));  // King on h1
  // board.addPiece(new Rook(1, 1, WHITE));  // Rook on b2
  // board.addPiece(new Knight(2, 5, WHITE));// Knight on f3

  // board.addPiece(new King(0, 0, WHITE));
  //   board.addPiece(new King(5,7, BLACK));
  //   board.addPiece(new Queen(2, 6, WHITE));
  // board.addPiece(new Pawn(5, 5,WHITE));

  //  board.addPiece(new King(0, 0, WHITE));
  //     board.addPiece(new King(4,1, BLACK));
  //      board.addPiece(new Rook(6, 2, WHITE));
  //   board.addPiece(new Rook(7,3,WHITE));

  //    board.addPiece(new King(0, 0, WHITE));
  //   board.addPiece(new King(6,0, BLACK));
  //    board.addPiece(new Queen(3, 1, WHITE));
  // board.addPiece(new Rook(5, 4,WHITE));

  //    board.addPiece(new King(0, 0, WHITE));
  //   board.addPiece(new King(7,7, BLACK));
  //   board.addPiece(new Knight(4, 5,WHITE));
  //   board.addPiece(new Knight(6, 4, WHITE));
  //    board.addPiece(new Bishop(4, 3, WHITE));
  // board.addPiece(new Pawn(5, 6,WHITE));

  board.addPiece(new King(2, 0, WHITE));
  board.addPiece(new King(0, 0, BLACK));
  board.addPiece(new Queen(1, 7, WHITE));

  board.printBoard();
  // mate in two steps
  //  if (board.isCheckmateInTwoMoves(WHITE)) {
  //       std::cout << "White can force checkmate in two moves." << std::endl;
  //   } else {
  //       std::cout << "White cannot force checkmate in two moves." << std::endl;
  //   }
  // mate in one step
  if (board.isCheckmateInOneMove(WHITE)) {
      std::cout << "White can checkmate black in one move." << std::endl;
  } else {
      std::cout << "White cannot checkmate black in one move." << std::endl;
  }
  // cheking mate
  // if (board.isCheckmate(WHITE))
  // {
  //   std::cout << "White is in checkmate." << std::endl;
  // }
  // else if (board.isCheckmate(BLACK))
  // {
  //   std::cout << "Black is in checkmate." << std::endl;
  // }
  // else
  // {
  //   std::cout << "No checkmate." << std::endl;
  // }

  return 0;
}
