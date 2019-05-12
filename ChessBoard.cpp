#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "ChessMove.h"
#include "ChessPieces/King.h"
#include "ChessPieces/Knight.h"
#include "ChessPieces/Pawn.h"
#include "ChessPieces/Bishop.h"
#include "ChessPieces/Rook.h"
#include "ChessPieces/Queen.h"
#include <uchar.h>

ChessBoard::ChessBoard(): boardSize(8){
  state = Matris<ChessPiece*>(boardSize);
}

ChessBoard::ChessBoard(const ChessBoard& chess){
  state = Matris<ChessPiece*>(chess.boardSize);
  for (int i = 0; i < state.rows(); i++){
    for (int j = 0; j < state.cols(); j++){
      if (chess.state(i, j) != nullptr){
        switch (chess.state(i, j)->latin1Representation()){
          case 'K':
            state(i, j) = new King(i, j, true, this);
            break;
          case 'k':
            state(i, j) = new King(i, j, false, this);
            break;
          case 'N':
            state(i, j) = new Knight(i, j, true, this);
            break;
          case 'n':
            state(i, j) = new Knight(i, j, false, this);
            break;
          case 'P':
            state(i, j) = new Pawn(i, j, true, this);
            break;
          case 'p':
            state(i, j) = new Pawn(i, j, false, this);
            break;
          case 'B':
            state(i, j) = new Bishop(i, j, true, this);
            break;
          case 'b':
            state(i, j) = new Bishop(i, j, false, this);
            break;
          case 'R':
            state(i, j) = new Rook(i, j, true, this);
            break;
          case 'r':
            state(i, j) = new Rook(i, j, false, this);
            break;
          case 'Q':
            state(i, j) = new Queen(i, j, true, this);
            break;
          case 'q':
            state(i, j) = new Queen(i, j, false, this);
            break;
          default:
            break;
        }
      }
    }
  }
}


ChessBoard::~ChessBoard(){
  for (int i = 0; i < state.rows(); i++){
    for (int j = 0; j < state.cols(); j++){
      if (state(i, j) != nullptr){
        delete state(i, j);
        state(i, j) = nullptr;
      }
    }
  }
}

void ChessBoard::move_piece(ChessMove chessMove){
  if (chessMove.piece->board->state(chessMove.to_x, chessMove.to_y) != nullptr){
    delete chessMove.piece->board->state(chessMove.to_x, chessMove.to_y);
  }
  chessMove.piece->x = chessMove.to_x;
  chessMove.piece->y = chessMove.to_y;
  state(chessMove.to_x, chessMove.to_y) = chessMove.piece;
  state(chessMove.from_x, chessMove.from_y) = nullptr;
}

void ChessBoard::move_piece(ChessMove chessMove, char c){
  if (checkPawnPromotion(chessMove)){
    switch (c){
      case 'b':
        chessMove.piece = new Bishop(chessMove.to_x, chessMove.to_y, chessMove.piece->getIsWhite(), this);
        break;
      case 'n':
        chessMove.piece = new Knight(chessMove.to_x, chessMove.to_y, chessMove.piece->getIsWhite(), this);
        break;
      case 'r':
        chessMove.piece = new Rook(chessMove.to_x, chessMove.to_y, chessMove.piece->getIsWhite(), this);
        break;
      case 'q':
        chessMove.piece = new Queen(chessMove.to_x, chessMove.to_y, chessMove.piece->getIsWhite(), this);
        break;
    }
  }
  move_piece(chessMove);
}


bool ChessBoard::checkPawnPromotion(ChessMove chessMove) const {
  if (state(chessMove.from_x, chessMove.from_y)->latin1Representation() == 'P' && chessMove.to_x == 0){
    return true;
  } else if (state(chessMove.from_x, chessMove.from_y)->latin1Representation() == 'p' && chessMove.to_x == 7){
    return true;
  } else {
    return false;
  }
}

std::vector<ChessMove> ChessBoard::capturingMoves (bool isWhite){
  vector<ChessMove> capMoves;
  for (int i = 0; i < state.rows(); i++) {
    for (int j = 0; j < state.cols(); j++) {
      //std::cerr << "Board::capMoves: " << i << "," << j << std::endl;
      //if (state(i,j)) std::cerr << "Current Piece is white: " << state(i, j)->getIsWhite() << std::endl;
      if (state(i, j) && state(i, j)->getIsWhite() == isWhite){
        vector<ChessMove> moves = state(i, j)->capturingMoves();
        //std::cerr << "Piece " << state(i, j)->latin1Representation() << " (" << i << "," << j << ") got " << moves.size() << " non capture moves"<< std::endl;
        for (int k = 0; k < moves.size(); k++){
          capMoves.push_back(moves[k]);
        }
      }
    }
  }
  //std::cerr << "In total " << capMoves.size() << " capturing moves" << '\n';
  return capMoves;
}

std::vector<ChessMove> ChessBoard::nonCapturingMoves (bool isWhite){
  vector<ChessMove> nonCapMoves;
  for (int i = 0; i < state.rows(); i++) {
    for (int j = 0; j < state.cols(); j++) {
      //std::cerr << "Board::capMoves: " << i << "," << j << std::endl;
      //if (state(i,j)) std::cerr << "Current Piece is white: " << state(i, j)->getIsWhite() << std::endl;
      if (state(i, j) && state(i, j)->getIsWhite() == isWhite){
        vector<ChessMove> moves = state(i, j)->nonCapturingMoves();
        //std::cerr << "Piece " << state(i, j)->latin1Representation() << " (" << i << "," << j << ") got " << moves.size() << " non capture moves"<< std::endl;
        for (int k = 0; k < moves.size(); k++){
          nonCapMoves.push_back(moves[k]);
        }
      }
    }
  }
  //std::cerr << "In total " << nonCapMoves.size() << " non capturing moves" << '\n';
  return nonCapMoves;
}

const ChessPiece* ChessBoard::getState(int x, int y) const {
  return state(x, y);
}

ChessPiece*& ChessBoard::setState(int x, int y) {
  return state(x, y);
}

ChessBoard& operator>> (std::istream& is, ChessBoard& chessBoard){
  std::string line;
  int row = 0, col = 0;
  while (std::getline(is, line)) {
    for (auto it = line.begin(); it != line.end(); it++){
      if (*it != '.'){
        switch(*it){
        case 'K':
          chessBoard.state(row, col) = new King(row, col, true, &chessBoard);
          break;
        case 'k':
          chessBoard.state(row, col) = new King(row, col, false, &chessBoard);
          break;
        case 'N':
          chessBoard.state(row, col) = new Knight(row, col, true, &chessBoard);
          break;
        case 'n':
          chessBoard.state(row, col) = new Knight(row, col, false, &chessBoard);
          break;
        case 'P':
          chessBoard.state(row, col) = new Pawn(row, col, true, &chessBoard);
          break;
        case 'p':
          chessBoard.state(row, col) = new Pawn(row, col, false, &chessBoard);
          break;
        case 'B':
          chessBoard.state(row, col) = new Bishop(row, col, true, &chessBoard);
          break;
        case 'b':
          chessBoard.state(row, col) = new Bishop(row, col, false, &chessBoard);
          break;
        case 'R':
          chessBoard.state(row, col) = new Rook(row, col, true, &chessBoard);
          break;
        case 'r':
          chessBoard.state(row, col) = new Rook(row, col, false, &chessBoard);
          break;
        case 'Q':
          chessBoard.state(row, col) = new Queen(row, col, true, &chessBoard);
          break;
        case 'q':
          chessBoard.state(row, col) = new Queen(row, col, false, &chessBoard);
          break;
        default:
          break;
        }
      }
      col++;
    }
    row++;
    col = 0;
  }
  return chessBoard;
}

std::ostream& operator<< (std::ostream& os, const ChessBoard& chessBoard){
  for (int i = 0; i < chessBoard.state.rows(); i++){
    for (int j = 0; j < chessBoard.state.cols(); j++){
      if (chessBoard.state(i, j) != nullptr){
        if (utf){
          mbstate_t state;
          char piece[sizeof(char32_t)/sizeof(char)];
          c32rtomb(piece, chessBoard.state(i, j)->utfRepresentation(), &state);
          os << piece;
        } else {
          os << chessBoard.state(i, j)->latin1Representation();
        }
      }
      else {
        os  << ".";
      }
    }
    os << std::endl;
  }
  return os;
}
