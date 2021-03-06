# Ultimate Chess!

Ultimate Chess is a console-based chess game written in C++. Ultimate Chess follows all the rules of the traditional chess. Each chess piece is represented by a colored letter on a 8x8 console grid. King, Queen, Bishop, Knight, Rook and Pawn correspond to the letter 'K', 'Q', 'B', 'N', 'R' and 'P' respectively. The color of the letter can be either cyan for white pieces or magenta for black pieces. The game ends when a checkmate or a stalemate occurs.


## Getting Started

Ultimate Chess currently only runs on Linux machines. Simply clone this repository to get a copy of the souce files.  
You can clone this project by running one of the following commands in the Linux console:  
  SSH: `git clone git@github.com:px1624/chess-bot.git`  
HTTPS: `git clone https://github.com/px1624/chess-bot.git`  

### Prerequisites

Ultimate Chess uses the C++ standard library and it does not require any external libraries.  
Other requirements, including g++ compiler and make, are needed to build the program.

### Installing

Navigate to the project root directory on the console and run  
```
make
```
This should build the program "chess_player" using the makefile in the project directory.

Simple run the following command to start the program: 
```
./chess_player
```
Notice the program does not take any command line argument.

### How To Play


##### Game Menu

When you start the program, you will see the main menu.  
Enter 1 to go to the 1 player mode, 2 to go to the two player mode, or 3 to quit.  
1 player mode: you will be playing as P1 (cyan) against a computer (P2), and you will be prompted to move first  
2 player mode: two players alternating moves starting from P1 (cyan)  
quit: exit the program


##### In The Game

In both the one player and two player modes, the user has the same options of what they can enter.  
At any time, a player can quit the game by entering **QUIT** when he or she is propmted to enter a move.

The player can also enter **HINT** when prompted to enter a move to display all of the available moves he can make, broken down by piece.
   
Finally the last option a player has is to enter his move.  
To correctly enter a move, the input **_MUST_** be in the following format **rowofPiecetoMove columnofPiecetoMove theRowtoMoveTo theColumnToMoveTo**  
An example would be "2 d 4 d." The input is not case sensitive.  
All of the rules of chess apply, and the game ends when one player is put in checkmate, or a stalemate is reached.  

## Running The Tests

If you would like to check the win conditions (check and stalemate), we have prepared test cases that show that these work.

For testing checkmate, run
```
./chess_player < test2.txt
```
and to check stalemate run
```
./chess_player < input3.txt
```

## Known Issues

The only known issue so far is when the user erroneously enters an invalid value for the rows. Because the input is coming in as a string,and using stoi, if the user incorrectly enters the row, an stoi error will occur, ending the game. We did not intend for this to happen.

## Authors
  * Michael Wermert
  * Pengda Xie

