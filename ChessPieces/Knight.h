#ifndef Knight_H
#define Knight_H

#include "../ChessPiece.h"
#include "../ChessBoard.h"

class Knight : public ChessPiece {
protected:
  int validMove(int to_x, int to_y);
  char32_t utfRepresentation();
  char latin1Representation();

public:
  Knight(int row, int col, bool isWhite, ChessBoard* board):
                        ChessPiece(row, col, isWhite, board){}

};

#endif
