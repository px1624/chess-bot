#include "chess_board.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

void ChessBoard::Print()
{
    string solidRow = "\t  +----+----+----+----+----+----+----+----+";
    string buffRow  = "\t  |    |    |    |    |    |    |    |    |";

    cout << endl;
    cout << "\t     " << 'A';
    for(int i = 1; i < col_size; i++)
        cout << "    " << char('A' + i);
    cout << endl;
    cout << solidRow << endl;


    for(int i = 0; i < row_size; i++)
    {
        //cout << buffRow << endl;
        cout << "\t" << 8 - i << " |";
        for(int j = 0;  j < col_size; j++){
            cout << " " << (board[i][j] == nullptr ? "  ": board[i][j]->GetPieceStr()) << " |";
        }
        cout << endl;
        //cout << buffRow << endl;
        cout << solidRow << endl;
    }  
}

void ChessBoard::PrintAllValidMoves()
{
    Piece* p;
    multimap<int, int> m;
    multimap<int, int>::iterator it;
    int r, c;

    for(int i = 0; i < row_size; i++)
    {
        for(int j = 0; j < col_size; j++)
        {
            p = board[i][j];
            if(p != nullptr)
            {
                m.clear();
                p->ValidMoves(m, board);
                p->GetPosition(r, c);

                printf("%s (%d, %c):", p->GetPieceStr().c_str(), 8 - r, static_cast<char>(c+'A'));
                for(it = m.begin(); it != m.end(); ++it)
                    printf(" (%d, %c)", 8 - it->first, static_cast<char>(it->second + 'A'));
                printf("\n");
            }
        }
    }
}

bool ChessBoard::PawnPCheck(int &row, int &col){

	for(int i = 0;i < board[0].size();i++){
		if( board[0][i] != nullptr && board[0][i]->GetColor() == 'w' && board[0][i]->GetSymbol() == 'P'){
			row = 0;
			col = i;
			return true;
		}
	}
	
	for(int i = 0;i < board[7].size();i++){
		if( board[7][i] != nullptr && board[7][i]->GetColor() == 'b' && board[7][i]->GetSymbol() == 'P'){
			row = 7;
			col = i;
			return true;
		}
	}

	return false;
}


void ChessBoard::PawnPromotion(int row, int col){

	string npiece;
	char toColor;
	unsigned int i;
	cout<<"Pawn Promotion! Please select a piece to switch out the pawn with: "<<endl;
	cout<<"Please enter 'queen' 'bishop' 'knight' or 'rook'"<<endl;
	cin>>npiece;

	toColor = board[row][col]->GetColor();

	if(toColor == 'w'){
		for( i = 0; i < whites.size();i++){
			if(whites[i] == board[row][col])
				break;
		}
	}
	else if(toColor == 'b'){
		
		for( i = 0; i < blacks.size();i++){
			if(blacks[i] == board[row][col])
				break;
		}

	}


	if(npiece == "queen"){
		
		if(toColor == 'w'){
			delete board[row][col];
			board[row][col] = new Queen(row, col, 'w');
			whites[i] = board[row][col];
		}
		
		if(toColor == 'b'){
			delete board[row][col];
			board[row][col] = new Queen(row, col, 'b');
			blacks[i] = board[row][col];
		}
		
	}
	
	else if(npiece == "bishop"){
		
		if(toColor == 'w'){
			delete board[row][col];
			board[row][col] = new Bishop(row, col, 'w');
			whites[i] = board[row][col];
		}
		
		if(toColor == 'b'){
			delete board[row][col];
			board[row][col] = new Bishop(row, col, 'b');
			blacks[i] = board[row][col];
		}
		
	}

	else if(npiece == "knight"){
		
		if(toColor == 'w'){
			delete board[row][col];
			board[row][col] = new Knight(row, col, 'w');
			whites[i] = board[row][col];
		}
		
		if(toColor == 'b'){
			delete board[row][col];
			board[row][col] = new Knight(row, col, 'b');
			blacks[i] = board[row][col];
		}
		
	}

	else if(npiece == "rook"){
		
		if(toColor == 'w'){
			delete board[row][col];
			board[row][col] = new Rook(row, col, 'w');
			whites[i] = board[row][col];
		}
		
		if(toColor == 'b'){
			delete board[row][col];
			board[row][col] = new Rook(row, col, 'b');
			blacks[i] = board[row][col];
		}
		
	}



}

ChessBoard::ChessBoard() : turnCount(0), board(row_size, vector<Piece*>(col_size, nullptr))
{
    Piece* buffer;
	turnCount = 0;

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
    //turnCount stores the count before the move
    //0 is white's move because white moves first
    bool isBlackTurn = turnCount % 2;
    Piece* src = board[rFrom][cFrom];
    multimap<int, int> moves;
    if(src == nullptr)
        cout << "Invalid move! There is no chess piece on this cell.\n";
    
    if((isBlackTurn && src->GetColor() == 'w') || (!isBlackTurn && src->GetColor() == 'b'))
        cout << "Invalid move! You can't move another player's piece.\n";

    src->ValidMoves(moves, board);

    //if user's move is contained within the chosen piece's valid moves map
    if(ContainsMove(moves, rTo, cTo))
    {
        //remove destination piece
        RemovePiece(rTo, cTo);
        //move source to destination
        board[rTo][cTo] = src;
        //set source to nullptr
        board[rFrom][cFrom] = nullptr;

		board[rTo][cTo]->SetPosition(rTo, cTo);
    }
    else
        cout << "Invalid move! This piece cannot move here.";

	turnCount++;
}

bool ChessBoard::ContainsMove(multimap<int, int> &moves, int r, int c)
{
    bool contains = false;
    multimap<int, int>::iterator it;
    for(it = moves.begin(); it != moves.end(); ++it)
    {
        if(it->first == r && it->second == c)
        {
            contains = true;
            break;
        }
    }
    return contains;
}

void ChessBoard::RemovePiece(int r, int c)
{
    Piece* p = board[r][c];
    if(p == nullptr)
        return;
    
    vector<Piece*> *vP;
    //pick whether to delete from white
    if(p->GetColor() == 'w')
        vP = &whites;
    else
        vP = &blacks;

    //erase-remove idiom
    //remove a piece from either whites or blacks
    vP->erase(remove(vP->begin(), vP->end(), p), vP->end());
    board[r][c] = nullptr;
    delete p;
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

int ChessBoard::check(int turn){

	std::multimap<int, int> kmoves;
	std::multimap<int, int>::iterator mit;
	int krow, kcol;
	if(turn == 2){
		
		for(unsigned int i = 0; i < blacks.size();i++){
			if(blacks[i]->GetSymbol() == 'K'){
				blacks[i]->GetPosition(krow, kcol);
				break;
			}
		}

		for(unsigned int i = 0;i < whites.size();i++){
			
			kmoves.clear();
			whites[i]->ValidMoves(kmoves, this->board);
			for(mit = kmoves.begin(); mit != kmoves.end();++mit){
				
				if(mit->first ==  krow && mit->second == kcol){
					return 1;
				}
			}
		}
		return 0;
	}
	else{
		
		for(unsigned int i = 0; i < whites.size();i++){
			if(whites[i]->GetSymbol() == 'K'){
				whites[i]->GetPosition(krow, kcol);
				break;
			}
		}
	
		for(unsigned int i = 0;i < blacks.size();i++){
			
			kmoves.clear();
			blacks[i]->ValidMoves(kmoves, this->board);
			for(mit = kmoves.begin(); mit != kmoves.end();++mit){
	
				if(mit->first == krow && mit->second == kcol){
					
					return 1;
				}
			}
		}
		return 0;

	}
}

