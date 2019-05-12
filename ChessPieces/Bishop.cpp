
#include "Bishop.h"
#include "../ChessMove.h"
using std::vector;

int Bishop::validMove(int to_x, int to_y){
  int delta_x = abs(x - to_x);
  int delta_y = abs(y - to_y);
  if (delta_x == delta_y && clearPath(to_x, to_y)){
    if (board->getState(to_x, to_y) && board->getState(to_x, to_y)->getIsWhite() != isWhite)
      return 2;
    else if (!board->getState(to_x, to_y))
      return 1;
  }
  return 0;
}

char32_t Bishop::utfRepresentation(){
  if (isWhite) return U'♗';
  else return U'♝';
}
char Bishop::latin1Representation(){
  if (isWhite) return 'B';
  else return 'b';
}

bool Bishop::clearPath (int to_x, int to_y) const{
  int diff_x = x - to_x;
  int diff_y = y - to_y;

  if (diff_x < 0 && diff_y < 0){
    for (int i = 1; i < abs(diff_x); i++) {
      if (board->getState(x+i, y+i)){
        return false;
      }
    }
  }
  else if (diff_x < 0 && diff_y > 0){
    for (int i = 1; i < abs(diff_x); i++) {
      if (board->getState(x+i, y-i)){
        return false;
      }
    }
  }
  else if (diff_x > 0 && diff_y < 0){
    for (int i = 1; i < abs(diff_x); i++) {
      if (board->getState(x-i, y+i)){
        return false;
      }
    }
  }
  else if (diff_x > 0 && diff_y > 0){
    for (int i = 1; i < abs(diff_x); i++) {
      if (board->getState(x-i, y-i)){
        return false;
      }
    }
  }
  return true;
}
