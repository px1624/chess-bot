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

private:
    vector<Piece> blacks;
    vector<Piece> whites;
    vector<vector <Piece*> > board;
};

#endif
