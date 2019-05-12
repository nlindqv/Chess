#include <random>
#include <chrono>
#include "ChessAI.h"
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "ChessMove.h"
#include "ChessPieces/Knight.h"
#include "ChessPieces/Bishop.h"
#include "ChessPieces/Rook.h"
#include "ChessPieces/Queen.h"

ChessMove ChessAI::getNextMove(ChessBoard& chess){
  pawnPromotion = false;
  // Collect all capturing moves
  std::vector<ChessMove> v = chess.capturingMoves(isWhite);
  if (v.size() == 0){
    // If none, collect all non capturing moves
    v = chess.nonCapturingMoves(isWhite);
  }
  if (AI == 2){
    for (int i = 0; i < v.size(); i++){
      // Simulate move and calculate next players capturing moves on that square
      ChessBoard newBoard(chess);
      ChessMove newMove(v[i]);
      newMove.piece = newBoard.setState(newMove.from_x, newMove.from_y);
      newBoard.move_piece(newMove);
      vector<ChessMove> candidates = newBoard.capturingMoves(!isWhite);
      for (int j = 0; j < candidates.size(); j++){
        if (candidates[j].to_x == v[i].to_x && candidates[j].to_y == v[i].to_y){
          if ((isWhite && v[i].to_x == 0 && v[i].piece->latin1Representation() == 'P') || (!isWhite && v[i].to_x == 7 && v[i].piece->latin1Representation() == 'p')){
            pawnPromotion = true;
          }
          return v[i];
        }
      }
    }
  }

  int index = 0;
  if (v.size() > 1){
    std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0,v.size()-1);
    index = dist(engine);
  }
  if ((isWhite && v[index].to_x == 0 && v[index].piece->latin1Representation() == 'P') || (!isWhite && v[index].to_x == 7 && v[index].piece->latin1Representation() == 'p')){
    pawnPromotion = true;
  }
  return v[index];  // generates number in the range 1.. v.size()
}


char ChessAI::getPawnPromotion(ChessBoard& chess, ChessMove& move){
  char pieces[4] = {'b', 'n', 'r', 'q'};
  int sizePieces = sizeof(pieces)/sizeof(char);

  if (AI == 2){
    for (int i = 0; i < sizePieces; i++) {
      ChessBoard testBoard(chess);
      testBoard.setState(move.from_x, move.from_y) = nullptr;
      testBoard.setState(move.to_x, move.to_y) = newPiece(pieces[i], move.to_x, move.to_y, testBoard);
      if (testBoard.setState(move.to_x, move.to_y)->capturingMoves().size() == 0){
        return pieces[i];
      }
    }
  }

  std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(0, sizePieces-1);
  return pieces[dist(engine)];
}



ChessPiece* ChessAI::newPiece(char c, int x, int y, ChessBoard& chess){
  ChessPiece* newP;
  switch (c){
    case 'b':
    newP = new Bishop(x, y, isWhite, &chess);
    break;
    case 'n':
    newP = new Knight(x, y, isWhite, &chess);
    break;
    case 'r':
    newP = new Rook(x, y, isWhite, &chess);
    break;
    case 'q':
    newP = new Queen(x, y, isWhite, &chess);
    break;
  }
  return newP;
}
