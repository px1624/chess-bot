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
    void PrintAllValidMoves();
    void Move(int rFrom, int cFrom, int rTo, int cTo);
	char getSpaceColor(int r, int c);
	char getSpaceType(int r, int c);
	bool checkNull(int r, int c);
	Piece *getPiece(int r, int c);
	std::vector<std::vector <Piece*> > getBoard();
	int check(int turn);
	bool PawnPCheck(int &row, int &col);
	void PawnPromotion(int row, int col);

private:
    const int row_size = 8;
    const int col_size = 8;
    int turnCount;
    std::vector<Piece*> blacks;
    std::vector<Piece*> whites;
    std::vector<std::vector <Piece*> > board;
    bool ContainsMove(std::multimap<int, int> &moves, int r, int c);
    void RemovePiece(int r, int c);
};

#endif
