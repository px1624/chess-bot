#include <iostream>
#include <string>
#include <map>
#include "piece.h"

using namespace std;

Pawn::Pawn(int row, int col, char color):Piece(row, col, color, 'P', 10)
{

}

void Pawn::ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board){

		moves.clear();
	    if (this->piece_color == 'w'){
        //cout << "check w\n" << flush;
		
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
	
		else{

			for(int i = 1; i < 2; i++ ){
				if(row - i >=0){

					if(board[row - i][col] == nullptr)
						moves.insert( std::pair<int,int>(row - i, col));

				}

			}
		}

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
		else{

		for(int i = 1; i < 2; i++ ){

            if(row + i <= 7){

                if(board[row + i][col] == nullptr)
                    moves.insert( std::pair<int,int>(row + i, col));

            }

        }


		}

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
