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
            if(board[i][j] != nullptr)
                cout << " " << board[i][j]->GetColor() << board[i][j]->GetSymbol() << " #";
            else
                cout << "  * #";
        }
        cout<<endl;
        cout<<buffRow<<endl;
        cout<<solidRow<<endl;

        rowCount++;
    }  
}

ChessBoard::ChessBoard(): board(8, vector<Piece*>(8, nullptr))
{
/*
	vector < Piece* > temp;
	Piece *buffer;
	buffer = new Pawn(0, 0, 'w');
	temp.push_back(buffer);
	board.push_back(temp);
	cout<<board[0][0]->GetColor()<<board[0][0]->GetSymbol()<<endl;
*/
    Piece* buffer;

    //place black pawns
    for(unsigned int i = 0; i < board[1].size(); i++)
    {
        //make pawn
        buffer = new Pawn(1, i, 'b');
        //place it on board
        board[1][i] = buffer;
    }
    
    //place white pawns
    for(unsigned int i = 0; i < board[6].size(); i++)
    {
        //make pawn
        buffer = new Pawn(6, i, 'w');
        //place it on board
        board[6][i] = buffer;
    }

    //place black pieces
    for(unsigned int i = 0; i < board[0].size(); i++)
    {
        if(i == 0 || i == 7)
        {
            buffer = new Rook(0, i, 'b');
        }
        else if(i == 1 || i == 6)
        {
            buffer = new Knight(0, i, 'b');
        }
        else if(i == 2 || i == 5)
        {
            buffer = new Bishop(0, i, 'b');
        }
        else if(i == 3)
        {
            buffer = new Queen(0, i, 'b');
        }
        else if(i == 4)
        {
            buffer = new King(0, i, 'b');
        }

        board[0][i] = buffer;
    }
    
    //place white pieces
    for(unsigned int i = 0; i < board[7].size(); i++)
    {
        if(i == 0 || i == 7)
        {
            buffer = new Rook(7, i, 'w');
        }
        else if(i == 1 || i == 6)
        {
            buffer = new Knight(7, i, 'w');
        }
        else if(i == 2 || i == 5)
        {
            buffer = new Bishop(7, i, 'w');
        }
        else if(i == 3)
        {
            buffer = new Queen(7, i, 'w');
        }
        else if(i == 4)
        {
            buffer = new King(7, i, 'w');
        }

        board[7][i] = buffer;
    }

}

ChessBoard::~ChessBoard()
{
    for(unsigned int i = 0; i < board.size(); i++)
    {
        for(unsigned int j = 0; j < board[0].size(); j++)
        {
            if(board[i][j] != nullptr)
            {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
        board[i].clear();
    }
    board.clear();
}

void ChessBoard::Move(int rFrom, int cFrom, int rTo, int cTo)
{

}
