/*bishop.cpp - Written by Michael Wermert and Pengda Xie
 * Description - This contains the function definitions for
 * the bishop class in the piece.h file.

*/
#include "piece.h"

using namespace std;

//constructor
Bishop::Bishop(int row, int col, char color):Piece(row, col, color, 'B', 30)
{
}

void Bishop::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
{
    moves.clear();
    int r, c;
    
    //check top left
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
