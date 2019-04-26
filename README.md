ULTIMATE CHESS USER GUIDE 

1. Ultimate chess was built and on the Hydra machines and requires no special libraries.

2. You can compile Ultimate chess using the makefile provided in the github repository. To run ultimate chess,
simply type "./chess_player" after the make

3.
------Menu---------

When you start the file, you will see the main menu. Enter 1 to go to the 1 player mode, 2 to go to the two player mode, or 3 to quit.

-------In a chess game--------

In both the one player and two player modes, the user has the same options of what they can enter. At any time, a player can quit the game
by entering "QUIT" when he or she is propmted to enter a move. The player can also enter "HINT" when prompted to enter a move to display all of the available
moves he can make broken down by piece. Finally the last option a player has is to enter his move. To correctly enter a move, the input MUST be in the 
following format "rowofPiecetoMove columnofPiecetoMove theRowtoMoveTo thecolumnToMoveTo." An example would be "2 d 4 d." The input is not case sensitive. All of the rules of chess apply, and the game ends when one player is put in checkmate, or a stalemate is reached.


4. The only known glitch so far is when the user erroneously enters an invalid value for the rows. Because the input is coming in as a string,and using stoi, if the user incorrectly enters the row, an stoi error will occur, ending the game. We did not intend for this to happen.

5. If you would like to check the win conditions (check and stalemate), we have prepared test cases that show that these work. For testing checkmate, run 
"./chess_player < test2.txt" and to check stalemate, run "./chess_player < input3.txt"


