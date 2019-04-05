#include "chess_board.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

void ChessBoard::Print()
{
    string solidRow = "\t  +----+----+----+----+----+----+----+----+";
    string buffRow  = "\t  |    |    |    |    |    |    |    |    |";


    cout << endl;
    cout << "\t     " << 'A';
    for(unsigned int i = 1; i < board[0].size(); i++)
        cout << "    " << char('A' + i);
    cout << endl;
    cout << solidRow << endl;


    for(unsigned int i = 0; i < board.size();i++)
    {
        //cout << buffRow << endl;
        cout << "\t" << 8 - i << " |";
        for(unsigned int j = 0;  j < board[i].size();j++){
            cout << " " << (board[i][j] == nullptr ? "  ": board[i][j]->GetPieceStr()) << " |";
        }
        cout << endl;
        //cout << buffRow << endl;
        cout << solidRow << endl;
    }  
}

ChessBoard::ChessBoard(): board(8, vector<Piece*>(8, nullptr))
{
    Piece* buffer;

    //place black pawns
    for(unsigned int i = 0; i < board[1].size(); i++)
    {
        //make pawn
        buffer = new Pawn(1, i, 'b');
        //place it on board
        board[1][i] = buffer;
        //add piece to blacks
        blacks.push_back(buffer);
    }
    
    //place white pawns
    for(unsigned int i = 0; i < board[6].size(); i++)
    {
        //make pawn
        buffer = new Pawn(6, i, 'w');
        //place it on board
        board[6][i] = buffer;
        //add piece to whites
        whites.push_back(buffer);
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
        blacks.push_back(buffer);
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
        whites.push_back(buffer);
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

    blacks.clear();
    whites.clear();
}

void ChessBoard::Move(int rFrom, int cFrom, int rTo, int cTo)
{

}

char ChessBoard::getSpaceColor(int r, int c){
	return board[r][c]->GetColor();
}


char ChessBoard::getSpaceType(int r, int c){
	return board[r][c]->GetSymbol();
}

bool ChessBoard::checkNull(int r, int c){

	if(board[r][c] == nullptr)
		return true;
	else
		return false;

}


Piece *ChessBoard::getPiece(int r, int c){

	return board[r][c];

}



std::vector<std::vector <Piece*> > ChessBoard::getBoard(){

	return board;

}

