#ifndef PIECE_H
#define PIECE_H

class Piece
{
 public:

        virtual void ValidMoves(multimap < char, int > &moves, vector < vector <string> > &board, int turn ) = 0;

};

class King : public Piece
{
};

class Queen : public Piece
{
};

class Bishop : public Piece
{
};

class Knight : public Piece
{
};

class Rook : public Piece
{
}

class Pawn : public Piece
{
public:
        void ValidMoves(multimap < char, int > &moves, vector < vector <string> > &board, int turn );

        Pawn(int rowIn, int col);


    private:
        int row;
        int col;


};

#endif
