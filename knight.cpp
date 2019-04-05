#include "piece.h"

Knight::Knight(int row, int col, char color):Piece(row, col, color, 'N', 30)
{

}

void Knight::ValidMoves(std::multimap<int, int>&moves, const std::vector < std::vector <Piece*> > &board){

	

	if(row - 1 >= 0 && col - 2 >= 0){
		if(board[row - 1][col-2] == nullptr || board[row - 1][col-2]->GetColor() != this->piece_color)
			moves.insert ( std::pair<int,int>(row - 1, col-2) );
	}

	if(row - 2 >= 0 && col - 1 >= 0){
		if(board[row - 2][col-1] == nullptr || board[row - 2][col-1]->GetColor() != this->piece_color)
			 moves.insert ( std::pair<int,int>(row - 2, col-1) );
	}

	if(row + 1 < (int)board.size() && col - 2 >= 0){
		if(board[row +1][col-2] == nullptr || board[row +1][col-2]->GetColor() != this->piece_color)
		 moves.insert ( std::pair<int,int>(row + 1, col-2) );
	}

	if(row + 2 < (int)board.size() && col - 1 >= 0){
		if(board[row + 2][col-1] == nullptr || board[row + 2][col-1]->GetColor() != this->piece_color)
			 moves.insert ( std::pair<int,int>(row + 2, col-1) );
	}


	if(row - 1 >= 0 && col + 2 < (int)board[0].size()){
		if(board[row - 1][col+2] == nullptr || board[row - 1][col+2]->GetColor() != this->piece_color)
			 moves.insert ( std::pair<int,int>(row - 1, col+2) );
	}


	if(row - 2 >= 0 && col + 1 < (int)board[0].size()){
		if(board[row - 2][col+1] == nullptr || board[row - 2][col+1]->GetColor() != this->piece_color)
			moves.insert ( std::pair<int,int>(row - 2, col+1) );
	}

	
	if(row + 1 < (int)board.size() && col + 2 < (int)board[0].size()){
		if(board[row + 1][col+2] == nullptr || board[row + 1][col+2]->GetColor() != this->piece_color)
			 moves.insert ( std::pair<int,int>(row + 1, col+2) );
	}


	if(row + 2 < (int)board.size() && col + 1 < (int)board[0].size()){
		if(board[row + 2][col+1] == nullptr || board[row + 2][col+1]->GetColor() != this->piece_color)
			moves.insert ( std::pair<int,int>(row + 2, col+1) );
	}	

}
