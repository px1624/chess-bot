/*chess_board.h - Written by Michael Wermert and Pengda Xie
 * Description - This is the header file for the ChessBoard class. The functions are
 * defined in chess_board.cpp.

*/
#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <vector>
#include "piece.h"

struct AIMove{
    int rFrom;
	int cFrom;
	int rTo;
	int cTo;
};

class ChessBoard
{
public:
    ChessBoard();
    ~ChessBoard();
    void Print();
    void PrintAllValidMoves();
    bool Move(int rFrom, int cFrom, int rTo, int cTo, bool EPFlag);
	char getSpaceColor(int r, int c);
	char getSpaceType(int r, int c);
	bool checkNull(int r, int c);
	Piece *getPiece(int r, int c);
	std::vector<std::vector <Piece*> > getBoard();
	int check();
	bool PawnPCheck(int &row, int &col);
	void PawnPromotion(int row, int col);
	void UndoMove();
	bool ContainsMove(std::multimap<int, int> &moves, int r, int c);
	void incTurnCount();
    int GetTurnCount();
    bool IsWhiteTurn();
	bool CheckMate();
	void EPCleanup();
	void GenerateMove(std::multimap <int, AIMove, std::greater<int> > &allMoves);


private:
    const int row_size = 8;
    const int col_size = 8;
    int turnCount;
    std::vector<Piece*> blacks;
    std::vector<Piece*> whites;
    std::vector<std::vector <Piece*> > board;
    void RemovePiece(int r, int c);
	int prevToRow;
	int prevToCol;
	char prevToColor;
	char prevToSymbol;
    int prevToMoveCount;

	int prevFromRow;
	int prevFromCol;
	char prevFromColor;
	char prevFromSymbol;

};

#endif
