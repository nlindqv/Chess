#ifndef ChessBoard_H
#define ChessBoard_H

#include <vector>
#include "Matris.h"

using std::vector;
class ChessPiece;
struct ChessMove;


class ChessBoard {
  friend ChessBoard& operator>> (std::istream&, ChessBoard&);
  friend std::ostream& operator<< (std::ostream&, const ChessBoard&);

private:
  unsigned boardSize;
  Matris<ChessPiece*> state; // Matris from lab 4  Matrix
  bool checkPawnPromotion(ChessMove chessMove) const;


public:
  bool utf = true;
  ChessBoard();
  ChessBoard(const ChessBoard&);
  ~ChessBoard();

  void move_piece(ChessMove chessMove);
  void move_piece(ChessMove chessMove, char c);
  vector<ChessMove> capturingMoves(bool isWhite);
  vector<ChessMove> nonCapturingMoves(bool isWhite);

  const ChessPiece* getState(int x, int y) const;
  ChessPiece*& setState(int x, int y);

 };


ChessBoard& operator>> (std::istream&, ChessBoard&);
std::ostream& operator<< (std::ostream&, const ChessBoard&);

#endif
