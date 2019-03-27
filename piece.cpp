
#include "piece.h"

using namespace std;

Piece::Piece(int row, int col, char color, char symbol):piece_symbol(symbol), piece_color(color), row(row), col(col)
{
}

char Piece::GetColor(){
	
	return piece_color;

}

void Piece::SetPosition(int r, int c){

	row = r;
	col = c;

}

void Piece::GetPosition(int &r, int &c){

	r = row;
	c = col;

}


