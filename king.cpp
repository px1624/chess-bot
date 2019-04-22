#include "piece.h"
#include <cmath>
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

    //chek for castle
    //king never moved
    if(move_count == 0)
    {
        //get both rooks
        Piece* kSideR = board[row][7];
        Piece* qSideR = board[row][0];
        
        //king side castle
        if(kSideR != nullptr &&
           kSideR->GetMoveCount() == 0 &&
           kSideR->GetSymbol() == 'R' &&
           kSideR->GetColor() == this->piece_color)
        {
            //no piece should be between the king and the rook
            if(board[row][col + 1] == nullptr && board[row][col + 2] == nullptr)
            {
                //the king is not currently in check
                //and the king does not move through a square that is under attack
                if(!isInCheck(board, row, col) &&
                   !isInCheck(board, row, col + 1) &&
                   !isInCheck(board, row, col + 2))
                {
                    moves.insert(make_pair(row, col + 2));
                }
            }
        }

        //queen side castle
        if(qSideR != nullptr &&
           qSideR->GetMoveCount() == 0 &&
           qSideR->GetSymbol() == 'R' &&
           qSideR->GetColor() == this->piece_color)
        {
            //no piece should be between the king and the rook
            if(board[row][col - 1] == nullptr &&
               board[row][col - 2] == nullptr &&
               board[row][col - 3] == nullptr)
            {
                //the king is not currently in check
                //and the king does not move through a square that is under attack
                if(!isInCheck(board, row, col) &&
                   !isInCheck(board, row, col - 1) &&
                   !isInCheck(board, row, col - 2))
                {
                    moves.insert(make_pair(row, col - 2));
                }
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
                if(board[i][j]->GetSymbol() == 'K')
                {
                    if((abs(r - i) <= 1) && (abs(c - j) <= 1))
                        return true;
                }
                else
                {
                    board[i][j]->ValidMoves(moves, newBoard);
                    //cout << "got valid moves\n" << flush;
                    for(it = moves.begin(); it != moves.end(); ++it)
                    {
                        if(it->first == r && it->second == c)
                            return true;
                    }
                }
            }
        }
    }
    return false;
}
