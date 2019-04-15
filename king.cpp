#include "piece.h"
#include <utility>
#include <iostream>
using namespace std;

King::King(int row, int col, char color):Piece(row, col, color, 'K', 900)
{
}

void King::ValidMoves(multimap<int, int> &moves, const vector<vector<Piece*> > &board)
{
    moves.clear();
    vector<pair<int, int>> allMoves;
    int r, c;
    Piece* pPtr;
    allMoves.push_back(make_pair(row - 1, col - 1));
    allMoves.push_back(make_pair(row - 1, col));
    allMoves.push_back(make_pair(row - 1, col + 1));
    allMoves.push_back(make_pair(row, col - 1));
    allMoves.push_back(make_pair(row, col + 1));
    allMoves.push_back(make_pair(row + 1, col - 1));
    allMoves.push_back(make_pair(row + 1, col));
    allMoves.push_back(make_pair(row + 1, col + 1));
    
    for(unsigned int i = 0; i < allMoves.size(); i++)
    {
        r = allMoves[i].first;
        c = allMoves[i].second;
        
        //if col and row are within the bound
        if(r >= 0 && r < (int)board.size() && c >= 0 && c < (int)board.size())
        {
            pPtr = board[r][c];
            //if the target cell is a valid move
            if(pPtr == nullptr || pPtr->GetColor () != this->piece_color)
            {
                if(!isInCheck(board, r, c))
                    moves.insert(allMoves[i]);
            }
        }
    }
}


bool King::isInCheck(const vector<vector<Piece*> > &board, int r, int c)
{
    vector<vector<Piece*> > newBoard = board;
    multimap<int, int> moves;
    multimap<int, int>::iterator it;
    newBoard[r][c] = newBoard[this->row][this->col];
    newBoard[this->row][this->col] = nullptr;
    for(unsigned int i = 0; i < board.size(); i++)
    {
        for(unsigned int j = 0; j < board[i].size(); j++)
        {
            if(board[i][j] != nullptr && board[i][j]->GetColor() != this->piece_color)
            {
                //cout << i << " " << j << endl << flush;
                board[i][j]->ValidMoves(moves, newBoard);
                //cout << "got valid moves\n" << flush;
                for(it = moves.begin(); it != moves.end(); ++it)
                {
                    if(it->first == r && it->second == c)
                    {
                        cout << "king cannot move to " << r << " " << c << endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
