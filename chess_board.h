#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

class ChessBoard
{
public:
    ChessBoard();
    ~ChessBoard();
    void Print();

private:
    vector<Piece> blacks;
    vector<Piece> whites;
    vector<vector<Piece>> board;
};

#endif
