
#include "Queen.h"
#include "../ChessMove.h"
using std::vector;

int Queen::validMove(int to_x, int to_y){
  return Bishop::validMove(to_x, to_y) > Rook::validMove(to_x, to_y) ?
         Bishop::validMove(to_x, to_y) : Rook::validMove(to_x, to_y);
}

char32_t Queen::utfRepresentation(){
  if (isWhite) return U'♕';
  else return U'♛';
}
char Queen::latin1Representation(){
  if (isWhite) return 'Q';
  else return 'q';
}
