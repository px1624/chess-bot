/*piece.h - Written by Michael Wermert and Pengda Xie
 * Description - This file declares the basic piece class and the 
 * specific classes for each piece that have inherited the base piece class
 * functions.

*/
#ifndef PIECE_H
#define PIECE_H
#include <map>
#include <vector>
#include <string>

//base class
class Piece
{
 public:
    Piece(int row, int col, char color, char symbol, int pVal);
    virtual ~Piece();
    virtual void ValidMoves(std::multimap<int, int> &moves, const std::vector < std::vector <Piece*> > &board);
    std::string GetPieceStr(std::string bgColor = "40");
    char GetColor();
    char GetSymbol();
    void SetPosition(int r, int c);
    void GetPosition(int &r, int &c);
    void IncMoveCount();
    void DecMoveCount();
    int GetMoveCount();
    void SetMoveCount(int moveCount);
	int  GetPrevRow();
	void SetPrevRow(int pRow);
	int getPieceValue();

protected:
    char piece_symbol;
    char piece_color;
    int row;
    int col;
    int piece_value;
    int move_count;
	int prevRow;
};

//derived class for all chess pieces
class King : public Piece
{
public:
    King(int row, int col, char color);
    void ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board);
    bool isInCheck(const std::vector < std::vector < Piece*> > &board, int r, int c);
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
