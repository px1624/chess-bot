#include "chess_board.h"
#include <string>
#include <vector>

void ChessBoard::Print()
{
	string solidRow = "\t  #########################################";
	string buffRow  = "\t  #    #    #    #    #    #    #    #    #";


	cout<<endl;
	cout<<"\t     1";
	for(int i = 2;i <= 8;i++)
		cout<<"    "<<i;
	cout<<endl;
	cout<<solidRow<<endl;
	char rowCount = 'A';
	

	for(int i = 0; i < board.size();i++){

		cout<<buffRow<<endl;
		cout<<"\t"<<rowCount<<" #";
		for(int j = 0;  j < board[i].size();j++){
			
			cout<<" "<<board[i][j]<<" #";

		}
		cout<<endl;
		cout<<buffRow<<endl;
		cout<<solidRow<<endl;

		rowCount++;
	}  
}

ChessBoard::ChessBoard()
{
  
}

ChessBoard::~ChessBoard()
{
  
}

void ChessBoard::move()
{
   
}
