#ifndef PIECE_H
#define PIECE_H

class Piece
{
 public:
    virtual void ValidMoves(multimap < char, int > &moves, ChessBoard &board, int turn ) = 0;
    virtual char GetColor() = 0;
    virtual char GetSymbol() = 0;
    virtual void SetPosition(int row, int col);
    virtual void GetPosition(int &row, int &col);

protected:
    char piece_symbol;
    char piece_color;
    int row;
    int col;
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
