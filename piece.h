#ifndef PIECE_H
#define PIECE_H
#include <map>
#include <vector>
#include <string>

class Piece
{
 public:
    Piece(int row, int col, char color, char symbol);
    virtual ~Piece();
    virtual void ValidMoves(std::multimap<char, int> &moves, const std::vector < std::vector <Piece*> > &board);
    std::string GetPieceStr();
    char GetColor();
    char GetSymbol();
    void SetPosition(int r, int c);
    void GetPosition(int &r, int &c);

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
