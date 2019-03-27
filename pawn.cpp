#include <iostream>
#include <string>
#include <map>
#include "piece.h"

using namespace std;

Pawn::Pawn(int row, int col, char color):Piece(row, col, color, 'P')
{

}

void Pawn::ValidMoves(std::multimap<char, int>&moves, const std::vector < std::vector <Piece*> > board){
/*
    if (turn == 1){
        for(int i = 1; i < 3; i++ ){

            if(row - i >=0){

                if(board[row - i][col][0] == ' ')
                    moves.insert( std::pair<char,int>(row - i + 'A', col));

            }

        }

        if(row-1 >= 0 && col - 1 >= 0){

            if(board[row - 1][col-1][0] != board[row][col][0] && board[row - 1][col-1][0] != ' ')
                moves.insert( std::pair<char,int>(row - 1 + 'A', col - 1));

        }

        if(row-1 >= 0 && col + 1 < board[0].size()){

            if(board[row - 1][col+1][0] != board[row][col][0] && board[row - 1][col+1][0] != ' ')
                moves.insert( std::pair<char,int>(row - 1 + 'A', col + 1));

        }
    }
    if (turn == 2){
        for(int i = 1; i < 3; i++ ){

            if(row + i >=0){

                if(board[row + i][col][0] == ' ')
                    moves.insert( std::pair<char,int>(row + i + 'A', col));

            }

        }

        if(row+1 >= 0 && col - 1 >= 0){

            if(board[row + 1][col-1][0] != board[row][col][0] && board[row + 1][col-1][0] != ' ')
                moves.insert( std::pair<char,int>(row + 1 + 'A', col - 1));

        }

        if(row+1 >= 0 && col + 1 < board[0].size()){

            if(board[row + 1][col+1][0] != board[row][col][0] && board[row + 1][col+1][0] != ' ')
                moves.insert( std::pair<char,int>(row + 1 + 'A', col + 1));

        }
    }
	*/
}
