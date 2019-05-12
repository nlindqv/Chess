
#include "Pawn.h"
#include "../ChessMove.h"

using std::vector;

int Pawn::validMove(int to_x, int to_y){
  if (captureValid(to_x, to_y)){
    return 2;
  } else if (oneStepValid(to_x, to_y) || doubleStepValid(to_x, to_y)){
    return 1;
  } else {
    return 0;
  }
}

char32_t Pawn::utfRepresentation(){
  if (isWhite) return U'♙';
  else return U'♟';
}
char Pawn::latin1Representation(){
  if (isWhite) return 'P';
  else return 'p';
}

bool Pawn::doubleStepValid (int to_x, int to_y) const {
  if (isWhite){
    if (y == to_y && x == 6 && to_x == 4 && !board->getState(to_x, to_y) && !board->getState(to_x+1, to_y)){
      return true;
    } else {
      return false;
    }
  } else {
    if (y == to_y && x == 1 && to_x == 3 && !board->getState(to_x, to_y) && !board->getState(to_x-1, to_y)){
      return true;
    } else {
      return false;
    }
  }
}

bool Pawn::captureValid (int to_x, int to_y) const {
  int delta_y = abs(y - to_y);
  int diff_x = x - to_x;
  if (isWhite){
    if (delta_y == 1 && diff_x == 1 && board->getState(to_x, to_y) && !board->getState(to_x, to_y)->getIsWhite()){
      return true;
    }
  } else {
    if (delta_y == 1 && diff_x == -1 && board->getState(to_x, to_y) && board->getState(to_x, to_y)->getIsWhite()){
      return true;
    }
  }
  return false;
}

bool Pawn::oneStepValid (int to_x, int to_y) const {
  int diff_x = x - to_x;
  if (isWhite){
    if (y == to_y && diff_x == 1 && !board->getState(to_x, to_y)){
      return true;
    }
  } else {
    if (y == to_y && diff_x == -1 && !board->getState(to_x, to_y)){
      return true;
    }
  }
  return false;
}
