
#include "Knight.h"
#include "../ChessMove.h"
using std::vector;


int Knight::validMove(int to_x, int to_y){
  int delta_x = abs(x - to_x);
  int delta_y = abs(y - to_y);
  if (((delta_x*delta_x) + (delta_y*delta_y)) == 5){
    if (board->getState(to_x, to_y) && board->getState(to_x, to_y)->getIsWhite() != isWhite)
      return 2;
    else if (!board->getState(to_x, to_y))
      return 1;
  }
  return 0;
}

char32_t Knight::utfRepresentation(){
  if (isWhite) return U'♘';
  else return U'♞';
}
char Knight::latin1Representation(){
  if (isWhite) return 'N';
  else return 'n';
}
