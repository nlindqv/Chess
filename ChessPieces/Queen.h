#ifndef Queen_H
#define Queen_H

#include "../ChessPiece.h"
#include "../ChessBoard.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Bishop, public Rook {
protected:
  int validMove(int to_x, int to_y) override;
  char32_t utfRepresentation() override;
  char latin1Representation() override;

public:
  Queen(int row, int col, bool isWhite, ChessBoard* board) :
                          ChessPiece(row, col, isWhite, board),
                          Bishop(row, col, isWhite, board),
                          Rook(row, col, isWhite, board) {}
};

#endif
