FLAGS = -std=c++11 -Wall -pedantic

chess:	main.cpp ChessBoard.o ChessPiece.o King.o Knight.o Pawn.o Bishop.o Rook.o Queen.o ChessAI.o
	g++ $(FLAGS) main.cpp ChessBoard.o ChessPiece.o King.o Knight.o Pawn.o Bishop.o Rook.o Queen.o ChessAI.o

game:	a.out
	./a.out white 2 2

%.o:	ChessPieces/%.h	ChessPieces/%.cpp
	g++ $(FLAGS) -c ChessPieces/$*.cpp

ChessBoard.o:	ChessBoard.h	ChessBoard.cpp
		g++ $(FLAGS) -c ChessBoard.cpp

ChessPiece.o:	ChessPiece.h	ChessPiece.cpp
		g++ $(FLAGS) -c ChessPiece.cpp

ChessAI.o:	ChessAI.h	ChessAI.cpp
		g++ $(FLAGS) -c ChessAI.cpp


clean:
	rm *.o
	rm *.out
	rm *.gch
