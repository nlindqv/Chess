#include "Rook.h"
#include "../ChessMove.h"

using std::vector;

int Rook::validMove(int to_x, int to_y){
  int delta_x = abs(x - to_x);
  int delta_y = abs(y - to_y);
  if ((delta_x == 0 || delta_y == 0) && clearPath(to_x, to_y)){
    if (board->getState(to_x, to_y) && board->getState(to_x, to_y)->getIsWhite() != isWhite)
      return 2;
    else if (!board->getState(to_x, to_y) && !(delta_x == 0 && delta_y == 0))
      return 1;
  }
  return 0;
}

char32_t Rook::utfRepresentation(){
  if (isWhite) return U'♖';
  else return U'♜';
}
char Rook::latin1Representation(){
  if (isWhite) return 'R';
  else return 'r';
}

bool Rook::clearPath (int to_x, int to_y) const {
  int diff_x = x - to_x;
  int diff_y = y - to_y;

  if (diff_x == 0 && diff_y < 0){
    for (int i = 1; i < abs(diff_y); i++) {
      if (board->getState(x, y+i)){
        return false;
      }
    }
  }
  else if (diff_x == 0 && diff_y > 0){
    for (int i = 1; i < abs(diff_y); i++) {
      if (board->getState(x, y-i)){
        return false;
      }
    }
  }
  else if (diff_x < 0 && diff_y == 0){
    for (int i = 1; i < abs(diff_x); i++) {
      if (board->getState(x+i, y)){
        return false;
      }
    }
  }
  else if (diff_x > 0 && diff_y == 0){
    for (int i = 1; i < abs(diff_x); i++) {
      if (board->getState(x-i, y)){
        return false;
      }
    }
  }
  return true;
}
