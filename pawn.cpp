#include <iostream>
#include <string>
#include <map>
#include "piece.h"

using namespace std;

Pawn::Pawn(int row, int col, char color):Piece(row, col, color, 'P', 10)
{

}

void Pawn::ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board){

	    if (piece_color == 'w'){
        for(int i = 1; i < 3; i++ ){

            if(row - i >=0){

                if(board[row - i][col] == nullptr)
                    moves.insert( std::pair<int,int>(row - i, col));

            }

        }

        if(row-1 >= 0 && col - 1 >= 0){

            if(board[row - 1][col-1] != nullptr){
				if(board[row-1][col-1]->GetColor() != board[row][col]->GetColor())
					moves.insert( std::pair<int,int>(row - 1, col - 1));
			}

        }

        if(row-1 >= 0 && col + 1 < (int)board[0].size()){

            if(board[row - 1][col+1] != nullptr){
				if(board[row - 1][col+1]->GetColor() !=  board[row][col]->GetColor())
					moves.insert( std::pair<int,int>(row - 1, col + 1));
			}
        }
    }
	else if (piece_color == 'b'){
        for(int i = 1; i < 3; i++ ){

            if(row + i >=0){

                if(board[row + i][col] == nullptr)
                    moves.insert( std::pair<int,int>(row + i, col));

            }

        }

        if(row+1 <= (int)board.size() && col - 1 >= 0){

			if(board[row + 1][col-1] != nullptr){
				if(board[row + 1][col-1]->GetColor() !=  board[row][col]->GetColor())
					moves.insert( std::pair<int,int>(row + 1, col - 1));
			}
        }

        if(row+1 <= (int)board.size() && col + 1 < board[0].size()){

			if(board[row + 1][col+1] != nullptr){
				if(board[row + 1][col+1]->GetColor() !=  board[row][col]->GetColor())
					moves.insert( std::pair<int,int>(row + 1, col + 1));
			}
            
        }
    }	

}
