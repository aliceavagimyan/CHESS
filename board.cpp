#include "board.hpp"
#include <algorithm>
#include <typeinfo>
Board::Board() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            board[i][j] = nullptr;
}
Board::~Board() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            delete board[i][j];
}

void Board::addPiece(Piece* piece) {
    int x = piece->getX();
    int y = piece->getY();

    
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        std::cout << "Error: Invalid coordinates (" << x << ", " << y << "). Piece not added." << std::endl;
        delete piece;
        return;
    }

    if (dynamic_cast<King*>(piece)) {
        int kingCount = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr && dynamic_cast<King*>(board[i][j])) {
                    kingCount++;
                }
            }
        }
        if (kingCount >= 2) {
            std::cout << "Error: More than two kings on the board. Piece not added." << std::endl;
            delete piece;
            return;
        }
    }

    
    board[x][y] = piece;
}

bool Board::isCheck(Color color) {
    
    int kingX, kingY;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->getColor() == color) {
                if (dynamic_cast<King*>(board[i][j])) {
                    kingX = i;
                    kingY = j;
                }
            }
        }
    }

    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->getColor() != color) {
                if (board[i][j]->isValidMove(kingX, kingY, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(Color color) {
    if (!isCheck(color)) return false;


    int kingX, kingY;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->getColor() == color) {
                if (dynamic_cast<King*>(board[i][j])) {
                    kingX = i;
                    kingY = j;
                }
            }
        }
    }

    
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; ++i) {
        int newX = kingX + dx[i];
        int newY = kingY + dy[i];
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            Piece* originalPiece = board[newX][newY];
            board[newX][newY] = board[kingX][kingY];
            board[kingX][kingY] = nullptr;

            bool check = isCheck(color);

            board[kingX][kingY] = board[newX][newY];
            board[newX][newY] = originalPiece;

            if (!check) {
                return false;
            }
        }
    }

    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->getColor() == color) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        if (board[i][j]->isValidMove(x, y, board)) {
                            Piece* originalPiece = board[x][y];
                            board[x][y] = board[i][j];
                            board[i][j] = nullptr;

                            bool check = isCheck(color);

                            board[i][j] = board[x][y];
                            board[x][y] = originalPiece;

                            if (!check) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}
void Board::printBoard() {
    char symbols[] = {'R', 'N', 'B', 'Q', 'K', 'P', '.', '.'};
    char colors[] = {'W', 'B'};

    std::cout << "   a  b  c  d  e  f  g  h\n";
    for (int i = 7; i >= 0; --i) {
        std::cout << i + 1 << ' ';
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece == nullptr) {
                std::cout << " . ";
            } else {
                char symbol = ' ';
                if (dynamic_cast<Rook*>(piece)) symbol = 'R';
                else if (dynamic_cast<Knight*>(piece)) symbol = 'N';
                else if (dynamic_cast<Bishop*>(piece)) symbol = 'B';
                else if (dynamic_cast<Queen*>(piece)) symbol = 'Q';
                else if (dynamic_cast<King*>(piece)) symbol = 'K';
                else if (dynamic_cast<Pawn*>(piece)) symbol = 'P';

                std::cout << symbol << (piece->getColor() == WHITE ? 'W' : 'B') << ' ';
            }
        }
        std::cout << i + 1 << '\n';
    }
    std::cout << "   a  b  c  d  e  f  g  h\n";

    
    int kingCount = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && dynamic_cast<King*>(board[i][j])) {
                kingCount++;
            }
        }
    }
    if (kingCount != 2) {
        std::cout << "Warning: There should be exactly two kings on the board. Found " << kingCount << "." << std::endl;
    }

    if (areKingsAdjacent()) {
        std::cout << "Warning: Two kings are adjacent, which is not allowed." << std::endl;
    }
}

bool Board::areKingsAdjacent() {
    int kingPositions[2][2] = { {-1, -1}, {-1, -1} };
    int kingCount = 0;

  
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece != nullptr && dynamic_cast<King*>(piece)) {
                if (kingCount < 2) {
                    kingPositions[kingCount][0] = i;
                    kingPositions[kingCount][1] = j;
                    kingCount++;
                }
            }
        }
    }

    
    if (kingCount == 2) {
        int dx = std::abs(kingPositions[0][0] - kingPositions[1][0]);
        int dy = std::abs(kingPositions[0][1] - kingPositions[1][1]);
        return (dx <= 1 && dy <= 1);
    }

    return false;
}  

bool Board::isCheckmateInOneMove(Color color) {
   
    Color opponentColor = (color == WHITE) ? BLACK : WHITE;

    
    if (isCheckmate(opponentColor)) {
        std::cout << "The opponent is already in checkmate." << std::endl;
        return false; 
    }

    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->getColor() == color) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        if (piece->isValidMove(x, y, board)) {
                            
                            Piece* originalPiece = board[x][y];
                            board[x][y] = piece;
                            board[i][j] = nullptr;
                            piece->setPosition(x, y);

                            
                            if (isCheckmate(opponentColor) && !areKingsAdjacent()) {
                                std::cout << "Move: from (" << i << ", " << j << ") to (" << x << ", " << y << ") results in checkmate." << std::endl;
                                
                                
                                printBoard();
                                
                               
                                board[i][j] = piece;
                                board[x][y] = originalPiece;
                                piece->setPosition(i, j);
                                return true;
                            }

                            
                            board[i][j] = piece;
                            board[x][y] = originalPiece;
                            piece->setPosition(i, j);
                        }
                    }
                }
            }
        }
    }

    std::cout << "No checkmate in one move found for " << (color == WHITE ? "White" : "Black") << "." << std::endl;
    return false;
}

bool Board::isCheckmateInTwoMoves(Color color) {
    Color opponentColor = (color == WHITE) ? BLACK : WHITE;

   
    if (isCheckmate(opponentColor)) {
        std::cout << "The opponent is already in checkmate." << std::endl;
        return false; 
    }
    
   
    if (isCheckmateInOneMove(opponentColor)) {
        std::cout << "Checkmate in one move is possible." << std::endl;
        return false; 
    }

    bool checkmateFound = false;

   
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->getColor() == color) {
               
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        if (piece->isValidMove(x, y, board) && isInsideBoard(x, y)) {
                           
                            Piece* originalPiece = board[x][y];
                            board[x][y] = piece;
                            board[i][j] = nullptr;
                            int originalX = piece->getX();
                            int originalY = piece->getY();
                            piece->setPosition(x, y);

                           
                            for (int k = 0; k < 8; ++k) {
                                for (int l = 0; l < 8; ++l) {
                                    Piece* blackPiece = board[k][l];
                                    if (blackPiece && blackPiece->getColor() == opponentColor && dynamic_cast<King*>(blackPiece)) {
                                        
                                        for (int m = 0; m < 8; ++m) {
                                            for (int n = 0; n < 8; ++n) {
                                                if (blackPiece->isValidMove(m, n, board) && isInsideBoard(m, n)) {
                                                    if (isUnderAttack(m, n, color)) {
                                                        continue;
                                                    }

                                                
                                                    Piece* originalKing = board[k][l];
                                                    Piece* targetPiece = board[m][n];
                                                    board[m][n] = blackPiece;
                                                    board[k][l] = nullptr;
                                                    int originalKingX = blackPiece->getX();
                                                    int originalKingY = blackPiece->getY();
                                                    blackPiece->setPosition(m, n);

                                                   
                                                    for (int p = 0; p < 8; ++p) {
                                                        for (int q = 0; q < 8; ++q) {
                                                            Piece* finalPiece = board[p][q];
                                                            if (finalPiece && finalPiece->getColor() == color) {
                                                                for (int r = 0; r < 8; ++r) {
                                                                    for (int s = 0; s < 8; ++s) {
                                                                        if (finalPiece->isValidMove(r, s, board) && isInsideBoard(r, s)) {
                                                                           
                                                                            Piece* finalOriginalPiece = board[r][s];
                                                                            board[r][s] = finalPiece;
                                                                            board[p][q] = nullptr;
                                                                            int finalOriginalX = finalPiece->getX();
                                                                            int finalOriginalY = finalPiece->getY();
                                                                            finalPiece->setPosition(r, s);

                                                                            if (isCheckmate(opponentColor)) {
                                                                                std::cout << "White moves from (" << i << ", " << j << ") to (" << x << ", " << y << ") " << std::endl;
                                                                                std::cout << "Black moves from (" << k << ", " << l << ") to (" << m << ", " << n << ") " << std::endl;
                                                                                std::cout << "White moves from (" << p << ", " << q << ") to (" << r << ", " << s << ") results in checkmate." << std::endl;
                                                                                printBoard();

                                                                                board[p][q] = finalOriginalPiece;
                                                                                board[r][s] = finalPiece;
                                                                                finalPiece->setPosition(finalOriginalX, finalOriginalY);
                                                                                board[k][l] = originalKing;
                                                                                board[m][n] = targetPiece;
                                                                                blackPiece->setPosition(originalKingX, originalKingY);
                                                                                board[i][j] = piece;
                                                                                board[x][y] = originalPiece;
                                                                                piece->setPosition(originalX, originalY);
                                                                                return true;
                                                                            }

                                                                            
                                                                            board[p][q] = finalPiece;
                                                                            board[r][s] = finalOriginalPiece;
                                                                            finalPiece->setPosition(finalOriginalX, finalOriginalY);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }

                                                   
                                                    board[k][l] = originalKing;
                                                    board[m][n] = targetPiece;
                                                    blackPiece->setPosition(originalKingX, originalKingY);
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            
                            board[i][j] = piece;
                            board[x][y] = originalPiece;
                            piece->setPosition(originalX, originalY);
                        }
                    }
                }
            }
        }
    }

    std::cout << "No checkmate in two moves found for " << (color == WHITE ? "White" : "Black") << "." << std::endl;
    return false;
}

bool Board::isInsideBoard(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

bool Board::isUnderAttack(int x, int y, Color color) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->getColor() == color && piece->isValidMove(x, y, board)) {
                return true;
            }
        }
    }
    return false;
}




int Board::countAttacks(int x, int y, Color color) {
    int attackCount = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->getColor() == color && piece->isValidMove(x, y, board)) {
                attackCount++;
            }
        }
    }
    return attackCount;
}

// // bool Board::isCheckmateInTwoMoves(Color color) {
// //     Color opponentColor = (color == WHITE) ? BLACK : WHITE;

// //     // Check if the opponent is already in checkmate
// //     if (isCheckmate(opponentColor)) {
// //         std::cout << "The opponent is already in checkmate." << std::endl;
// //         return false; // No need to search for two-move checkmate if checkmate already exists
// //     }

// //     // Check if there is a checkmate in one move
// //     if (isCheckmateInOneMove(opponentColor)) {
// //         std::cout << "Checkmate in one move." << std::endl;
// //         return false; // No need to search for two-move checkmate if checkmate already exists
// //     }

// //     // Iterate over all possible moves for the player
// //     for (int i = 0; i < 8; ++i) {
// //         for (int j = 0; j < 8; ++j) {
// //             Piece* piece = board[i][j];
// //             if (piece && piece->getColor() == color) {
// //                 for (int x = 0; x < 8; ++x) {
// //                     for (int y = 0; y < 8; ++y) {
// //                         if (piece->isValidMove(x, y, board) && isInsideBoard(x, y)) {
// //                             // Save the original state of the board and piece
// //                             Piece* originalPiece = board[x][y];
// //                             board[x][y] = piece;
// //                             board[i][j] = nullptr;
// //                             int originalX = piece->getX();
// //                             int originalY = piece->getY();
// //                             piece->setPosition(x, y);

// //                             bool allBlackKingMovesLeadToCheckmate = true;

// //                             // Iterate over all possible moves for the black king
// //                             for (int k = 0; k < 8; ++k) {
// //                                 for (int l = 0; l < 8; ++l) {
// //                                     Piece* blackPiece = board[k][l];
// //                                     if (blackPiece && blackPiece->getColor() == opponentColor && dynamic_cast<King*>(blackPiece)) {
// //                                         // Try all possible moves for the black king
// //                                         bool blackKingHasValidMove = false;
// //                                         for (int m = 0; m < 8; ++m) {
// //                                             for (int n = 0; n < 8; ++n) {
// //                                                 if (blackPiece->isValidMove(m, n, board) && isInsideBoard(m, n)) {
// //                                                     // Check if the black king would be under attack
// //                                                     if (isUnderAttack(m, n, color)) {
// //                                                         continue;
// //                                                     }

// //                                                     // Save the original state of the black king
// //                                                     Piece* originalKing = board[k][l];
// //                                                     Piece* targetPiece = board[m][n];
// //                                                     board[m][n] = blackPiece;
// //                                                     board[k][l] = nullptr;
// //                                                     int originalKingX = blackPiece->getX();
// //                                                     int originalKingY = blackPiece->getY();
// //                                                     blackPiece->setPosition(m, n);

// //                                                     // Check if White can deliver checkmate in one move after black king's move
// //                                                     bool canCheckmate = false;
// //                                                     std::string checkmateSteps;
// //                                                     for (int p = 0; p < 8; ++p) {
// //                                                         for (int q = 0; q < 8; ++q) {
// //                                                             Piece* finalPiece = board[p][q];
// //                                                             if (finalPiece && finalPiece->getColor() == color) {
// //                                                                 for (int r = 0; r < 8; ++r) {
// //                                                                     for (int s = 0; s < 8; ++s) {
// //                                                                         if (finalPiece->isValidMove(r, s, board) && isInsideBoard(r, s)) {
// //                                                                             // Save the state of the board and piece
// //                                                                             Piece* finalOriginalPiece = board[r][s];
// //                                                                             board[r][s] = finalPiece;
// //                                                                             board[p][q] = nullptr;
// //                                                                             int finalOriginalX = finalPiece->getX();
// //                                                                             int finalOriginalY = finalPiece->getY();
// //                                                                             finalPiece->setPosition(r, s);

// //                                                                             // Check if the move results in checkmate
// //                                                                             if (isCheckmate(opponentColor)) {
// //                                                                                 canCheckmate = true;
// //                                                                                 checkmateSteps = "White moves from (" + std::to_string(i) + ", " + std::to_string(j) + ") to (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
// //                                                                                 checkmateSteps += "Black moves from (" + std::to_string(k) + ", " + std::to_string(l) + ") to (" + std::to_string(m) + ", " + std::to_string(n) + ").\n";
// //                                                                                 checkmateSteps += "White moves from (" + std::to_string(p) + ", " + std::to_string(q) + ") to (" + std::to_string(r) + ", " + std::to_string(s) + ") results in checkmate.\n";

// //                                                                                 // Restore the board state
// //                                                                                 board[p][q] = finalOriginalPiece;
// //                                                                                 board[r][s] = finalPiece;
// //                                                                                 finalPiece->setPosition(finalOriginalX, finalOriginalY);
// //                                                                                 break;
// //                                                                             }

// //                                                                             // Restore the board state
// //                                                                             board[p][q] = finalPiece;
// //                                                                             board[r][s] = finalOriginalPiece;
// //                                                                             finalPiece->setPosition(finalOriginalX, finalOriginalY);
// //                                                                         }
// //                                                                     }
// //                                                                     if (canCheckmate) break;
// //                                                                 }
// //                                                             }
// //                                                             if (canCheckmate) break;
// //                                                         }
// //                                                         if (canCheckmate) break;
// //                                                     }

// //                                                     // Restore the board state
// //                                                     board[k][l] = originalKing;
// //                                                     board[m][n] = targetPiece;
// //                                                     blackPiece->setPosition(originalKingX, originalKingY);

// //                                                     if (!canCheckmate) {
// //                                                         blackKingHasValidMove = true;
// //                                                         break;
// //                                                     } else {
// //                                                         // Print the recorded checkmate steps
// //                                                         std::cout << checkmateSteps << std::endl;
// //                                                     }
// //                                                 }
// //                                             }
// //                                             if (blackKingHasValidMove) break;
// //                                         }

// //                                         if (!blackKingHasValidMove) {
// //                                             // All moves of the black king lead to checkmate
// //                                             std::cout << "White moves from (" << i << ", " << j << ") to (" << x << ", " << y << ") results in a checkmate in two moves." << std::endl;
// //                                             printBoard();
// //                                             return true;
// //                                         }
// //                                     }
// //                                 }
// //                             }

// //                             // Restore the board state and piece
// //                             board[i][j] = piece;
// //                             board[x][y] = originalPiece;
// //                             piece->setPosition(originalX, originalY);
// //                         }
// //                     }
// //                 }
// //             }
// //         }
// //     }

// //     std::cout << "No checkmate in two moves found for " << (color == WHITE ? "White" : "Black") << "." << std::endl;
// //     return false;
// // }

// // Helper function to check if the position is within the board boundaries
// // bool Board::isInsideBoard(int x, int y) {
// //     return x >= 0 && x < 8 && y >= 0 && y < 8;
// // }

// // // Helper function to check if a position is under attack by any piece of a given color
// // bool Board::isUnderAttack(int x, int y, Color color) {
// //     for (int i = 0; i < 8; ++i) {
// //         for (int j = 0; j < 8; ++j) {
// //             Piece* piece = board[i][j];
// //             if (piece && piece->getColor() == color && piece->isValidMove(x, y, board)) {
// //                 return true;
// //             }
// //         }
// //     }
// //     return false;
// // }bool Board::isCheckmateInTwoMoves(Color color) {
// //     Color opponentColor = (color == WHITE) ? BLACK : WHITE;

// //     // Check if the opponent is already in checkmate
// //     if (isCheckmate(opponentColor)) {
// //         std::cout << "The opponent is already in checkmate." << std::endl;
// //         return false; // No need to search for two-move checkmate if checkmate already exists
// //     }

// //     // Check if there is a checkmate in one move
// //     if (isCheckmateInOneMove(opponentColor)) {
// //         std::cout << "Checkmate in one move." << std::endl;
// //         return false; // No need to search for two-move checkmate if checkmate already exists
// //     }

// //     bool checkmateFound = false;

// //     // Iterate over all possible moves for the player
// //     for (int i = 0; i < 8; ++i) {
// //         for (int j = 0; j < 8; ++j) {
// //             Piece* piece = board[i][j];
// //             if (piece && piece->getColor() == color) {
// //                 // Try moving the piece to all possible positions
// //                 for (int x = 0; x < 8; ++x) {
// //                     for (int y = 0; y < 8; ++y) {
// //                         if (piece->isValidMove(x, y, board) && isInsideBoard(x, y)) {
// //                             // Save the original state of the board and piece
// //                             Piece* originalPiece = board[x][y];
// //                             board[x][y] = piece;
// //                             board[i][j] = nullptr;
// //                             int originalX = piece->getX();
// //                             int originalY = piece->getY();
// //                             piece->setPosition(x, y);

// //                             bool allBlackKingMovesLeadToCheckmate = true;

// //                             // Iterate over all possible moves for the black king
// //                             for (int k = 0; k < 8; ++k) {
// //                                 for (int l = 0; l < 8; ++l) {
// //                                     Piece* blackPiece = board[k][l];
// //                                     if (blackPiece && blackPiece->getColor() == opponentColor && dynamic_cast<King*>(blackPiece)) {
// //                                         // Print black king's position
// //                                         std::cout << "Black King at: (" << k << ", " << l << ")" << std::endl;
                                        
// //                                         // Try all possible moves for the black king
// //                                         bool blackKingHasValidMove = false;
// //                                         for (int m = 0; m < 8; ++m) {
// //                                             for (int n = 0; n < 8; ++n) {
// //                                                 if (blackPiece->isValidMove(m, n, board) && isInsideBoard(m, n)) {
// //                                                     // Print each move of the black king
// //                                                     std::cout << "Black King tries move to: (" << m << ", " << n << ")" << std::endl;

// //                                                     // Check if the black king would be under attack
// //                                                     if (isUnderAttack(m, n, color)) {
// //                                                         std::cout << "Move to (" << m << ", " << n << ") is under attack, skipping." << std::endl;
// //                                                         continue;
// //                                                     }

// //                                                     // Save the original state of the black king
// //                                                     Piece* originalKing = board[k][l];
// //                                                     Piece* targetPiece = board[m][n];
// //                                                     board[m][n] = blackPiece;
// //                                                     board[k][l] = nullptr;
// //                                                     int originalKingX = blackPiece->getX();
// //                                                     int originalKingY = blackPiece->getY();
// //                                                     blackPiece->setPosition(m, n);

// //                                                     // Check if White can deliver checkmate in one move after black king's move
// //                                                     bool canCheckmate = false;
// //                                                     for (int p = 0; p < 8; ++p) {
// //                                                         for (int q = 0; q < 8; ++q) {
// //                                                             Piece* finalPiece = board[p][q];
// //                                                             if (finalPiece && finalPiece->getColor() == color) {
// //                                                                 for (int r = 0; r < 8; ++r) {
// //                                                                     for (int s = 0; s < 8; ++s) {
// //                                                                         if (finalPiece->isValidMove(r, s, board) && isInsideBoard(r, s)) {
// //                                                                             // Save the state of the board and piece
// //                                                                             Piece* finalOriginalPiece = board[r][s];
// //                                                                             board[r][s] = finalPiece;
// //                                                                             board[p][q] = nullptr;
// //                                                                             int finalOriginalX = finalPiece->getX();
// //                                                                             int finalOriginalY = finalPiece->getY();
// //                                                                             finalPiece->setPosition(r, s);

// //                                                                             // Check if the move results in checkmate
// //                                                                             if (isCheckmate(opponentColor)) {
// //                                                                                 canCheckmate = true;

// //                                                                                 // Restore the board state
// //                                                                                 board[p][q] = finalOriginalPiece;
// //                                                                                 board[r][s] = finalPiece;
// //                                                                                 finalPiece->setPosition(finalOriginalX, finalOriginalY);
// //                                                                                 break;
// //                                                                             }

// //                                                                             // Restore the board state
// //                                                                             board[p][q] = finalPiece;
// //                                                                             board[r][s] = finalOriginalPiece;
// //                                                                             finalPiece->setPosition(finalOriginalX, finalOriginalY);
// //                                                                         }
// //                                                                     }
// //                                                                     if (canCheckmate) break;
// //                                                                 }
// //                                                             }
// //                                                             if (canCheckmate) break;
// //                                                         }
// //                                                         if (canCheckmate) break;
// //                                                     }

// //                                                     // Restore the board state
// //                                                     board[k][l] = originalKing;
// //                                                     board[m][n] = targetPiece;
// //                                                     blackPiece->setPosition(originalKingX, originalKingY);

// //                                                     if (!canCheckmate) {
// //                                                         blackKingHasValidMove = true;
// //                                                         break;
// //                                                     }
// //                                                 }
// //                                             }
// //                                             if (blackKingHasValidMove) break;
// //                                         }

// //                                         if (!blackKingHasValidMove) {
// //                                             // All moves of the black king lead to checkmate
// //                                             std::cout << "White move from (" << i << ", " << j << ") to (" << x << ", " << y << ") results in a checkmate in two moves." << std::endl;
// //                                             printBoard();
// //                                             return true;
// //                                         }
// //                                     }
// //                                 }
// //                             }

// //                             // Restore the board state and piece
// //                             board[i][j] = piece;
// //                             board[x][y] = originalPiece;
// //                             piece->setPosition(originalX, originalY);
// //                         }
// //                     }
// //                 }
// //             }
// //         }
// //     }

// //     std::cout << "No checkmate in two moves found for " << (color == WHITE ? "White" : "Black") << "." << std::endl;
// //     return false;
// // }