#ifndef Rook_H
#define Rook_H

#include "../ChessPiece.h"
#include "../ChessBoard.h"

class Rook : public virtual ChessPiece {
private:
  bool clearPath(int, int) const;

protected:
  int validMove(int to_x, int to_y) override;
  char32_t utfRepresentation() override;
  char latin1Representation() override;

public:
  Rook(int row, int col, bool isWhite, ChessBoard* board):
                      ChessPiece(row, col, isWhite, board){}

};

#endif
