#ifndef Pawn_H
#define Pawn_H

#include "../ChessPiece.h"
#include "../ChessBoard.h"

class Pawn : public ChessPiece {
private:
  bool captureValid (int to_x, int to_y) const;
  bool oneStepValid (int to_x, int to_y) const;
  bool doubleStepValid (int to_x, int to_y) const;
protected:
  int validMove(int to_x, int to_y);
  char32_t utfRepresentation();
  char latin1Representation();

public:
  Pawn(int row, int col, bool isWhite, ChessBoard* board):
                      ChessPiece(row, col, isWhite, board){}

};

#endif
