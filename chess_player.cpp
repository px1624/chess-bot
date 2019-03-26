#include <iostream>
#include <vector>
#include <string>
#include "piece.h"

using namespace std;

void PrintBoard(vector < vector <string> > &board);

void InitializeBoard( vector < vector <string> > &board);

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

    char row;
    int numRow;
    int col;
    char finRow;
    int numFinRow;
    int finCol;
    Piece *pieceptr;
    int turnCount = 0;
    string currPiece;

    vector < vector <string> > board;
    multimap <char, int> moves;
    multimap <char, int>::iterator mit;
    InitializeBoard(board);
    PrintBoard(board);

    for(int i = 0;i<2;i++){

        moves.clear();
        cout<<"P"<<turnCount%2+1<<" please enter your move: \n";

        //DATA MUST BE ENTERED IN THE FORM ROWOFYOURPIECE COLOFYOURPIECE ROWOFNEWSPACE COLOFNEWSPACE EX. A 2 B 2
        cin>> row >> col >> finRow >> finCol;

        numRow = row - 'A';
        numFinRow = finRow - 'A';

        //checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
        if(turnCount%2+1 == 1){
            while(board[numRow][col][0] != 'w'){
                cout<<"Please enter a valid piece\n";

                cin>> row >> col >> finRow >> finCol;

                numRow = row - 'A';
                numFinRow = finRow - 'A';
            }
        }
        //checks to make sure the input is valid, repeatedly makes the user has inputted a valid piece
        else if(turnCount%2+1 == 2){
            while(board[numRow][col][0] != 'b'){
            cout<<"Please enter a valid piece\n";

            cin>> row >> col >> finRow >> finCol;

            numRow = row - 'A';
            numFinRow = finRow - 'A';

            }
        }

        currPiece = board[numRow][col];

        if(currPiece[1] == 'P'){

            pieceptr = new Pawn(numRow, col);
            pieceptr->ValidMoves(moves, board, turnCount%2+1);
            for(mit = moves.begin();mit != moves.end();++mit)
                cout<<mit->first<<" "<<mit->second<<endl;

            delete pieceptr;
        }

        turnCount++;
    }

}



void PrintBoard(vector < vector <string> > &board){

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


//initializes board at the beginning of the game
void InitializeBoard( vector < vector <string> > &board){

	vector <string> temp;

	temp.push_back("bR");
	temp.push_back("bN");
	temp.push_back("bB");
	temp.push_back("bQ");
	temp.push_back("bK");
	temp.push_back("bB");
	temp.push_back("bN");
	temp.push_back("bR");

	board.push_back(temp);

	temp.resize(0);

	for(int i = 0; i < 8;i++)
		temp.push_back("bP");
		
	board.push_back(temp);

	temp.resize(0);
	
	for(int i = 0; i < 4;i++){
		for(int j = 0; j < 8;j++)
			temp.push_back(" *");

		board.push_back(temp);
		temp.resize(0);

	}

	for(int i = 0; i < 8;i++)
        temp.push_back("wP");

    board.push_back(temp);

    temp.resize(0);

	temp.push_back("wR");
    temp.push_back("wN");
    temp.push_back("wB");
    temp.push_back("wQ");
    temp.push_back("wK");
    temp.push_back("wB");
    temp.push_back("wN");
    temp.push_back("wR");

    board.push_back(temp);

    temp.resize(0);


}







