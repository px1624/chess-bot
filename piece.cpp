#include <map>
#include <vector>
#include "piece.h"

using namespace std;

Piece::Piece(int row, int col, char color, char symbol, int pVal):piece_symbol(symbol), piece_color(color), row(row), col(col), piece_value(pVal)
{
    if(color == 'b')
    {
        piece_value *= -1;
    }
}

Piece::~Piece()
{
}

void Piece::ValidMoves(multimap<char, int> &moves, const vector<vector<Piece*> > &board)
{    
}

string Piece::GetPieceStr()
{
    string pieceStr = "";
    pieceStr.push_back(piece_color);
    pieceStr.push_back(piece_symbol);
    return pieceStr;
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


