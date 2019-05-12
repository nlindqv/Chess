#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "ChessBoard.h"
#include "ChessPiece.h"
#include "ChessMove.h"
#include "ChessAI.h"
using namespace std;


const string initBoard = "rnbkqbnr\npppppppp\n........\n........\n........\n........\nPPPPPPPP\nRNBQKBNR";
const string testBoards[] = {"Q..n...r\n........\nn.r.....\n........\n........\n........\n........\n........",
                             "Kb......\nnn......\n........\n........\n........\n........\n........\n........",
                             "R..n....\nbn......\n........\n........\n........\n........\n........\n........",
                             "B..n....\nbn......\n........\n........\n........\n........\n........\n........",
                             "N..n....\nbnp.....\n.p......\n........\n........\n........\n........\n........"};


void printState(const ChessBoard& chess, const ChessMove& move, const bool isWhite);

void testCases (){
  for (int i = 3; i < sizeof(testBoards)/sizeof(testBoards[0]); i++){
    ChessBoard chess;
    stringstream s;
    s << testBoards[i];
    s >> chess;
    cout << chess;
    cout << "White capture moves: " << chess.capturingMoves(true).size() << endl;
    cout << "Black capture moves: " << chess.capturingMoves(false).size() << endl << endl;
  }
}

int main (int argc, char* argv[]){
  int p1 = 1, p2 = 2;
  int* nextPlayer = &p1;
  bool whitePlayerTurn = true;
  if (argc == 4){
    if (!string(argv[1]).compare("black")){
      whitePlayerTurn = false;
      nextPlayer = &p2;
    }
    p1 = std::atoi(argv[2]);
    p2 = std::atoi(argv[3]);
  }


  ChessBoard chess;
  stringstream s;
  s << "...k...." << endl;
  s << "..P....." << endl;
  s << ".r.p...." << endl;
  s << "........" << endl;
  s << "........" << endl;
  s << "........" << endl;
  s << "........" << endl;
  s << "........";
  //s << initBoard;
  s >> chess;
  cout << chess << endl;

  ChessAI player1(true, p1);
  ChessAI player2(false, p2);
  int nonCapturingMoves = 0;
  // While next player can move
  while (chess.capturingMoves(whitePlayerTurn).size() + chess.nonCapturingMoves(whitePlayerTurn).size() > 0){
    // Make move
    if (whitePlayerTurn){
      ChessMove move = player1.getNextMove(chess);
      if (player1.pawnPromotion){
        cout << "Pawn promotion DONE!" << endl;
        int i;
        cin >> i;
        chess.move_piece(move, player1.getPawnPromotion(chess, move));
      } else {
        chess.move_piece(move);
      }
      printState(chess, move, whitePlayerTurn);
      whitePlayerTurn = false;
    } else {
      ChessMove move = player2.getNextMove(chess);
      if (player2.pawnPromotion){
        cout << "Pawn promotion2 DONE!" << endl;
        int i;
        cin >> i;
        chess.move_piece(move, player2.getPawnPromotion(chess, move));
      } else {
        chess.move_piece(move);
      }
      printState(chess, move, whitePlayerTurn);
      whitePlayerTurn = true;
    }
  }
  if (chess.capturingMoves(true).size() + chess.nonCapturingMoves(true).size() == 0){
    std::cout << "White player win!" << std::endl;
  }
  else {
    std::cout << "Black player win!" << std::endl;
  }
  return 0;
}


void printState(const ChessBoard& chess, const ChessMove& move, const bool isWhite){
  if (isWhite){
    cout << "White player moved ";
  } else {
    cout << "Black player moved ";
  }
  cout << move.piece->latin1Representation() << " from (" << move.from_x << "," << move.from_y << ") to (" << move.to_x << "," << move.to_y << ")." << endl;
  cout << chess << endl;

}
