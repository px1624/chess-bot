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
			cout<<"Invalid Input: Menu Input must be 'A' B' or 'C'"<<endl<<endl;
			cin.clear();
		}

		if(userResponse != 1 && userResponse != 2 && userResponse != 3)
			cout<<"Invalid Input: Menu Input must be 'A' B' or 'C'"<<endl<<endl;
	
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
    int turnCount = 0;
    

    ChessBoard game;
    multimap <int, int> moves;
    multimap <int, int>::iterator mit;

    for(int i = 0;i<50;i++){
		
		game.Print();
        moves.clear();
//        game.PrintAllValidMoves();
		if(game.check(turnCount%2+1) == 1)
			cout<<"CHECK!"<<endl;

        cout<<"P"<<turnCount%2+1<<" please enter your move: \n";

        //DATA MUST BE ENTERED IN THE FORM ROWOFYOURPIECE COLOFYOURPIECE ROWOFNEWSPACE COLOFNEWSPACE EX. A 2 B 2
        cin>> row >> col >> finRow >> finCol;

		row = 8 - row;
		finRow = 8 - finRow;
        numCol = col - 'A';
		numFinCol = finCol - 'A';
        

		cout<<row<<" "<<numCol<<endl;
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

        game.getPiece(row, numCol)->ValidMoves(moves, game.getBoard());

		for(mit = moves.begin(); mit != moves.end();++mit)
			cout<< mit->first <<" "<< static_cast<char>(mit->second+'A') <<endl;

		game.Move(row, numCol, finRow, numFinCol);	
	
		if(game.PawnPCheck(PProw, PPcol) == true)
			game.PawnPromotion(PProw, PPcol);


        turnCount++;
    }

}
