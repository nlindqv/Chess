#ifndef King_H
#define King_H

#include "../ChessPiece.h"
#include "../ChessBoard.h"


class King : public ChessPiece {
protected:
  int validMove(int to_x, int to_y) override;
  char32_t utfRepresentation() override;
  char latin1Representation() override;

public:
  King(int row, int col, bool isWhite, ChessBoard* board):
                      ChessPiece(row, col, isWhite, board){}

};

#endif
