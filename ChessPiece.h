#ifndef ChessPiece_H
#define ChessPiece_H

#include <vector>
#include <iostream>
#include "ChessBoard.h"

struct ChessMove;

class ChessPiece {
  friend void ChessBoard::move_piece(ChessMove p);
protected:
  int x,y;
  bool isWhite;
  ChessBoard* board;
  /**
  * Returns 0 if target square is unreachable.
  * Returns 1 if target square is reachable and empty.
  * Returns 2 if move captures a piece.
  */
  virtual int validMove(int to_x, int to_y) = 0;

public:
  virtual char32_t utfRepresentation() = 0;
  virtual char latin1Representation() = 0;
  const bool getIsWhite() const;


  ChessPiece(int row, int col, bool white, ChessBoard* chessBoard): x(row), y(col), isWhite(white), board(chessBoard){}

  virtual ~ChessPiece() = default;

  /**
  * Checks if this move is valid for this piece and captures
  * a piece of the opposite color.
  */
  bool capturingMove(int to_x, int to_y);
  /**
  * Checks if this move is valid but does not capture a piece.
  */
  bool nonCapturingMove(int to_x, int to_y);
  virtual std::vector<ChessMove> capturingMoves();
  virtual std::vector<ChessMove> nonCapturingMoves();

  /**
  * For testing multiple inheritance
  */
  int unnecessaryInt;
};


#endif
