#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <vector>
#include "piece.h"

class ChessBoard
{
public:
    ChessBoard();
    ~ChessBoard();
    void Print();
    void Move(int rFrom, int cFrom, int rTo, int cTo);
	char getSpaceColor(int r, int c);
	char getSpaceType(int r, int c);
	bool checkNull(int r, int c);
	Piece *getPiece(int r, int c);
	std::vector<std::vector <Piece*> > getBoard();

private:
    std::vector<Piece*> blacks;
    std::vector<Piece*> whites;
    std::vector<std::vector <Piece*> > board;
};

#endif
