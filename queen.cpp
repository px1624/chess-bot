/*queen.cpp - Written by Michael Wermert and Pengda Xie
 * Description - This file contains the method definitions for the queen class 
 * declared at piece.h .

*/
#include "piece.h"

using namespace std;

//constructor
Queen::Queen(int row, int col, char color):Piece(row, col, color, 'Q', 90)
{
}

void Queen::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
{
    moves.clear();
 //check left
    for(int i = this->col - 1; i >= 0; --i)
    {
        if(board[row][i] == nullptr)
            moves.insert(make_pair(this->row, i));
        else
        {
            if(board[row][i]->GetColor() != this->piece_color)
                moves.insert(make_pair(this->row, i));

            break;
        }
    }

    //check right
    for(unsigned int i = this->col + 1; i < board[this->row].size(); ++i)
    {
        if(board[row][i] == nullptr)
            moves.insert(make_pair(this->row, i));
        else
        {
            if(board[row][i]->GetColor() != this->piece_color)
                moves.insert(make_pair(this->row, i));

            break;
        }
    }

    //check top
    for(int i = this->row - 1; i >= 0; i--)
    {
        if(board[i][this->col] == nullptr)
            moves.insert(make_pair(i, this->col));
        else
        {
            if(board[i][this->col]->GetColor() != this->piece_color)
                moves.insert(make_pair(i, this->col));

            break;
        }
    }
 //check bottom
    for( int i = this->row + 1; i < 8 ;i++)
    {
        if(board[i][this->col] == nullptr)
            moves.insert(make_pair(i, this->col));
        else
        {
            if(board[i][this->col]->GetColor() != this->piece_color)
                moves.insert(make_pair(i, this->col));

            break;
        }
    }
	
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
