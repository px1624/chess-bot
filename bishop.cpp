#include "piece.h"
//#include <iostream>
using namespace std;

Bishop::Bishop(int row, int col, char color):Piece(row, col, color, 'B', 30)
{
}

void Bishop::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
{
    moves.clear();
    int r, c;
    
    //check top left
    //cout << "check top left...\n" << flush;
    for(r = this->row - 1, c = this->col - 1; r >= 0 && c >= 0;)
    {
        if(board[r][c] == nullptr)
            moves.insert(make_pair(r, c));
        else
        {
            if(board[r][c]->GetColor() != this->piece_color)
                moves.insert(make_pair(r, c));

            break;
        }

        --r;
        --c;
    }

    //check top right
    //cout << "check top right...\n" << flush;
    for(r = this->row - 1, c = this->col + 1; r >= 0 && c < (int)board.size();)
    {
        if(board[r][c] == nullptr)
            moves.insert(make_pair(r, c));
        else
        {
            if(board[r][c]->GetColor() != this->piece_color)
                moves.insert(make_pair(r, c));

            break;
        }

        --r;
        ++c;
    }
 
    //check bottom left
    //cout << "check bottom left...\n" << flush;
    for(r = this->row + 1, c = this->col - 1; r < (int)board.size() && c >= 0;)
    {
        if(board[r][c] == nullptr)
            moves.insert(make_pair(r, c));
        else
        {
            if(board[r][c]->GetColor() != this->piece_color)
                moves.insert(make_pair(r, c));

            break;
        }

        ++r;
        --c;
    }
 
    //check bottom right
    //cout << "check bottom right...\n" << flush;
    for(r = this->row + 1, c = this->col + 1; r < (int)board.size() && c < (int)board.size();)
    {
        if(board[r][c] == nullptr)
            moves.insert(make_pair(r, c));
        else
        {
            if(board[r][c]->GetColor() != this->piece_color)
                moves.insert(make_pair(r, c));

            break;
        }

        ++r;
        ++c;
    }

}
