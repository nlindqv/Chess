#ifndef ChessMove_H
#define ChessMove_H

class ChessPiece;

struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    ChessPiece* piece;   // you can change the position of the chess piece with this pointer.

    ChessMove() = default;
    ChessMove(int f_x, int f_y, int t_x, int t_y, ChessPiece* cPiece):
        from_x(f_x), from_y(f_y), to_x(t_x), to_y(t_y), piece(cPiece){}

};

#endif






/*
ChessPiece Vairables

int x,y;            Board Position
bool isWhite;       ChessPiece Color
ChessBoard* board;  Pointer to the board where the piece is stored

*/
