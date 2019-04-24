/*rook.cpp - Written by Michael Wermert and Pengda Xie
 * Description - This file contains the method definitions for the rook class declared in
 * piece.h.

*/
#include "piece.h"

using namespace std;

Rook::Rook(int row, int col, char color):Piece(row, col, color, 'R', 50)
{
}

void Rook::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
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
    for(int i = this->row - 1; i >= 0; --i)
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
    for(unsigned int i = this->row + 1; i < board.size(); ++i)
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

}
