#include "chess_board.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

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
			for(int j = 0; j < whites.size();j++){
				whites[j]->ValidMoves(whiteMoves, this->board);
				for(wmit = whiteMoves.begin();wmit != whiteMoves.end();++wmit){
					if(this->board[wmit->first][wmit->second] != nullptr)
						tempScore -= abs(this->board[wmit->first][wmit->second]->getPieceValue());

				}
			}

			UndoMove();
			allMoves.insert(std::pair<int,AIMove>(tempScore, temp));

		}
	}

}

void ChessBoard::GenerateMove_2(multimap <int, AIMove, std::greater<int> > &allMoves)
{
}

bool ChessBoard::CheckMate(){

	multimap<int, int> moves;
	multimap<int, int>::iterator mit;
	int r, c;
	if(IsWhiteTurn()){

		for(int i = 0;i < whites.size();i++){
			moves.clear();
			whites[i]->ValidMoves(moves, this->board);
			whites[i]->GetPosition(r, c);
			for(mit = moves.begin();mit != moves.end();++mit){
				
				Move(r, c, mit->first, mit->second, false);
				if(check() == 0){
					UndoMove();
				//	cout<<r<<" "<<c<<"can move to "<<mit->first<<" "<<mit->second<<endl;
					return false;
				}
				UndoMove();
			//	cout<<"cannot move to "<<mit->first<<" "<<mit->second<<endl;
			}

		}
		return true;

	}
	else{

		for(int i = 0;i < blacks.size();i++){
			moves.clear();
			blacks[i]->ValidMoves(moves, this->board);
			blacks[i]->GetPosition(r, c);
			for(mit = moves.begin();mit != moves.end();++mit){
				
				Move(r, c, mit->first, mit->second, false);
				if(check() == 0){
					UndoMove();
				//	cout<<r<<" "<<c<<"can move to "<<mit->first<<" "<<mit->second<<endl;
					return false;
				}
				UndoMove();
		//		cout<<"cannot move to "<<mit->first<<" "<<mit->second<<endl;
			}

		}
		return true;
	}

}

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
            //string bgColor = ((i + j) % 2 == 0)? "47" : "40";
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
    vector<Piece*>* pieces = IsWhiteTurn() ? &whites : &blacks;

    for(int i = 0; i < (int)pieces->size(); i++)
    {
            p = (*pieces)[i];
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

	if(prevToSymbol == 'P'){
		board[prevToRow][ prevToCol] = new Pawn(prevToRow,  prevToCol, prevToColor);
		if(prevToColor == 'w')
			whites.push_back(board[prevToRow][ prevToCol]);
		else if(prevToColor == 'b')
			blacks.push_back(board[prevToRow][ prevToCol]);
	}

	else if(prevToSymbol == 'B'){
		board[prevToRow][ prevToCol] = new Bishop(prevToRow,  prevToCol, prevToColor);
		if(prevToColor == 'w')
			whites.push_back(board[prevToRow][ prevToCol]);
		else if(prevToColor == 'b')
			blacks.push_back(board[prevToRow][ prevToCol]);
	}

	else if(prevToSymbol == 'N'){
		board[prevToRow][ prevToCol] = new Knight(prevToRow,  prevToCol, prevToColor);
		if(prevToColor == 'w')
			whites.push_back(board[prevToRow][ prevToCol]);
		else if(prevToColor == 'b')
			blacks.push_back(board[prevToRow][ prevToCol]);
	}

	else if(prevToSymbol == 'R'){
		board[prevToRow][ prevToCol] = new Rook(prevToRow,  prevToCol, prevToColor);
		if(prevToColor == 'w')
			whites.push_back(board[prevToRow][ prevToCol]);
		else if(prevToColor == 'b')
			blacks.push_back(board[prevToRow][ prevToCol]);
	}
	
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

bool ChessBoard::Move(int rFrom, int cFrom, int rTo, int cTo, bool EPFlag)
{
	bool EFlag;
    Piece* src = board[rFrom][cFrom];
    multimap<int, int> moves;
    if(src == nullptr)
    {
        cout << "Invalid move! There is no chess piece on this cell.\n";
        return false;
    }
    
    if((IsWhiteTurn() && src->GetColor() == 'b') || (!IsWhiteTurn() && src->GetColor() == 'w'))
    {
        cout << "Invalid move! You can't move another player's piece.\n";
        return false;
    }

    src->ValidMoves(moves, board);

    //if user's move is contained within the chosen piece's valid moves map
    if(ContainsMove(moves, rTo, cTo))
    {	

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
    else
    {
        cout << " 2nd Invalid move! This piece cannot move here."<<endl;
		return false;
	}

	return true;
}

void ChessBoard::incTurnCount(){

	turnCount++;

}

int ChessBoard::GetTurnCount()
{
    return turnCount;
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

int ChessBoard::check(){

	std::multimap<int, int> kmoves;
	std::multimap<int, int>::iterator mit;
	int krow, kcol;
	if(!IsWhiteTurn()){
		
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

bool ChessBoard::IsWhiteTurn()
{
    //turnCount records the count right before a player's move.
    //i.e. 0 means white's turn, after white moves, the count is incremented to 1
    //     1 is black's turn, 2 is white's turn and so on.
    //
    //all even turnCounts are whites turn and odds are blacks
    return (turnCount % 2 == 0);
}
