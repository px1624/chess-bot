#include "piece.h"
#include <utility>

using namespace std;

King::King(int row, int col, char color):Piece(row, col, color, 'K', 900)
{
}

void King::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
{
    moves.clear();
    vector<pair<int, int>> allMoves;
    Piece* pPtr;
    allMoves.push_back(make_pair(row - 1, col - 1));
    allMoves.push_back(make_pair(row - 1, col));
    allMoves.push_back(make_pair(row - 1, col + 1));
    allMoves.push_back(make_pair(row, col - 1));
    allMoves.push_back(make_pair(row, col + 1));
    allMoves.push_back(make_pair(row + 1, col - 1));
    allMoves.push_back(make_pair(row + 1, col));
    allMoves.push_back(make_pair(row + 1, col + 1));
    
    //need to add a check for if the target cell is under attack
    for(unsigned int i = 0; i < allMoves.size(); i++)
    {
        pPtr = board[allMoves[i].first][allMoves[i].second];
        if(pPtr == nullptr || pPtr->GetColor() != this->piece_color)
        {
            moves.insert(allMoves[i]);
        }
    }
}
