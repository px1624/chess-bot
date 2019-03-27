#ifndef PIECE_H
#define PIECE_H
#include <map>
#include <vector>

class Piece
{
 public:
    Piece(int row, int col, char color, char symbol);
    virtual void ValidMoves(std::multimap<char, int> &moves, const std::vector < std::vector <Piece*> > &board) = 0;
    virtual char GetColor() = 0;
    virtual char GetSymbol() = 0;
    virtual void SetPosition(int r, int c) = 0;
    virtual void GetPosition(int &r, int &c) = 0;

protected:
    char piece_symbol;
    char piece_color;
    int row;
    int col;
};

class King : public Piece
{
public:
    King(int row, int col, char color);
};

class Queen : public Piece
{
public:
    Queen(int row, int col, char color);
};

class Bishop : public Piece
{
public:
    Bishop(int row, int col, char color);
};

class Knight : public Piece
{
public:
    Knight(int row, int col, char color);
};

class Rook : public Piece
{
public:
    Rook(int row, int col, char color);
};

class Pawn : public Piece
{

public:
    void ValidMoves(std::multimap<char, int>&moves, const std::vector < std::vector <Piece*> > board);
    Pawn(int row, int col, char color);
private:
    int turn;
};

#endif
