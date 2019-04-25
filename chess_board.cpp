/*chess_board.cpp - Written by Michael Wermert and Pengda Xie
This file contains the method definitions for the ChessBoard class
defined in chess_board.h.
*/
#include "chess_board.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

//scores a move based on how many pieces can be taken by both sides and returns them in a map keyed on the score
//used for the 1p mode
void ChessBoard::GenerateMove(multimap <int, AIMove, std::greater<int> > &allMoves){

	multimap <int, AIMove, std::greater<int> >::iterator allMit;
	multimap<int, int> moves;
	multimap<int, int>::iterator mit;
	multimap<int, int> whiteMoves;
	multimap<int, int>::iterator wmit;
	multimap<int, int> secondMoves;
	multimap<int, int>::iterator secondMit;
	AIMove temp;
	int r, c;
	int tempScore = 0;

	//goes through all the moves for every black piece and calculates all of the white pieces that it can hit
	for(unsigned int i = 0;i < blacks.size();i++){
		moves.clear();
		blacks[i]->GetPosition(r, c);
		blacks[i]->ValidMoves(moves, this->board);
		temp.rFrom = r;
		temp.cFrom = c;
		for(mit = moves.begin();mit != moves.end(); ++mit){
			secondMoves.clear();
			tempScore = 0;	
			temp.rTo = mit->first;
			temp.cTo = mit->second;
			if(this->board[mit->first][mit->second] != nullptr)
				tempScore += abs(this->board[mit->first][mit->second]->getPieceValue());		
			
			Move(r, c, mit->first, mit->second, false);
			this->board[mit->first][mit->second]->ValidMoves(secondMoves, this->board);
			for(secondMit = secondMoves.begin();secondMit != secondMoves.end(); ++secondMit){
				if(this->board[secondMit->first][secondMit->second] != nullptr)
					tempScore += abs(this->board[secondMit->first][secondMit->second]->getPieceValue());

			}

			//goes through all of the white pieces and subtracts all of the black pieces that they can hit from the score
			for(int j = 0; j < whites.size();j++){
				whites[j]->ValidMoves(whiteMoves, this->board);
				for(wmit = whiteMoves.begin();wmit != whiteMoves.end();++wmit){
					if(this->board[wmit->first][wmit->second] != nullptr)
						tempScore -= abs(this->board[wmit->first][wmit->second]->getPieceValue());

				}
			}

			//inserts the move into the multimap keyed on score
			UndoMove();
			allMoves.insert(std::pair<int,AIMove>(tempScore, temp));

		}
	}

}


//determines if one side is in checkmate, returns true if yes
bool ChessBoard::CheckMate(){

	multimap<int, int> moves;
	multimap<int, int>::iterator mit;
	int r, c;
	if(IsWhiteTurn()){

		//if no move that the white pieces can make results in the check being ended, black wins and it returns true
		//else it returns false
		for(int i = 0;i < whites.size();i++){
			moves.clear();
			whites[i]->ValidMoves(moves, this->board);
			whites[i]->GetPosition(r, c);
			for(mit = moves.begin();mit != moves.end();++mit){
				
				Move(r, c, mit->first, mit->second, false);
				if(check() == 0){
					UndoMove();
		
					return false;
				}
				UndoMove();
			
			}

		}
		return true;

	}
	else{

		//if no move that the black pieces can make results in the check being ended, white wins and it returns true
		//else it returns false
		for(int i = 0;i < blacks.size();i++){
			moves.clear();
			blacks[i]->ValidMoves(moves, this->board);
			blacks[i]->GetPosition(r, c);
			for(mit = moves.begin();mit != moves.end();++mit){
				
				Move(r, c, mit->first, mit->second, false);
				if(check() == 0){
					UndoMove();
				
					return false;
				}
				UndoMove();
		
			}

		}
		return true;
	}

}

//updates the prevRow variable for the pawns so that the legality of en passant can be determined
void ChessBoard::EPCleanup(){

	int r, c;
	if(IsWhiteTurn()){
		for(int i = 0; i < whites.size();i++){
			if(whites[i]->GetSymbol() == 'P'){
				whites[i]->GetPosition(r, c);
				whites[i]->SetPrevRow(r);
				
			}
		}
	}

	else{
		for(int i = 0; i < blacks.size();i++){
			if(blacks[i]->GetSymbol() == 'P'){
				blacks[i]->GetPosition(r, c);
				blacks[i]->SetPrevRow(r);
				
			}
		}
	}
}

//prints out the chessboard in two different colors
void ChessBoard::Print()
{
    string solidRow = "\t  +----+----+----+----+----+----+----+----+";

    //print column indicator
    cout << endl;
    cout << "\t     " << 'A';
    for(int i = 1; i < col_size; i++)
        cout << "    " << char('A' + i);
    cout << endl;
    cout << solidRow << endl;


    //print chess pieces
    for(int i = 0; i < row_size; i++)
    {
        cout << "\t" << 8 - i << " |";
        for(int j = 0;  j < col_size; j++){
            //string bgColor = ((i + j) % 2 == 0)? "47" : "40";
            cout << " " << (board[i][j] == nullptr ? "  ": board[i][j]->GetPieceStr()) << " |";
        }
        cout << endl;
        cout << solidRow << endl;
    }  
}

//prints all valid moves that one team can make
void ChessBoard::PrintAllValidMoves()
{
    Piece* p;
    multimap<int, int> m;
    multimap<int, int>::iterator it;
    int r, c;
    //get white pieces in white's turn, and black pieces for black's turn
    vector<Piece*>* pieces = IsWhiteTurn() ? &whites : &blacks;

    for(int i = 0; i < (int)pieces->size(); i++)
    {
        p = (*pieces)[i];
        if(p != nullptr)
        {
            m.clear();
            //get valid moves and piece's current position
            p->ValidMoves(m, board);
            p->GetPosition(r, c);

            //print all valid moves for this piece
            printf("%s (%d, %c):", p->GetPieceStr().c_str(), 8 - r, static_cast<char>(c+'A'));
            for(it = m.begin(); it != m.end(); ++it)
                printf(" (%d, %c)", 8 - it->first, static_cast<char>(it->second + 'A'));
            printf("\n");
        }
    }
}

//checks if pawn promotion is available, returns location of the pawn by reference if it is available
bool ChessBoard::PawnPCheck(int &row, int &col){

	//checks whites
	for(int i = 0;i < board[0].size();i++){
		if( board[0][i] != nullptr && board[0][i]->GetColor() == 'w' && board[0][i]->GetSymbol() == 'P'){
			row = 0;
			col = i;
			return true;
		}
	}
	
	//checks blacks
	for(int i = 0;i < board[7].size();i++){
		if( board[7][i] != nullptr && board[7][i]->GetColor() == 'b' && board[7][i]->GetSymbol() == 'P'){
			row = 7;
			col = i;
			return true;
		}
	}

	return false;
}

//performs pawn promotion, user enters what kind of piece they want and the piece is exchanged
void ChessBoard::PawnPromotion(int row, int col){

	string npiece;
	char toColor;
	unsigned int i;

	//output and user inputs a piece
	cout<<"Pawn Promotion! Please select a piece to switch out the pawn with: "<<endl;
	cout<<"Please enter 'queen' 'bishop' 'knight' or 'rook'"<<endl;
	cin>>npiece;

	toColor = board[row][col]->GetColor();

	//finds correct pawn
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

	//exchanges a pawn for a queen
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
	
	//exchanges a pawn for a bishop
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

	//exchanges a pawn for a knight
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

	//exchanges a pawn for a rook
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

//constructor, initializes board so that all of the pieces are in the proper places
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
        if (buffer != nullptr)
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
        if(buffer != nullptr)
            whites.push_back(buffer);
    }

}

//destructor, deletes all pieces in the board, and then the whites and blacks vector
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

//undoes a move, used in move function and GenerateMove
void ChessBoard::UndoMove(){

	board[prevFromRow][prevFromCol] = board[prevToRow][prevToCol];
	board[prevFromRow][prevFromCol]->SetPosition(prevFromRow, prevFromCol);
    board[prevFromRow][prevFromCol]->DecMoveCount();

    //undo castle if king moved more than 1 space
    if(board[prevFromRow][prevFromCol]->GetSymbol() == 'K' &&
       abs(prevFromCol - prevToCol) > 1)
    {
        //determine rook to and from column position
        int rPrevToCol = (prevToCol == 6) ? 5 : 3;
        int rPrevFromCol = (prevToCol == 6) ? 7 : 0;
        //get rook
        Piece* rook = board[prevFromRow][rPrevToCol];
        //move rook back
        board[prevFromRow][rPrevFromCol] = rook;
        board[prevFromRow][rPrevToCol] = nullptr;
        //set new position and decrement movecount
        rook->SetPosition(prevFromRow, rPrevFromCol);
        rook->DecMoveCount();
    }

	//puts pawn back on the board if it was captured
	if(prevToSymbol == 'P'){
		board[prevToRow][ prevToCol] = new Pawn(prevToRow,  prevToCol, prevToColor);
		if(prevToColor == 'w')
			whites.push_back(board[prevToRow][ prevToCol]);
		else if(prevToColor == 'b')
			blacks.push_back(board[prevToRow][ prevToCol]);
	}

	//puts bishop back on the board if it was captured
	else if(prevToSymbol == 'B'){
		board[prevToRow][ prevToCol] = new Bishop(prevToRow,  prevToCol, prevToColor);
		if(prevToColor == 'w')
			whites.push_back(board[prevToRow][ prevToCol]);
		else if(prevToColor == 'b')
			blacks.push_back(board[prevToRow][ prevToCol]);
	}

	//puts knight back on the board if it was captured
	else if(prevToSymbol == 'N'){
		board[prevToRow][ prevToCol] = new Knight(prevToRow,  prevToCol, prevToColor);
		if(prevToColor == 'w')
			whites.push_back(board[prevToRow][ prevToCol]);
		else if(prevToColor == 'b')
			blacks.push_back(board[prevToRow][ prevToCol]);
	}

	//puts rook back on the board if it was captured
	else if(prevToSymbol == 'R'){
		board[prevToRow][ prevToCol] = new Rook(prevToRow,  prevToCol, prevToColor);
		if(prevToColor == 'w')
			whites.push_back(board[prevToRow][ prevToCol]);
		else if(prevToColor == 'b')
			blacks.push_back(board[prevToRow][ prevToCol]);
	}
	
	//puts queen back on the board if it was captured
	else if(prevToSymbol == 'Q'){
		board[prevToRow][ prevToCol] = new Queen(prevToRow,  prevToCol, prevToColor);
		if(prevToColor == 'w')
			whites.push_back(board[prevToRow][ prevToCol]);
		else if(prevToColor == 'b')
			blacks.push_back(board[prevToRow][ prevToCol]);
	}
	else
		board[prevToRow][ prevToCol] = nullptr;

    if(board[prevToRow][prevToCol] != nullptr)
        board[prevToRow][prevToCol]->SetMoveCount(prevToMoveCount);
}

//moves a piece from board[rFrom][cFrom] to board[rTo][cTo], returns true if it is possible
//false if it is not
bool ChessBoard::Move(int rFrom, int cFrom, int rTo, int cTo, bool EPFlag)
{
	bool EFlag;
    Piece* src = board[rFrom][cFrom];
    multimap<int, int> moves;
    
	//checks to make sure that there is a piece in board[rFrom][cFrom]
	if(src == nullptr)
    {
        cout << "Invalid move! There is no chess piece on this cell.\n";
        return false;
    }
    
	//checks to make sure the piece belongs to player whose turn it is
    if((IsWhiteTurn() && src->GetColor() == 'b') || (!IsWhiteTurn() && src->GetColor() == 'w'))
    {
        cout << "Invalid move! You can't move another player's piece.\n";
        return false;
    }

    src->ValidMoves(moves, board);

    //if user's move is contained within the chosen piece's valid moves map
    if(ContainsMove(moves, rTo, cTo))
    {	

        //record where a piece is moving from and to
		prevFromRow = rFrom;
		prevFromCol = cFrom;
		src->SetPrevRow(rFrom);
		prevFromColor = board[rFrom][cFrom]->GetColor();
		prevFromSymbol = board[rFrom][cFrom]->GetSymbol();

		prevToRow = rTo;
		prevToCol = cTo;
		if(board[rTo][cTo] == nullptr)
        {
			prevToColor = 'n';
            prevToSymbol = 'Z';
            prevToMoveCount = -1;
        }
		else
        {
			prevToColor = board[rTo][cTo]->GetColor();
            prevToSymbol = board[rTo][cTo]->GetSymbol();
            prevToMoveCount = board[rTo][cTo]->GetMoveCount();
        }

		if(src->GetSymbol() == 'P' && abs(cTo - cFrom) > 0 && board[rTo][cTo] == nullptr && EPFlag == true){
			EFlag = true;
		}
		else 
			EFlag = false;
		
        //remove destination piece
        RemovePiece(rTo, cTo);
        //move source to destination
        board[rTo][cTo] = src;
        //set source to nullptr
        board[rFrom][cFrom] = nullptr;

		board[rTo][cTo]->SetPosition(rTo, cTo);
        
        src->IncMoveCount();
		
        //if king performed a castle move
        //move rook as well
        if(src->GetSymbol() == 'K' && abs(cTo - cFrom) > 1)
        {
            int rOldCol = (cTo > cFrom)? 7 : 0;
            int rNewCol = (rOldCol == 7)? rOldCol - 2 : rOldCol + 3;
            Piece* rook = board[rFrom][rOldCol];
            board[rFrom][rNewCol] = rook;
            board[rFrom][rOldCol] = nullptr;
            rook->SetPosition(rFrom, rNewCol);
            rook->IncMoveCount();
        }
		
		if(EFlag == true){
			RemovePiece(rFrom, cTo);
		}

    }

	//outputs that the move is invalid and returns false
    else
    {
        cout << "Invalid move! This piece cannot move here."<<endl;
		return false;
	}

	return true;
}

//increments turnCount
void ChessBoard::incTurnCount(){

	turnCount++;

}

//returns turn count
int ChessBoard::GetTurnCount()
{
    return turnCount;
}

//checks if the moves map contains the move that is passed in
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

//removes a piece from the board
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

//returns the color for a piece
char ChessBoard::getSpaceColor(int r, int c){
	return board[r][c]->GetColor();
}

//returns what type of piece is at the passed in location
char ChessBoard::getSpaceType(int r, int c){
	return board[r][c]->GetSymbol();
}

//checks if the there is a piece on the space,
//returns true if board[r][c] is nullptr
bool ChessBoard::checkNull(int r, int c){

	if(board[r][c] == nullptr)
		return true;
	else
		return false;

}

//returns the pointer to a piece at board[r][c]
Piece *ChessBoard::getPiece(int r, int c){

	return board[r][c];

}

//returns a copy of the board
std::vector<std::vector <Piece*> > ChessBoard::getBoard(){

	return board;

}

//returns true if either team is in check
int ChessBoard::check(){

	std::multimap<int, int> kmoves;
	std::multimap<int, int>::iterator mit;
	int krow, kcol;

	//returns true if the black king is in check
	if(!IsWhiteTurn()){
		
		//finds position of the king
		for(unsigned int i = 0; i < blacks.size();i++){
			if(blacks[i]->GetSymbol() == 'K'){
				blacks[i]->GetPosition(krow, kcol);
				break;
			}
		}

		//determines if the black king is in check
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

	//determines if the white king is in check
	else{
		
		//finds location of white king
		for(unsigned int i = 0; i < whites.size();i++){
			if(whites[i]->GetSymbol() == 'K'){
				whites[i]->GetPosition(krow, kcol);
				break;
			}
		}
	
		//determines if white king is in check
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

//returns true if it is the white team's turn
bool ChessBoard::IsWhiteTurn()
{
    //turnCount records the count right before a player's move.
    //i.e. 0 means white's turn, after white moves, the count is incremented to 1
    //     1 is black's turn, 2 is white's turn and so on.
    //
    //all even turnCounts are whites turn and odds are blacks
    return (turnCount % 2 == 0);
}
