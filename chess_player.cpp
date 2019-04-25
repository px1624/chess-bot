/*chess_player.cpp - Written by Michael Wermert and Pengda Xie
Description - This is the file that contains the menu, the one player mode, and the 2 player mode.
The format for the user input is listed in the user manual.
*/
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

//one player mode
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

	//creates chess board
	ChessBoard game;
	multimap <int, int> moves;
	multimap <int, int>::iterator mit;

	while(true){


		//prints the board and prompts the appropriate player to move
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
		
		//human player's move
		if(game.IsWhiteTurn()){
			if(check == 0){
				while(moveCheck == false ){
					
					//checks if there is a stalemate, ends game if there is
					if(game.CheckMate() == true){
						cout<<"P"<<(turnCount+1)%2+1<<" wins by Stalemate!"<<endl;
						return;
					}


					cin>>s;
					
					transform(s.begin(), s.end(), s.begin(), ::toupper);
					
					//checks for the quit command
					if(s == "QUIT")
						return;
					
					//checks for the hint command
					else if(s == "HINT"){
						game.PrintAllValidMoves();
						hintFlag = true;
					}
					else
						hintFlag = false;
					
					//user input is processed
					if(hintFlag == false){
						row = stoi(s);

						cin>>col>>finRow>>finCol;

						row = 8 - row;
						finRow = 8 - finRow;
						numCol = toupper(col) - 'A';
						numFinCol = toupper(finCol) - 'A';
					}

					//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
					
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
					
					

					game.getPiece(row, numCol)->ValidMoves(moves, game.getBoard());	

					moveCheck = game.ContainsMove(moves, finRow, numFinCol);


					//checks to make sure the move is valid
					if(moveCheck == false)
						cout << "Invalid move! This piece cannot move here."<<endl;
					
				}

				//moves piece and checks if pawn promotion is available
				game.Move(row, numCol, finRow, numFinCol, true);	
				if(game.PawnPCheck(PProw, PPcol) == true)
					game.PawnPromotion(PProw, PPcol);

			}
			//occurs if human player is in check
			if(check == 1){
				
				//input processed exactly the same as above
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
						
							while(hintFlag == true || game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'b'){
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
						


						game.getPiece(row, numCol)->ValidMoves(moves, game.getBoard());	

						moveCheck = game.ContainsMove(moves, finRow, numFinCol);

						if(moveCheck == false)
							cout << "Invalid move! This piece cannot move here."<<endl;

					}



					game.Move(row, numCol, finRow, numFinCol, true);	

					//makes sure that the king is moved out of check
					check = game.check();

					if(check == 1){
						cout<<"Invalid Move! You must move the king out of check\n";
						game.UndoMove();
					}

				}

			}
		}

		//AI move
		else{

			allMoves.clear();
			
			//checks if the ai is in stalemate or check
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

			//generates a move and makes sure it does not put the king in check
			game.GenerateMove(allMoves);
			for(AImit = allMoves.begin();AImit != allMoves.end();++AImit){
				game.Move(AImit->second.rFrom, AImit->second.cFrom, AImit->second.rTo, AImit->second.cTo, false);
				if(game.check() == 0){
					game.UndoMove();
					break;
				}
				game.UndoMove();						
			}

			//moves piece and outputs how the bot moved
			game.Move(AImit->second.rFrom, AImit->second.cFrom, AImit->second.rTo, AImit->second.cTo, true);
			printf("Chess bot moved: %d %c %d %c\n", 8 - AImit->second.rFrom, AImit->second.cFrom + 'A',
					8 - AImit->second.rTo, AImit->second.cTo + 'A');
		}
		
		//increments turn count
		game.incTurnCount();
		turnCount++;
	}

}

//two player mode
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
	bool hintFlag = false;
	string s;


	ChessBoard game;
	multimap <int, int> moves;
	multimap <int, int>::iterator mit;

	while (true){

		//prints board and determines whether or not either player is in check
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
		
		//occurs if the players are in check, output is processed exactly the same way as above
		if(check == 0){
			while(moveCheck == false ){

				if(game.CheckMate() == true){
					cout<<"P"<<(turnCount+1)%2+1<<" wins by Stalemate!"<<endl;
					return;
				}


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

				//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece, for p1
				if(turnCount%2+1 == 1){
					while(hintFlag == true || game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'b'){
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
				//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece, for player 2
				else if(turnCount%2+1 == 2){
					while(hintFlag == true || game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'w'){
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

			}

			//moves piece and checks pawn promotion
			game.Move(row, numCol, finRow, numFinCol, true);	
			if(game.PawnPCheck(PProw, PPcol) == true)
				game.PawnPromotion(PProw, PPcol);

		}

		//occurs while a player is in check
		if(check == 1){
			
			//loop repeats until player is not in check
			while(check == 1){

				if(game.CheckMate() == true){
					cout<<"P"<<(turnCount+1)%2+1<<" wins!"<<endl;
					return;
				}

				moveCheck = false;
				//input processed the same way as in the one player mode
				while(moveCheck == false){

				
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

					//checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
					if(turnCount%2+1 == 1){
						while(hintFlag == true || game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'b'){
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
						while(hintFlag == true || game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'w'){
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

					//checks to make sure move is valid
					game.getPiece(row, numCol)->ValidMoves(moves, game.getBoard());	

					moveCheck = game.ContainsMove(moves, finRow, numFinCol);

					if(moveCheck == false)
						cout << "Invalid move! This piece cannot move here."<<endl;

				}

			

				//moves piece
				game.Move(row, numCol, finRow, numFinCol, true);	

				//makes sure the king moves out of check
				check = game.check();
				
				if(check == 1){
					cout<<"Invalid Move! You must move the king out of check\n";
					game.UndoMove();
				}

			}

		}

		//increments turn count
		game.incTurnCount();
		turnCount++;
	}


}
