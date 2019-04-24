/*piece.cpp by Michael Wermert and Pengda Xie
 * This file contains the member functions for the piece class declared in
 * piece.h
 *
 **/
#include "piece.h"
#include <map>
#include <sstream>
#include <vector>

using namespace std;

//constructor
Piece::Piece(int row, int col, char color, char symbol, int pVal):piece_symbol(symbol), piece_color(color), row(row), col(col), piece_value(pVal), move_count(0)
{
    if(color == 'b')
    {
        piece_value *= -1;
    }
}

//destructor
Piece::~Piece()
{
}

//returns previous row of a piece
int Piece::GetPrevRow(){
	return prevRow;
}

//sets the previous row of a piece
void  Piece::SetPrevRow(int pRow){
	prevRow = pRow;
}

//returns the value of a piece, used 
//for the A.I. 
int Piece::getPieceValue(){

	return piece_value;

}

//generic valid moves function
void Piece::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
{
    moves.clear();
}

//returns the piece color and symbol together as a string
string Piece::GetPieceStr(string bgColor)
{
    ostringstream oss;
    int fgColor = this->piece_color == 'w' ? 96 : 95;
    oss.clear();
    oss << "\033[1;" << fgColor <</* ";" << bgColor <<*/  "m " << piece_symbol << "\033[0m";
    return oss.str();
}

//returns the color of a piece
char Piece::GetColor()
{
	return piece_color;
}

//returns the type of piece as a char
char Piece::GetSymbol()
{
    return piece_symbol;
}

//sets the positions of a piece
void Piece::SetPosition(int r, int c)
{
	row = r;
	col = c;
}

//returns the location of a piece
void Piece::GetPosition(int &r, int &c)
{
	r = row;
	c = col;
}

//increases move count
void Piece::IncMoveCount()
{
    ++move_count;
}

//decrements move counts
void Piece::DecMoveCount()
{
    --move_count;
}

//returns the move count
int Piece::GetMoveCount()
{
    return move_count;
}

//sets the move count
void Piece::SetMoveCount(int moveCount)
{
    this->move_count = moveCount;
}
