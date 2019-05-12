#include "King.h"

using std::vector;

int King::validMove(int to_x, int to_y){
  int delta_x = abs(x - to_x);
  int delta_y = abs(y - to_y);
  if (delta_x * delta_y == 1 || delta_x + delta_y == 1){
    if (board->getState(to_x, to_y) && board->getState(to_x, to_y)->getIsWhite() != isWhite /* or can be captured */ )
      return 2;
    else if (!board->getState(to_x, to_y))
      return 1;
  }
  return 0;
}

char32_t King::utfRepresentation(){
  if (isWhite) return U'♔';
  else return U'♚';
}
char King::latin1Representation(){
  if (isWhite) return 'K';
  else return 'k';
}
