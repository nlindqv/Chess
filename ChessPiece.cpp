#include "ChessPiece.h"
#include "ChessBoard.h"
#include "ChessMove.h"

bool ChessPiece::capturingMove(int to_x, int to_y){
  // std::cout << "Piece::capMove: (" << x << ", " << y << ") to (" << to_x << ", " << to_y << ") got validMove: " << validMove(to_x, to_y) << std::endl;
  if (validMove(to_x, to_y) == 2){
    //std::cout << "Piece::capMove: (" << x << ", " << y << ") to (" << to_x << ", " << to_y << ") got validMove: " << validMove(to_x, to_y) << std::endl;
    return true;
  } else {
    return false;
  }
}

/**
 * Checks if this move is valid but does not capture a piece.
 */
bool ChessPiece::nonCapturingMove(int to_x, int to_y){
  if (validMove(to_x, to_y) == 1){
    //std::cout << "Piece::capMove: (" << x << ", " << y << ") to (" << to_x << ", " << to_y << ") got validMove: " << validMove(to_x, to_y) << std::endl;
    return true;
  } else {
    return false;
  }
}

vector<ChessMove> ChessPiece::capturingMoves(){
  vector<ChessMove> captureMoves;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++){
      if (capturingMove(i, j)) {
        ChessMove newMove(x, y, i, j, this);
        captureMoves.push_back(newMove);
      }
    }
  }
  return captureMoves;
}

vector<ChessMove> ChessPiece::nonCapturingMoves(){
  vector<ChessMove> nonCaptureMoves;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++){
      if (nonCapturingMove(i, j)) {
        ChessMove newMove(x, y, i, j, this);
        nonCaptureMoves.push_back(newMove);
      }
    }
  }
  return nonCaptureMoves;
}

const bool ChessPiece::getIsWhite() const {
  return isWhite;
}
