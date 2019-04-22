
#include "piece.h"
#include <map>
#include <sstream>
#include <vector>

using namespace std;

Piece::Piece(int row, int col, char color, char symbol, int pVal):piece_symbol(symbol), piece_color(color), row(row), col(col), piece_value(pVal), move_count(0)
{
    if(color == 'b')
    {
        piece_value *= -1;
    }
}

Piece::~Piece()
{
}

int Piece::GetPrevRow(){
	return prevRow;
}

void  Piece::SetPrevRow(int pRow){
	prevRow = pRow;
}

int Piece::getPieceValue(){

	return piece_value;

}

void Piece::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
{
    moves.clear();
}

string Piece::GetPieceStr(string bgColor)
{
    ostringstream oss;
    int fgColor = this->piece_color == 'w' ? 96 : 95;
    oss.clear();
    oss << "\033[1;" << fgColor <</* ";" << bgColor <<*/  "m " << piece_symbol << "\033[0m";
    return oss.str();
}

char Piece::GetColor()
{
	return piece_color;
}

char Piece::GetSymbol()
{
    return piece_symbol;
}

void Piece::SetPosition(int r, int c)
{
	row = r;
	col = c;
}

void Piece::GetPosition(int &r, int &c)
{
	r = row;
	c = col;
}

void Piece::IncMoveCount()
{
    ++move_count;
}

void Piece::DecMoveCount()
{
    --move_count;
}

int Piece::GetMoveCount()
{
    return move_count;
}

void Piece::SetMoveCount(int moveCount)
{
    this->move_count = moveCount;
}
