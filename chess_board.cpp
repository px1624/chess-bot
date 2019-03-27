#include "chess_board.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

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
/*
	vector < Piece* > temp;
	Piece *buffer;
	buffer = new Pawn(0, 0, 'w');
	temp.push_back(buffer);
	board.push_back(temp);
	cout<<board[0][0]->GetColor()<<board[0][0]->GetSymbol()<<endl;
*/
}

ChessBoard::~ChessBoard()
{

}

void ChessBoard::Move(int rFrom, int cFrom, int rTo, int cTo)
{

}
