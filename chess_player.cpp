#include <iostream>
#include <vector>
#include <string>
#include "piece.h"
#include "chess_board.h"

using namespace std;


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
			cin.clear();
		}

		if(userResponse != 1 && userResponse != 2 && userResponse != 3)
			cout<<"Invalid Input: Menu Input must be '1' '2' or '3'"<<endl<<endl;
	
		if(userResponse == 2)
			TwoPlayerMode();
		

		if(userResponse == 3)
			return 0;
	
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
	bool check;
    int turnCount = 0;
    

    ChessBoard game;
    multimap <int, int> moves;
    multimap <int, int>::iterator mit;

    for(int i = 0;i<50;i++){
		
		game.Print();
        moves.clear();
		moveCheck = false;
		check = game.check(turnCount%2+1);
		if(check == 1)
			cout<<"CHECK!"<<endl;

        cout<<"P"<<turnCount%2+1<<" please enter your move: \n";

        //DATA MUST BE ENTERED IN THE FORM ROWOFYOURPIECE COLOFYOURPIECE ROWOFNEWSPACE COLOFNEWSPACE EX. 2 A 2 B
//		if(check == 0){
		while(moveCheck == false){


	        cin>> row >> col >> finRow >> finCol;

			row = 8 - row;
			finRow = 8 - finRow;
		     numCol = col - 'A';
			numFinCol = finCol - 'A';


//		cout<<row<<" "<<numCol<<endl;
        //checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
	        if(turnCount%2+1 == 1){
			    while(game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'b'){
					cout<<"Please enter a valid piece\n";

	                cin>> row >> col >> finRow >> finCol;

					row = 8 - row;
					finRow = 8 - finRow;
		            numCol = col - 'A';
	                numFinCol = finCol - 'A';
		        }
	        }
		    //checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
	        else if(turnCount%2+1 == 2){
		        while(game.checkNull(row, numCol) == true || game.getSpaceColor(row, numCol) == 'w'){
					cout<<"Please enter a valid piece\n";

					cin>> row >> col >> finRow >> finCol;

					row = 8 - row;
					finRow = 8 - finRow;
					numCol = col - 'A';
					numFinCol = finCol - 'A';

			    }
			}
		
//		}
//		if(check == 1){
			
//			if(turnCount%2+1 == 1){
//			}
//		}


			game.getPiece(row, numCol)->ValidMoves(moves, game.getBoard());	

			moveCheck = game.ContainsMove(moves, finRow, numFinCol);

			if(moveCheck == false)
				cout << "Invalid move! This piece cannot move here."<<endl;

		}
//		cout<<finRow<<" "<<numFinCol<<endl;
        /* shouldn't need to check piece because validmoves function is virtual
         *
		if(game.getSpaceType(row, numCol) == 'P'){
			pawnptr = new Pawn(row, numCol, game.getSpaceColor(row, numCol));
			pawnptr->ValidMoves(moves, game.getBoard());
			delete pawnptr;

		}
		
		if(game.getSpaceType(row, numCol) == 'N'){
			knightptr = new Knight(row, numCol, game.getSpaceColor(row, numCol));
			knightptr->ValidMoves(moves, game.getBoard());
			delete knightptr;

		}
        */

        //get moves and print them for debugging purpose
    

        cout << "Valid moves for this piece:\n";
		for(mit = moves.begin(); mit != moves.end();++mit)
			cout<< 8 - mit->first << " " << static_cast<char>(mit->second + 'A')<<endl;

		game.Move(row, numCol, finRow, numFinCol);	
	
		if(game.PawnPCheck(PProw, PPcol) == true)
			game.PawnPromotion(PProw, PPcol);


        turnCount++;
    }

}
