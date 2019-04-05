#include "piece.h"

using namespace std;

Queen::Queen(int row, int col, char color):Piece(row, col, color, 'Q', 90)
{
}

void Queen::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
{
    moves.clear();
    moves.insert(make_pair(-1, -1));
}
