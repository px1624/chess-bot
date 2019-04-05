#ifndef PIECE_H
#define PIECE_H
#include <map>
#include <vector>
#include <string>

class Piece
{
 public:
    Piece(int row, int col, char color, char symbol, int pVal);
    virtual ~Piece();
    virtual void ValidMoves(std::multimap<int, int> &moves, const std::vector < std::vector <Piece*> > &board);
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
    int piece_value;
};

class King : public Piece
{
public:
    King(int row, int col, char color);
    void ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board);
};

class Queen : public Piece
{
public:
    Queen(int row, int col, char color);
    void ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board);
};

class Bishop : public Piece
{
public:
    Bishop(int row, int col, char color);
    void ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board);
};

class Knight : public Piece
{
public:
	void ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board);
    Knight(int row, int col, char color);
};

class Rook : public Piece
{
public:
    Rook(int row, int col, char color);
    void ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board);
};

class Pawn : public Piece
{

public:
    void ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board);
    Pawn(int row, int col, char color);  
};

#endif
