#include "piece.h"
#include "chess_board.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

void OnePlayerMode();
void TwoPlayerMode();

int main(){

	int userResponse;


	//displays game menu, user must enter 1 2 or 3 to choose an option

	while (true){

		cout<<"\t\tUltimate Chess!"<<endl<<endl;
		cout<<"\t\tMain Menu:"<<endl<<endl;
		cout<<"\t\t1: One Player"<<endl;
		cout<<"\t\t2: Two Player"<<endl;
		cout<<"\t\t3: Quit"<<endl<<endl;
		cout<<"\t\tPlease Enter 1, 2, or 3"<<endl;


		while(!(cin>>userResponse)){
			cout<<"Invalid Input: Menu Input must be '1' '2' or '3'"<<endl<<endl;
			string dump;
			cin.clear();
			cin >> dump;
		}

		if(userResponse != 1 && userResponse != 2 && userResponse != 3)
			cout<<"Invalid Input: Menu Input must be '1' '2' or '3'"<<endl<<endl;

		if(userResponse == 1)
			OnePlayerMode();

		if(userResponse == 2)
			TwoPlayerMode();


		if(userResponse == 3)
			return 0;

	}


}

void OnePlayerMode(){


	int row;
	int numCol;
	char col;
	int finRow;
	int numFinCol;
	int PProw, PPcol;
	char finCol;
	bool moveCheck = false;
	bool newCheck = 1;
	bool check = 0;
	int turnCount = 0;
	string s;
	bool hintFlag = false;
	multimap <int, AIMove, std::greater<int> > allMoves;
	multimap <int, AIMove, std::greater<int> >::iterator AImit;

	ChessBoard game;
	multimap <int, int> moves;
	multimap <int, int>::iterator mit;

	while(true){


		game.Print();
		moves.clear();
		newCheck = 1;
		moveCheck = false;
		game.EPCleanup();
		check = game.check();
		if(check == 1)
			cout<<"CHECK!"<<endl;

		cout<<"P"<< (game.IsWhiteTurn()? "1" : "2") <<" please enter your move: \n";

		//DATA MUST BE ENTERED IN THE FORM ROWOFYOURPIECE COLOFYOURPIECE ROWOFNEWSPACE COLOFNEWSPACE EX. 2 A 2 B
		if(game.IsWhiteTurn()){
			if(check == 0){
				while(moveCheck == false || newCheck == 1){

					if(game.CheckMate() == true){
						cout<<"P"<<(turnCount+1)%2+1<<" wins by Stalemate!"<<endl;
						return;
					}


					cin>>s;
					//to uppercase
					transform(s.begin(), s.end(), s.begin(), ::toupper);
					if(s == "QUIT")
						return;
					else if(s == "HINT"){
						game.PrintAllValidMoves();
						hintFlag = true;
					}
					else
						hintFlag = false;

					if(hintFlag == false){
						row = stoi(s);

						cin>>col>>finRow>>finCol;

						row = 8 - row;
						finRow = 8 - finRow;
						numCol = toupper(col) - 'A';
						numFinCol = toupper(finCol) - 'A';
					}

					//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
					if(turnCount%2+1 == 1){
						while(hintFlag == true ||game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'b'){
							cout<<"Please enter a valid piece\n";

							cin>>s;

							transform(s.begin(), s.end(), s.begin(), ::toupper);
							if(s == "QUIT")
								return;
							else if(s == "HINT"){
								game.PrintAllValidMoves();
								hintFlag = true;
							}						                
							else
								hintFlag = false;

							if(hintFlag == false){
								row = stoi(s);

								cin>>col>>finRow>>finCol;


								row = 8 - row;
								finRow = 8 - finRow;
								numCol = toupper(col) - 'A';
								numFinCol = toupper(finCol) - 'A';
							}
						}
					}
					//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
					else if(turnCount%2+1 == 2){
						while(game.checkNull(hintFlag == true || row, numCol) == true || game.getSpaceColor(row, numCol) == 'w' ){
							cout<<"Please enter a valid piece\n";

							cin>>s;

							transform(s.begin(), s.end(), s.begin(), ::toupper);
							if(s == "QUIT")
								return;

							else if(s == "HINT"){
								game.PrintAllValidMoves();
								hintFlag = true;
							}						                
							else
								hintFlag = false;

							if(hintFlag == false){
								row = stoi(s);

								cin>>col>>finRow>>finCol;


								row = 8 - row;
								finRow = 8 - finRow;
								numCol = toupper(col) - 'A';
								numFinCol = toupper(finCol) - 'A';
							}
							
						}
					}

					game.getPiece(row, numCol)->ValidMoves(moves, game.getBoard());	

					moveCheck = game.ContainsMove(moves, finRow, numFinCol);


					//checks to make sure the move is valid
					if(moveCheck == false)
						cout << "Invalid move! This piece cannot move here."<<endl;

					//makes sure that the move does not put the king in danger
					//do not need to check if king is moving because king
					//by default cannot move into a check
					Piece* tmp = game.getPiece(row, numCol);
					bool moved = false;
					if(tmp != nullptr && tmp->GetSymbol() != 'K')
					{
						moved = game.Move(row, numCol, finRow, numFinCol, false);
					}
					newCheck = game.check();
					if(newCheck == 1){
						cout <<"Cannot put the king in danger!"<<endl;
					}
					if(moved)
						game.UndoMove();
				}

				/* uncomment this to debug
				   cout << "Valid moves for this piece:\n";
				   for(mit = moves.begin(); mit != moves.end();++mit)
				   cout<< 8 - mit->first << " " << static_cast<char>(mit->second + 'A')<<endl;
				   */

				game.Move(row, numCol, finRow, numFinCol, true);	
				if(game.PawnPCheck(PProw, PPcol) == true)
					game.PawnPromotion(PProw, PPcol);

			}
			if(check == 1){

				while(check == 1){

					if(game.CheckMate() == true){
						cout<<"P"<<(turnCount+1)%2+1<<" wins!"<<endl;
						return;
					}

					moveCheck = false;
					while(moveCheck == false){


						cin>>s;

						transform(s.begin(), s.end(), s.begin(), ::toupper);
						if(s == "QUIT")
							return;

						row = stoi(s);

						cin>>col>>finRow>>finCol;

						row = 8 - row;
						finRow = 8 - finRow;
						numCol = toupper(col) - 'A';
						numFinCol = toupper(finCol) - 'A';

						cout<<row << numCol << finRow << numFinCol <<endl;
						//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
						if(turnCount%2+1 == 1){
							while(game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'b'){
								cout<<"Please enter a valid piece\n";

								cin>>s;

								transform(s.begin(), s.end(), s.begin(), ::toupper);
								if(s == "QUIT")
									return;

								row = stoi(s);

								cin>>col>>finRow>>finCol;


								row = 8 - row;
								finRow = 8 - finRow;
								numCol = toupper(col) - 'A';
								numFinCol = toupper(finCol) - 'A';
							}
						}
						//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
						else if(turnCount%2+1 == 2){
							while(game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'w'){
								cout<<"Please enter a valid piece\n";

								cin>>s;

								transform(s.begin(), s.end(), s.begin(), ::toupper);
								if(s == "QUIT")
									return;

								row = stoi(s);

								cin>>col>>finRow>>finCol;

								row = 8 - row;
								finRow = 8 - finRow;
								numCol = col - 'A';
								numFinCol = toupper(finCol) - 'A';

							}
						}


						game.getPiece(row, numCol)->ValidMoves(moves, game.getBoard());	

						moveCheck = game.ContainsMove(moves, finRow, numFinCol);

						if(moveCheck == false)
							cout << "Invalid move! This piece cannot move here."<<endl;

					}

					//get moves and print them for debugging purpose


					game.Move(row, numCol, finRow, numFinCol, true);	

					//this shouldn't be neccessary anymore, since validMoves for king does a check
					//for if the target cell is under attack.
					check = game.check();

					if(check == 1){
						cout<<"Invalid Move! You must move the king out of check\n";
						game.UndoMove();
					}

				}

			}
		}
		else{

			allMoves.clear();

			if(check == 0){

				if(game.CheckMate() == true){
					cout<<"P"<<(turnCount+1)%2+1<<" wins by Stalemate!"<<endl;
					return;
				}												                
			}
			if(check == 1){

				if(game.CheckMate() == true){
					cout<<"P"<<turnCount%2+1<<" wins!"<<endl;
					return;					
				}

			}
			game.GenerateMove(allMoves);
			for(AImit = allMoves.begin();AImit != allMoves.end();++AImit){
				game.Move(AImit->second.rFrom, AImit->second.cFrom, AImit->second.rTo, AImit->second.cTo, false);
				if(game.check() == 0){
					game.UndoMove();
					break;
				}
				game.UndoMove();						
			}
			game.Move(AImit->second.rFrom, AImit->second.cFrom, AImit->second.rTo, AImit->second.cTo, true);
			printf("Chess bot moved: %d %c %d %c\n", 8 - AImit->second.rFrom, AImit->second.cFrom + 'A',
					8 - AImit->second.rTo, AImit->second.cTo + 'A');
		}

		game.incTurnCount();
		turnCount++;
	}

}
void TwoPlayerMode(){

	int row;
	int numCol;
	char col;
	int finRow;
	int numFinCol;
	int PProw, PPcol;
	char finCol;
	bool moveCheck = false;
	bool newCheck = 1;
	bool check = 0;
	int turnCount = 0;
	string s;


	ChessBoard game;
	multimap <int, int> moves;
	multimap <int, int>::iterator mit;

	while (true){


		game.Print();
		moves.clear();
		newCheck = 1;
		moveCheck = false;
		game.EPCleanup();
		check = game.check();
		if(check == 1)
			cout<<"CHECK!"<<endl;

		cout<<"P"<< (game.IsWhiteTurn()? "1" : "2") <<" please enter your move: \n";

		//DATA MUST BE ENTERED IN THE FORM ROWOFYOURPIECE COLOFYOURPIECE ROWOFNEWSPACE COLOFNEWSPACE EX. 2 A 2 B

		if(check == 0){
			while(moveCheck == false || newCheck == 1){

				if(game.CheckMate() == true){
					cout<<"P"<<(turnCount+1)%2+1<<" wins by Stalemate!"<<endl;
					return;
				}


				cin>>s;
				//to uppercase
				transform(s.begin(), s.end(), s.begin(), ::toupper);
				if(s == "QUIT")
					return;

				row = stoi(s);

				cin>>col>>finRow>>finCol;

				row = 8 - row;
				finRow = 8 - finRow;
				numCol = toupper(col) - 'A';
				numFinCol = toupper(finCol) - 'A';

				//			cout<<row << numCol << finRow << numFinCol <<endl;

				//		cout<<row<<" "<<numCol<<endl;
				//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
				if(turnCount%2+1 == 1){
					while(game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'b'){
						cout<<"Please enter a valid piece\n";

						cin>>s;

						transform(s.begin(), s.end(), s.begin(), ::toupper);
						if(s == "QUIT")
							return;

						row = stoi(s);

						cin>>col>>finRow>>finCol;


						row = 8 - row;
						finRow = 8 - finRow;
						numCol = toupper(col) - 'A';
						numFinCol = toupper(finCol) - 'A';
					}
				}
				//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
				else if(turnCount%2+1 == 2){
					while(game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'w'){
						cout<<"Please enter a valid piece\n";

						cin>>s;

						transform(s.begin(), s.end(), s.begin(), ::toupper);
						if(s == "QUIT")
							return;

						row = stoi(s);

						cin>>col>>finRow>>finCol;

						row = 8 - row;
						finRow = 8 - finRow;
						numCol = toupper(col) - 'A';
						numFinCol = toupper(finCol) - 'A';

					}
				}


				game.getPiece(row, numCol)->ValidMoves(moves, game.getBoard());	

				moveCheck = game.ContainsMove(moves, finRow, numFinCol);


				//checks to make sure the move is valid
				if(moveCheck == false)
					cout << "Invalid move! This piece cannot move here."<<endl;

				//makes sure that the move does not put the king in danger
				//do not need to check if king is moving because king
				//by default cannot move into a check
				Piece* tmp = game.getPiece(row, numCol);
				bool moved = false;
				if(tmp != nullptr && tmp->GetSymbol() != 'K')
				{
					moved = game.Move(row, numCol, finRow, numFinCol, false);
				}
				newCheck = game.check();
				if(newCheck == 1){
					cout <<"Cannot put the king in danger!"<<endl;
				}
				if(moved)
					game.UndoMove();
			}

			/* debug message
			   cout << "Valid moves for this piece:\n";
			   for(mit = moves.begin(); mit != moves.end();++mit)
			   cout<< 8 - mit->first << " " << static_cast<char>(mit->second + 'A')<<endl;
			   */

			game.Move(row, numCol, finRow, numFinCol, true);	
			if(game.PawnPCheck(PProw, PPcol) == true)
				game.PawnPromotion(PProw, PPcol);

		}
		if(check == 1){

			while(check == 1){

				if(game.CheckMate() == true){
					cout<<"P"<<(turnCount+1)%2+1<<" wins!"<<endl;
					return;
				}

				moveCheck = false;
				while(moveCheck == false){


					cin>>s;

					transform(s.begin(), s.end(), s.begin(), ::toupper);
					if(s == "QUIT")
						return;

					row = stoi(s);

					cin>>col>>finRow>>finCol;

					row = 8 - row;
					finRow = 8 - finRow;
					numCol = toupper(col) - 'A';
					numFinCol = toupper(finCol) - 'A';

					cout<<row << numCol << finRow << numFinCol <<endl;
					//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
					if(turnCount%2+1 == 1){
						while(game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'b'){
							cout<<"Please enter a valid piece\n";

							cin>>s;

							transform(s.begin(), s.end(), s.begin(), ::toupper);
							if(s == "QUIT")
								return;

							row = stoi(s);

							cin>>col>>finRow>>finCol;


							row = 8 - row;
							finRow = 8 - finRow;
							numCol = toupper(col) - 'A';
							numFinCol = toupper(finCol) - 'A';
						}
					}
					//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
					else if(turnCount%2+1 == 2){
						while(game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'w'){
							cout<<"Please enter a valid piece\n";

							cin>>s;

							transform(s.begin(), s.end(), s.begin(), ::toupper);
							if(s == "QUIT")
								return;

							row = stoi(s);

							cin>>col>>finRow>>finCol;

							row = 8 - row;
							finRow = 8 - finRow;
							numCol = col - 'A';
							numFinCol = toupper(finCol) - 'A';

						}
					}


					game.getPiece(row, numCol)->ValidMoves(moves, game.getBoard());	

					moveCheck = game.ContainsMove(moves, finRow, numFinCol);

					if(moveCheck == false)
						cout << "Invalid move! This piece cannot move here."<<endl;

				}

				//get moves and print them for debugging purpose


				game.Move(row, numCol, finRow, numFinCol, true);	

				//this shouldn't be neccessary anymore, since validMoves for king does a check
				//for if the target cell is under attack.
				check = game.check();

				if(check == 1){
					cout<<"Invalid Move! You must move the king out of check\n";
					game.UndoMove();
				}

			}

		}


		game.incTurnCount();
		turnCount++;
	}


}
