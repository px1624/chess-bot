#include "piece.h"

using namespace std;

King::King(int row, int col, char color):Piece(row, col, color, 'K', 900)
{
}

void King::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
{
    moves.clear();
    moves.insert(make_pair(-1, -1));
}
