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
    int r, c;
    Piece* pPtr;

    vector<vector<Piece*>> newBoard;
    multimap<int, int> tmpMoves;
    char oppositeColor = this->piece_color == 'w' ? 'b' : 'w';
    bool inCheck = false;

    //push all 8 possible moves
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
            inCheck = false;
            //if the target cell is a valid move
            if(pPtr == nullptr || pPtr->GetColor () != this->piece_color)
            {
                //check if target cell is safe, i.e. king cannot be in check after the move
                //make a copy of the board and nulls the target cell on the copy
                newBoard = board;
                newBoard[r][c] = nullptr;
                //goes through the copied board
                for(unsigned int i = 0; i < newBoard.size(); i++)
                {
                    for(unsigned int j = 0; j < newBoard[i].size(); j++)
                    {
                        //for each opposite color piece
                        if(newBoard[i][j] != nullptr && newBoard[i][j]->GetColor() == oppositeColor)
                        {
                            //get the piece's valid moves
                            newBoard[i][j]->ValidMoves(tmpMoves, newBoard);
                            for(multimap<int, int>::iterator it = tmpMoves.begin(); it != tmpMoves.end(); ++it)
                            {
                                if(it->first == r && it->second == c)
                                {
                                    inCheck = true;
                                    break;
                                }
                            }
                        }
                        
                        if(inCheck)
                            break;
                    }

                    if(inCheck)
                        break;
                }

                if(!inCheck)
                    moves.insert(allMoves[i]);
            }
        }
    }
}
