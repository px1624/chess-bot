#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <vector>
#include "Piece.h"

class ChessBoard
{
public:
    ChessBoard();
    ~ChessBoard();
    void Print();
    void move(int rowFrom, int colFrom, int rowTo, int colTo);

private:
    vector<Piece> blacks;
    vector<Piece> whites;
    vector<vector <Piece*> > board;
};

#endif
