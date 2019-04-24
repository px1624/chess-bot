/* Pawn.cpp - Michael Wermert Pengda Xie
 * Description - This file contains the member function for the pawn 
 * class defined in piece.h.

*/
#include <iostream>
#include <string>
#include <map>
#include "piece.h"

using namespace std;

//constructor
Pawn::Pawn(int row, int col, char color):Piece(row, col, color, 'P', 10)
{

}

//fills map with all the valid moves for the pawn
void Pawn::ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board){

		moves.clear();
	    if (this->piece_color == 'w'){
        
		
		//if the white pawn is in the starting row, it can move two spaces forward
		if(row == 6){		

        for(int i = 1; i < 3; i++ ){

            if(row - i >=0){

                if(board[row - i][col] == nullptr)
                    moves.insert( std::pair<int,int>(row - i, col));
				if(board[row - i][col] != nullptr)
					break;

            }

        }
		}
		//else it can only move one space forward
		else{

			for(int i = 1; i < 2; i++ ){
				if(row - i >=0){

					if(board[row - i][col] == nullptr)
						moves.insert( std::pair<int,int>(row - i, col));

				}

			}
		}

		//if there is a black pawn in the diagonal forward spaces, the pawn may capture it
        if(row-1 >= 0 && col - 1 >= 0){

            if(board[row - 1][col-1] != nullptr){
				if(board[row-1][col-1]->GetColor() == 'b')
					moves.insert( std::pair<int,int>(row - 1, col - 1));
			}

        }

        if(row-1 >= 0 && col + 1 < (int)board[0].size()){

            if(board[row - 1][col+1] != nullptr){
				if(board[row - 1][col+1]->GetColor() ==  'b')
					moves.insert( std::pair<int,int>(row - 1, col + 1));
			}
        }

		//if the conditions are met, en passe may happen
		if(row == 3){
			if(col - 1 >= 0){
				if(board[row][col-1] != nullptr &&
						board[row][col-1]->GetColor() == 'b' &&
						board[row][col-1]->GetSymbol() == 'P' && board[row][col-1]->GetPrevRow() == 1 &&
						board[row-1][col-1] == nullptr){
					
					moves.insert(std::pair<int,int>(row - 1, col - 1));
				
				}
			}
			
			if(col + 1 < board[3].size()){
				if(board[row][col+1] != nullptr &&
						board[row][col+1]->GetColor() == 'b' &&
						board[row][col+1]->GetSymbol() == 'P' && board[row][col+1]->GetPrevRow() == 1 &&
						board[row-1][col+1] == nullptr){
					
					moves.insert(std::pair<int,int>(row - 1, col + 1));
				
				}
			}
		}

		
    }
	else if (this->piece_color == 'b'){
        
       // cout << "check b\n" << flush;
		
		//if the black pawns are in the starting row, they may move 2 spaces
		if(row == 1){
		
		for(int i = 1; i < 3; i++ ){

            if(row + i <= 7){

                if(board[row + i][col] == nullptr)
                    moves.insert( std::pair<int,int>(row + i, col));

				if(board[row + i][col] != nullptr)
					break;


            }

        }
		}

		//else they can move 1
		else{

		for(int i = 1; i < 2; i++ ){

            if(row + i <= 7){

                if(board[row + i][col] == nullptr)
                    moves.insert( std::pair<int,int>(row + i, col));

            }

        }


		}

		//can capture white pieces in the diagonal
        if(row+1 <= (int)board.size() && col - 1 >= 0){

			if(board[row + 1][col-1] != nullptr){
				if(board[row + 1][col-1]->GetColor()  == 'w')
					moves.insert( std::pair<int,int>(row + 1, col - 1));
			}
        }

        if(row+1 <= (int)board.size() && col + 1 < (int)board[0].size()){

			if(board[row + 1][col+1] != nullptr){
				if(board[row + 1][col+1]->GetColor() == 'w')
					moves.insert( std::pair<int,int>(row + 1, col + 1));
			}
            
        }

		//en passe for black pieces
		if(row == 4){
			if(col - 1 >= 0){
				if(board[row][col-1] != nullptr &&
						board[row][col-1]->GetColor() == 'w' &&
						board[row][col-1]->GetSymbol() == 'P' && board[row][col-1]->GetPrevRow() == 6 &&
						board[row+1][col-1] == nullptr){
					
					moves.insert(std::pair<int,int>(row + 1, col - 1));
				
				}
			}
			
			if(col + 1 < board[3].size()){
				if(board[row][col+1] != nullptr &&
						board[row][col+1]->GetColor() == 'w' &&
						board[row][col+1]->GetSymbol() == 'P' && board[row][col+1]->GetPrevRow() == 6 &&
						board[row+1][col+1] == nullptr){
					
					moves.insert(std::pair<int,int>(row + 1, col + 1));
				
				}
			}
		}
    }	

}
