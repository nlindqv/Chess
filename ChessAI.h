#ifndef CHESS_AI_H
#define CHESS_AI_H

#include "ChessBoard.h"
#include "ChessPiece.h"
#include "ChessMove.h"

typedef int AI_type;

class ChessAI {
  private:
    bool isWhite;
    AI_type AI;

    ChessPiece* newPiece(char c, int x, int y, ChessBoard& chess);

  public:

    bool pawnPromotion = false;

    ChessAI(bool color, int ai): isWhite(color), AI(ai) {}

    ChessMove getNextMove(ChessBoard& chess);
    char getPawnPromotion(ChessBoard& chess, ChessMove& move);
};

#endif
